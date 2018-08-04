# ISITDTU CTF 2018 Quals - Notes

## xor


從 enc_flag 可以知道 flag 長度是 130

然後已知 key 長度是 10

然後我們知道 flag 是 ISITDTU{....}

想法是要把 key 算出來

看他的加密方式，可以先簡單看一下 index 之間的關係

```python
key="123456789a"
flag = string.ascii_lowercase*5
count = 0
for a in range(len(key)):
    i = a
    for b in range(len(flag)//len(key)):
        if b % 2 != 0:
            m.append(ord(flag[i]) ^ ord(key[a]))
            print("count = ",count)
            print("b % 2 != 0  ",i, a)
            input("#")
            count += 1
        else:
            m.append(ord(flag[i+len(key)-(a+1+a)])^ ord(key[a]))
            print("count = ",count)
            print("b % 2 == 0   ",i+len(key)-(a+1+a),a)
            input("#")
            count += 1
        i += len(key)
```

然後因為 flag 格式的關係，可以知道 index: 0, 1, 2, 3, 4, 5, 6, 7, 129 的 flag 值

從上面的 code 可以得到有用的對應來算出 key 值
```
count =  12
b % 2 == 0    129 0

count =  26
b % 2 == 0    7 2

count =  39
b % 2 == 0    6 3

count =  52
b % 2 == 0    5 4

count =  65
b % 2 == 0    4 5

count =  78
b % 2 == 0    3 6

count =  91
b % 2 == 0    2 7

count =  104
b % 2 == 0    1 8

count =  117
b % 2 == 0    0 9
```

可以簡單寫一個程式算一下
```python
enc_flag = "1d14273b1c27274b1f10273b05380c295f5f0b03015e301b1b5a293d063c62333e383a20213439162e0037243a72731c22311c2d261727172d5c050b131c433113706b6047556b6b6b6b5f72045c371727173c2b1602503c3c0d3702241f6a78247b253d7a393f143e3224321b1d14090c03185e437a7a607b52566c6c5b6c034047"


flag = 'ISITDTU{'
m = []
for i in flag:
	m.append(ord(i))

c = []
for i in range(0,len(enc_flag),2):
	c.append(int(enc_flag[i:i+2], 16))

key = [0]*10

key[0] = ord('}') ^ c[12]
key[2] = m[7] ^ c[26]
key[3] = m[6] ^ c[39]
key[4] = m[5] ^ c[52]
key[5] = m[4] ^ c[65]
key[6] = m[3] ^ c[78]
key[7] = m[2] ^ c[91]
key[8] = m[1] ^ c[104]
key[9] = m[0] ^ c[117]


k = ''
for i in key:
	k += chr(i)

cc = ''
for i in c:
	cc += chr(i)



key = ''.join([chr(k) for k in key])
# key = x\x00RCr4cKm3
```

這樣除了 key[1] 不知道以外，其他 key 值都知道了

這樣就可以解密，在大概猜一下就好



## Simple RSA

直接[參考](https://ctftime.org/writeup/10525)這篇找質數

用 RsaCtfTool 不知道為啥會解不成功 - -

有質數其他都一樣了 

```python
#!/usr/bin/env python
from Crypto.Util.number import *
import gmpy2

def find_n(seed):
    p = gmpy2.next_prime(seed)
    p1 = gmpy2.next_prime(10*p)
    p2 = gmpy2.next_prime(10*p1)
    p3 = gmpy2.next_prime(10*p2)
    return p*p1*p2*p3

N = 603040899191765499692105412408128039799635285914243838639458755491385487537245112353139626673905393100145421529413079339538777058510964724244525164265239307111938912323072543529589488452173312928447289267651249034509309453696972053651162310797873759227949341560295688041964008368596191262760564685226946006231
c = 153348390614662968396805701018941225929976855876673665545678808357493865670852637784454103632206407687489178974011663144922612614936251484669376715328818177626125051048699207156003563901638883835345344061093282392322541967439067639713967480376436913225761668591305793224841429397848597912616509823391639856132
e = 65537
r = 0

for i in range(280, 0, -1):
    if find_n(r + 2**i) <= N:
        r += 2**i

p = gmpy2.next_prime(r)
p1 = gmpy2.next_prime(p*10)
p2 = gmpy2.next_prime(p1*10)
p3 = gmpy2.next_prime(p2*10)

phi = (p-1)*(p1-1)*(p2-1)*(p3-1)
d = gmpy2.invert(e,phi)
m = pow(c,d,N)
print(long_to_bytes(m))


```

## Baby
> Description:
>
> nc 35.185.178.212 33337 or nc 35.185.178.212 33338
>
> Download file : https://mega.nz/#!GiRiFazQ!Itnwoq3-Oysgf5fVZ_jeXCROpWnI8wEIOqeAlkoUbZY

先看程式碼，會把我們輸入的數字和 flag 做 or 之後做 sha512 給我們

所以給數字 0 就可以得到 sha512(flag)

```
root@solymx:/tmp/p#  nc 35.185.178.212 33338
********************Hello World********************
***************************************************
Number: 0
0
2c7b44d69a0f28798532e4bb606753128969e484118bd0baa215c6309ce6dc016c9a5601471abf4c556c0dc5525eb4144078a761a6456c919d134be8a10c64a0
```

所以我們先得到 sha512(flag) = 2c7b44d69a0f28798532e4bb606753128969e484118bd0baa215c6309ce6dc016c9a5601471abf4c556c0dc5525eb4144078a761a6456c919d134be8a10c64a0


那現在就是一個一個 bit 去翻轉，要注意的是她用的是 or

or 是只要都是 1 就是 1 ，我們這邊一個一個位元翻轉

一個字的 range 是 1 ~ 16 ，找最大的數字

之後找第二個 byte ，所以要一次性加 16

之後找第三個 ，要一次性加 256 

以此類推


```python
#!/usr/bin/env python
from pwn import *
import string
import libnum

allstr = string.printable
correct = '2c7b44d69a0f28798532e4bb606753128969e484118bd0baa215c6309ce6dc016c9a5601471abf4c556c0dc5525eb4144078a761a6456c919d134be8a10c64a0'



HOST = '35.185.178.212'
PORT = 33338

flag = []
n = 0
exp = 0
highest = 0
while 1:
	add = 16**exp
	for i in range(16):
		r = remote(HOST, PORT)
		r.sendlineafter('Number: ', str(n))
		r.recvline()
		res = r.recvline()[:-1]
		if res == correct:
			highest = n
			print "now i = ",i
		n += add
		print "n = ",n
		r.close()
	print "now find: ", hex(highest)
	exp += 1
	n = highest


print libnum.n2s(highest)
```

# Love Cryptography
> Description:
> File : https://mega.nz/#F!LjI2DYTK!GfoapiUhLcNeIs9P68Dl6A

首先看 code ，可以知道 "ISITDTU" 在 mes 裡面，所以先找她的位置

找的方法是: # 看 ISITDTU
enc[i] == enc[i+2]
enc[i+3] == enc[i+5]

```python
for i in range(len(enc)):
	if enc[i] == enc[i+2] and enc[i+3] == enc[i+5]:
		print i
```

這樣執行完可以知道位置在 36

之後要找 m ，首先我們知道:

S: 83
T: 84

所以讓 enc[39] - s[37]

這樣是 (2m + c ) % n - (m + c) % n

因為我們得到的答案是正數，代表他們還在同一個 round 中

所以 enc[39] - s[37] = m = 1110321085421447768275945874294757311370451552696385093861149689

下一個要找 n ，首先我們知道

T: 84
U: 85

那讓 enc[42] - enc[41] 會等於

(2m + c ) % n - (m + c) % n

得到的是負數，代表過了一個 round 了

那我們知道 enc[39] - enc[37] 是一個 m (沒超過 n)

enc[42] - enc[41] 也是一個 m (超過 n)

所以這兩個相減剛好是 n = 2315197515117055002182146598022231651703195899527687614857413551


最後暴力求 c 

```python
for k in range(1000):
	c = k * n + 1470896290937720121923671834268680644293311486759008609851306976 - 73*m
	if (73*m + c ) % n == enc[36] and (ord('S') * m + c) % n == enc[37]:
		print "get c = ",c
		raw_input()
```

猜  c =  1449370084268958114154753941529504723862204623391963277996853964

所以來解密


```python
#!/usr/bin/env python

import string

allstr = string.printable

m = 1110321085421447768275945874294757311370451552696385093861149689
n = 2315197515117055002182146598022231651703195899527687614857413551
c = 1449370084268958114154753941529504723862204623391963277996853964


# generate all
f = {}
for i in allstr:
	f[str((m*ord(i) + c) % n)] = i 

flag = ""
for c in enc:
	flag +=f[str(c)]
```


## aes cnv

直接看一下 challenge 可以看到

他一開始會要你輸入明文，然後 aes 加密後給你密文

然後再要你輸入密文，會幫你解密

然後禁止你要求 "Give me the flag" 的密文

所以只要可以構造 "Give me the flag" 的密文，給他就可以得到 flag 了

觀察可以發現 "Give me the flag" 長度是 16

所以她會 padding 第二組，總共會有二組 block

第一組是 "Give me the flag"，第二組是 padding

那我們改給他 "give me the flag" 然後取密文第一個 block 的第一個 byte

用 xor 改 g 為 G 就可以得到 "Give me the flag" 的密文


```python
#!/usr/bin/env python
from pwn import *

HOST = '127.0.0.1'
PORT = 13337

r = remote(HOST, PORT)
#Give me the flag
r.sendlineafter('request you want to encrypt:', 'give me the flag')
r.recvuntil('Your encypted: ')
c = b64d(r.recvuntil('\n')[:-1])
c = b64e(chr(ord('g') ^ ord('G') ^ ord(c[0])) + c[1:])

r.sendlineafter('your request: ', c)
r.interactive()
```




