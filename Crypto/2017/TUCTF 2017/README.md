# TUCTF 2017 - Notes


## The Never Ending Crypto

```python
#!/usr/bin/env python
from pwn import *

r = remote('neverending.tuctf.com', 12345)

for i in range(1,51):
	print r.recvuntil('Round %d. Give me some text:' % i)
	r.sendline('aabbcc')
	print r.recvuntil('encrypted is ')
	data = r.recv(1)
	print "data:",data
	count = ord(data) - ord('a')
	print "count:",count
	print r.recvuntil('What is ')
	c = r.recv(15)
	print "c:",c
	print r.recvrepeat(0.1)
	m = ''
	for i in c:
		tmp = ord(i) - count
		if tmp >= 127:
			tmp -= 95
		elif tmp < 32:
			tmp += 95
		m += chr(tmp)
	print "m:",m
	r.sendline(m)

	## first round end



r.interactive()
"""
nc neverending.tuctf.com 12345
"""


```

## Transporter
> Description:
>
> We have discovered some hackers have infiltrated our mainframe and may have exfiltrated some highly classified data.
Can you help us figure out what they stole?

> nc transporter.tuctf.com 54321

沒找到檔案 QQ ，大概看別人的 Write up 紀錄一下

nc 過去可以獲取到一個 pcap ，可以從中找到兩個有用的 base64 encode 的東西

```
# echo "ZW5jX2tleToxMzA1NTIzMDU0MDQyNjY0NTk2NDg0OTQKbjo1NDI4MDA1NzMzODAwODQ4MjY5MTAzODEKZTo2NTUzNwppdjpkqmNUCELPqQ==" | base64 -d
enc_key:130552305404266459648494
n:542800573380084826910381
e:65537
iv:d▒cBϩ
```

在後面補一下 xxd ，可以看到 iv 是 `64aa63540842cfa9`


和另一個是 cipher: `bncFlPPa6T6JFup6dMYQn7m3uWokRWYT3K/j907seyUm8Pk19ZD9a5hgPZ/P8w0itxAyMZNyG7dOtINeCVhSxw==`


那 iv 因為是 8 bytes ，可以直接猜是 des ，然後有 n, e 所以總結一下:
1. 先 rsa 解密 enc_key
2. 用得到的 iv 和 key 去解 cipher (DES)


```
from Crypto.Util.number import *
import gmpy2
import base64
import pyDes

p = 2693
q = 201559811875263582217
rsa_c = 130552305404266459648494
n=542800573380084826910381
e=65537
d = int(gmpy2.invert(e, (p-1)*(q-1)))
k = long_to_bytes(pow(rsa_c,d,n))
c = base64.b64decode('bncFlPPa6T6JFup6dMYQn7m3uWokRWYT3K/j907seyUm8Pk19ZD9a5hgPZ/P8w0itxAyMZNyG7dOtINeCVhSxw==')
iv = long_to_bytes(0x64aa63540842cfa9)

key = pyDes.des(k, pyDes.CBC, iv)
print(key.decrypt(c))
```





