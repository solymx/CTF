# AlexCTF 2017 - Notes

## re4-unvm-me

可以先用 file 看 一下
```
root@lubun:/tmp/p# file unvm_me.pyc
unvm_me.pyc: python 2.7 byte-compiled
```

可以知道是 python2 的

使用工具 [uncompyle2](https://github.com/wibiti/uncompyle2)

```
root@lubun:/tmp/p# uncompyle2 unvm_me.pyc  > a.py
```

可以看一下code
```python 
#Embedded file name: unvm_me.py
import md5
md5s = [174282896860968005525213562254350376167L,
 137092044126081477479435678296496849608L,
 126300127609096051658061491018211963916L,
 314989972419727999226545215739316729360L,
 256525866025901597224592941642385934114L,
 115141138810151571209618282728408211053L,
 8705973470942652577929336993839061582L,
 256697681645515528548061291580728800189L,
 39818552652170274340851144295913091599L,
 65313561977812018046200997898904313350L,
 230909080238053318105407334248228870753L,
 196125799557195268866757688147870815374L,
 74874145132345503095307276614727915885L]
print 'Can you turn me back to python ? ...'
flag = raw_input('well as you wish.. what is the flag: ')
if len(flag) > 69:
    print 'nice try'
    exit()
if len(flag) % 5 != 0:
    print 'nice try'
    exit()
for i in range(0, len(flag), 5):
    s = flag[i:i + 5]
    if int('0x' + md5.new(s).hexdigest(), 16) != md5s[i / 5]:
        print 'nice try'
        exit()

print 'Congratz now you have the flag'
```

把上面的 md5 依序轉回來就可以看到 flag 

## RE2 C++ is awesome

這題先執行看一下
```
root@lubun:/tmp/p# ./re2 flag
Better luck next time
root@lubun:/tmp/p# ./re2 ALEXCTF
You should have the flag by now
```

觀察可以看到只要給的字串是 FLAG 的一部分就會印出 You should have the flag by now

所以可以直接暴力
```python
#!/usr/bin/env python
import os
import string
allword = string.ascii_letters + string.digits + "_}"

flag = "ALEXCTF{"

while True:
	for i in allword:
		tmp = flag + i 
		if "flag" in os.popen("./re2 " + tmp).readline():
			flag = tmp
			print flag
			break
	if '}' in flag:
		break
```

或者可以直接 IDA PRO 分析來看

可[參考](https://ngaoopmeo.blogspot.tw/2017/02/alexctf-2017write-upre2-c-is-awesomed.html)

真的看不懂 C++ QQ..

## RE3: Catalyst system

一開始執行會發現等超久，用 ltrace 可以看到他是用 sleep 

把她 patch 掉

```
# sed -i s/sleep/isnan/g ./a
```

他之後會要我們輸入 username 和 password ，用 ida pro 看 main 

```
  sub_400C9A(username);
  sub_400CDD(username);
  sub_4008F7(username);
  sub_400977(username, password);
  sub_400876(username, password);
```

在 sub_400CDD 中，可以得到 username ，用 z3 解
```python
import libnum
from z3 import *
a1 = Int('a1')
a2 = Int('a2')
a3 = Int('a3')
s = Solver()
s.add(a1 - a2 + a3 == 1550207830)
s.add(a2 + 3 * (a3 + a1) == 12465522610)
s.add(a3 * a2 == 3651346623716053780)
if s.check() == sat:
	m = s.model()

print (libnum.n2s(m[a3].as_long())+libnum.n2s(m[a2].as_long())+libnum.n2s(m[a1].as_long()))[::-1]

```

得到 username = "catalyst_ceo"

密碼去分析 sub_400977 

```python 
#!/usr/bin/env python
#!/usr/bin/env python
import libnum
rand=[6833993,1732044087,2068121063,1889579618,869606716,1364883061,1500347741,2094174281,1508322742,1179934733]
sol =[  1441465642, 251096121 , -870437532 , -944322827 , 647240698 , 638382323 , 282381039 , -966334428 , -58112612 ]
password = []

for i in range(len(sol)):
	password.append(rand[i] + sol[i]) 
password.append( 605226810 + rand[-1] )
password.append( 605226810)

print ''.join([libnum.n2s(password[i])[::-1] for i in range(len(password)) ])
```

可以得到 "sLSVpQ4vK3cGWyW86AiZhggwLHBjmx9CRspVGggj"

輸入正確後可以得到 FLAG 

[參考](https://isitdtu.blogspot.tw/2017/02/alexctf-re3-catalyst-system.html)


## RE5: packed movement

一開始用 strings ，在開頭會看到
```
9vUPX!
td?$I
/lib
nux.so.2
msigaction
```

所以是有用 upx 去加殼，也可用其他工具去證明 如 Detect it Easy

解殼在 linux 上面也很簡單
```
$ upx -d ./move 
```

之後丟 ida 分析 ，可以看到 code 很長

試試看
```
root@lubun:/tmp/p# objdump -d -M intel ./move | grep 0x41
 80493db:       c7 05 68 20 06 08 41    mov    DWORD PTR ds:0x8062068,0x41
root@lubun:/tmp/p# objdump -d -M intel ./move | grep 0x4c
 8049dde:       c7 05 68 20 06 08 4c    mov    DWORD PTR ds:0x8062068,0x4c
root@lubun:/tmp/p# objdump -d -M intel ./move | grep 0x45
 804a7e1:       c7 05 68 20 06 08 45    mov    DWORD PTR ds:0x8062068,0x45

### ALEXCTF 
```

這樣我們把它弄出來分析
```
root@lubun:/tmp/p# objdump -d -M intel ./move | grep "mov    DWORD PTR ds:0x8062068," > test
```

寫 code 解 

```python 
a = [0x41, 0x4c, 0x45, 0x58, 0x43, 0x54, 0x46, 0x7b, 0x4d, 0x30, 0x56, 0x66, 0x75, 0x73, 0x63, 0x34, 0x74, 0x30, 0x72, 0x5f, 0x77, 0x30, 0x72, 0x6b, 0x35, 0x5f, 0x6c, 0x31, 0x6b, 0x65, 0x5f, 0x6d, 0x34, 0x67, 0x31, 0x63, 0x7d]

print ''.join([chr(a[i]) for i in range(len(a))])
```

這樣可以到 flag 

[參考 1](https://isitdtu.blogspot.tw/2017/02/alexctf-re5-packed-movement.html)
[參考 2](https://github.com/TeamContagion/CTF-Write-Ups/tree/master/AlexCTF-2017/Reversing/RE5%20-%20Packed%20Movement%20(350))
[參考 3](https://www.amn3s1a.com/blog/writeup/2017/02/10/AlexCTF-PackedMovement.html)