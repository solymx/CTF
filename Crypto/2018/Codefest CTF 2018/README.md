# Codefest CTF 2018 - Notes

## Access Denied?

先看一下程式碼:

一開始會要輸入 username ，之後用一個不知道是啥的函數確認有沒在裡面

沒的話會取 `_count: 範圍在 0 ~ 999` ，然後因為 random 有放 seed ，所以代表 random 是固定的

所以他後面都是可以算的，唯一不知道的只有一開始的 `_count` ，但她範圍只在 1000 內，所以可以寫個程式跑

```python
#!/usr/bin/env python
# -*- coding:utf-8 -*-
from pwn import *

HOST = '34.216.132.109'
PORT = 9094

# 先計算好
user = 'spreadfame'
codes = []
for c in range(1000):
# generate a code

	generator = "xorshift"
	random.seed(generator)
	count = 0;

	for ch in user:
		ra = random.randint(1, ord(ch))
		rb = (ord(ch) * random.randint(1, len(user))) ^ random.randint(1, ord(ch))

		count += (ra + rb)/2


	code = 1

	for i in range(1,count+c):
		code = (code + random.randint(1, i) ) % 1000000

	final = random.randint(1,9) * 1000000 + code

	codes.append(final)
# end 

r = remote(HOST, PORT)

r.sendlineafter('Enter your name: ',user)
r.sendlineafter('Enter your access code: ', '0')

for i in codes:
	r.sendlineafter('Please enter the code: ', str(i))
	print r.recvline()
	print r.recvline()
	res = r.recvline()
	print "res: ",res
	if 'Incorrect' not in res:
		print res
		raw_input()

r.interactive()
```

## ConveRSAtion
> Description:
>
> Alice and Bob were communicating over an insecure channel. Eve was listening on the whole conversation and this is what she saw:
> 
> Alice: Should I send you the flag?
> Bob: Fine. But make sure you encrypt it.
> Alice: That's a given. But first let me send you an encrypted test message.
> Alice: [test_ciphertext.txt](ConveRSAtion/test_ciphertext.txt)
> Bob: Well, everything works just as expected. Just send the flag already.
> Alice: Here you go.
> Alice: [ciphertext.txt](ConveRSAtion/ciphertext.txt) Given the limited information, Eve went to Bob's website to learn some more. She found that for different [public exponents](ConveRSAtion/public_keys.txt), Bob uses the same [message space](ConveRSAtion/message_space.txt). Moreover, Eve found an [implementation](ConveRSAtion/rsa.py) of the RSA cryptosystem in Bob's GitHub repository. From all the information Eve could gather, can you help her retrieve the flag?
> Output Format
> 
> CodefestCTF{flag} 

[參考](https://ctftime.org/writeup/10902)


首先一樣看一下程式碼，就是一個很標準的 rsa 加解密，唯一比較特別的地方在產生金鑰的部分
```python
    p = get_prime(1024)
    d = p
    e = inverse_mod(d, phi_n)
```

從這邊可以知道:
1. d 也是 n 的因數
2. e % p-1 = 1
3. r^e = r mod p for any r
4. r^e mod n = (r mod p) mod n

而 `r^e − r mod n` 有一個因數是 p，所以 `gcd(r^e − r mod n, n) = p`


不過題目沒有給 n ，但他有給一個 message space ，這個指的是 M 的範圍，根據 message space 定義 `{0:n-1}`

所以可以直接從 message space 得到 n






