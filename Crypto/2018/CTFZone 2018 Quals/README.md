# CTFZone 2018 Quals - Notes

## USSH
> Description:
> We've developed a new restricted shell. It also allows to manage user access more securely. Let's try it
> 
> nc crypto-01.v7frkwrfyhsjtbpfcppnu.ctfz.one 1337


連線過去，隨便輸入一個名稱，之後用 help 看有哪些指令可用

ls 下可以看到有 flag.txt ，但 cat 不可以看，因為不是 root

然後用 id 看一定都是 uid = 3 , gid = 3, groups = 3

```
root@solymx:/tmp/del# nc crypto-01.v7frkwrfyhsjtbpfcppnu.ctfz.one 1337
Login: a
Group: regular
a, welcome to crypto sh

a@crypto: $ help
Avaliable commands: ls, cat, id, session, help, exit

ss@crypto: $ ls
flag.txt  info.txt  backup.sh

ss@crypto: $ cat flag.txt
cat: flag.txt: Permission denied.
Expect group=root

ss@crypto: $ id
uid=3(regular) gid=3(regular) groups=3(regular)
```

裡面有一個有趣的指令是 session，他以冒號為分隔，冒號前面是 iv ，且必須是 16 bytes 長


```
asdasd@crypto: $ session
Usage: session [OPTIONS]

  --get  Print session
  --set [SESSION]  Set session

asdasd@crypto: $ session --get
ZMJbz8VLsSy5HtvKdFH4bQ==:kn+xK4dHxI0mp6oV7UvJLpCUq8PLyJUSpCVBMaUccD0=

as@crypto: $ session --set YXNkcw==:0Ykvzk7mt5hUgAM9MBmEYW2SoNZ1IihZFPKzjuWR1LA=
Error: IV must be 16 bytes long
```

如果對 iv 的第一個byte 做位元翻轉會出現 Invalid session
```python
#!/usr/bin/env python
from pwn import *

HOST = 'crypto-01.v7frkwrfyhsjtbpfcppnu.ctfz.one'
PORT = 1337

r = remote(HOST, PORT)

r.sendlineafter('Login: ', "aaaa") # send username and login
r.sendlineafter('crypto: $ ', "session --get")
iv, ct = map(b64d, r.recvuntil('\n')[:-1].split(':'))
iv = xor(iv,1)
s = b64e(iv) + ':' + b64e(ct)

r.sendlineafter('crypto: $ ', 'session --set ' + s)

r.interactive()
```

把每個 byte 嘗試位元翻轉，這邊我輸入的 login name: aaaa

翻轉第十個會改 login name: caaa
翻轉第十一個會改 login name: acaa
翻轉第十二個會改 login name: aaca
翻轉第十三個會改 login name: aaac

底下是使用的 code ，這邊翻是用 2 ，因為翻 1 的話會變成不可反引號不好打出來

```
#!/usr/bin/env python
from pwn import *

HOST = 'crypto-01.v7frkwrfyhsjtbpfcppnu.ctfz.one'
PORT = 1337

r = remote(HOST, PORT)

r.sendlineafter('Login: ', "aaaa") # send username and login
r.sendlineafter('crypto: $ ', "session --get")
iv, ct = map(b64d, r.recvuntil('\n')[:-1].split(':'))

filp = "".join(map(chr, [0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0]))

iv = xor(iv,filp)
s = b64e(iv) + ':' + b64e(ct)

r.sendlineafter('crypto: $ ', 'session --set ' + s)

r.interactive()
```

翻轉其他的都是 Invalid session ，這代表可能她的儲存格式是 {'user':...} 這種

然後改到旁邊的東西了

透過這種方式可以直接改 username 為 admin 之類的，可是會發現還是不可以看到 flag.txt

因為他看的是 group，所以也要改掉 group ，那我們知道 username 是出現在

第 10 個 bytes 開始，group 應該會放在後面，可能就會到第二個 block 了 


那現在我們來測一下，輸入 name 長度是多少會多一個 block
```python
#!/usr/bin/env python
from pwn import *

HOST = 'crypto-01.v7frkwrfyhsjtbpfcppnu.ctfz.one'
PORT = 1337

for i in range(1,17):
	r = remote(HOST, PORT)
	name = "a"*i
	r.sendlineafter('Login: ', name) # send username and login
	r.sendlineafter('crypto: $ ', "session --get")
	iv, ct = map(b64d, r.recvuntil('\n')[:-1].split(':'))

	print "login name length: ",len(name)
	print "ct length: ", len(ct)

	r.close()
```


可以發現當 name 長度到 9 的時候會多一個 block ， ct 長度由 32 -> 48

有可能前面是 "username=" 剛好九個 bytes 這樣

這樣我們可以猜測應該是

`username=xxxxxxxxx&group=regular`

剛好 32 個 bytes 這樣，

username=aaaaaaaaaaaaaaaaaaa&group

這邊的 & 是我自己猜的，實際上他用哪個不知道

所以可以輸入名稱: user1agroup=root

然後用位元翻轉改 a 為分隔符號

所以現在的做法會有兩個:
1. 改 group name 為 root
2. 改 分隔符號


這邊先嘗試改分隔符號，輸入 Name: adminkgroup=root

這樣要翻轉第十五個位元，嘗試爆破 xor  0 - 255 

不過可以先猜可能是 & ，這樣就是xor 77

```
#!/usr/bin/env python
from pwn import *

HOST = 'crypto-01.v7frkwrfyhsjtbpfcppnu.ctfz.one'
PORT = 1337

r = remote(HOST, PORT)

r.sendlineafter('Login: ', "adminkgroup=root") # send username and login
r.sendlineafter('crypto: $ ', "session --get")
iv, ct = map(b64d, r.recvuntil('\n')[:-1].split(':'))

filp = "".join(map(chr, [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 77, 0]))

iv = xor(iv,filp)
s = b64e(iv) + ':' + b64e(ct)

r.sendlineafter('crypto: $ ', 'session --set ' + s)

r.interactive()
```

這樣可以 get flag



那這次換第一種方式，要去改 group name

就先 xor ct 找哪一個會改到 regular


```python
#!/usr/bin/env python
from pwn import *

HOST = 'crypto-01.v7frkwrfyhsjtbpfcppnu.ctfz.one'
PORT = 1337

r = remote(HOST, PORT)

r.sendlineafter('Login: ', "a"*23) # send username and login
r.sendlineafter('crypto: $ ', "session --get")
iv, ct = map(b64d, r.recvuntil('\n')[:-1].split(':'))

l = [0]*48
l[23] = 1
filp = "".join(map(chr, l))

ct = xor(ct,filp)
s = b64e(iv) + ':' + b64e(ct)

r.sendlineafter('crypto: $ ', 'session --set ' + s)

r.interactive()
```


用上面的 code 可以發現到 23 這個位元改掉，用 id 看會變成
```
aaaaaaaÅ �@crypto: $ id
uid=3(segular) gid=3(segular) groups=3(segular)
```

最後用爆破找結尾要哪個 byte
```python
#!/usr/bin/env python
from pwn import *

HOST = 'crypto-01.v7frkwrfyhsjtbpfcppnu.ctfz.one'
PORT = 1337

for i in range(256):
	r = remote(HOST, PORT)

	r.sendlineafter('Login: ', "a"*23) # send username and login
	r.sendlineafter('crypto: $ ', "session --get")
	iv, ct = map(b64d, r.recvuntil('\n')[:-1].split(':'))

	l = [0]*23 + map(ord, xor('regular)', 'root)')) + [i] + [0]*16
	filp = "".join(map(chr, l))

	ct = xor(ct,filp)
	s = b64e(iv) + ':' + b64e(ct)

	r.sendlineafter('crypto: $ ', 'session --set ' + s)
	r.sendlineafter('crypto: $ ', 'cat flag.txt')
	res = r.recvline()
	print "res: ",res
	if 'ctfzone' in res:
		print res
		raw_input("#")
	else:
		r.close()
```
最後可獲得
```
res:  ctfzone{2e71b73d355eac0ce5a90b53bf4c03b2}
```



