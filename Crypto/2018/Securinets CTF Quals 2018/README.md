# Securinets CTF Quals 2018 - Notes

## The worst RSA Joke
> Description:
>
> The Emperors heard that the biggest weakness of RSA is when the attacker try to factorize the public modulous. That's why they ordered their security team to create pair keys using a single strong (big) prime modulous. Then, they started sending the first secret information. Given the public key and the ciphertext, can you decrypt the message ? 

這題說他的 n 只是一個 prime 

所以 phi(n) = n-1

直接算 rsa 就好...

```python
#!/usr/bin/env python
from Crypto.PublicKey import RSA
import libnum
import base64
c = libnum.s2n(base64.b64decode(open('flag.enc').read().strip()))
key = RSA.importKey(open('public.pem').read())
e = key.e
n = key.n
d = libnum.invmod(e,n-1)
print libnum.n2s(pow(c,d,n))
```


## looser
他要我們解密一個 png ，我們知道 png 前面的header 都是相同的

然後可以發現他是只 xor one byte ... ，簡單解密一下即可

```python
#!/usr/bin/env python
from pwn import *

one_byte = 238
c = open('flag.png.crypt').read()
with open("flag.png",'wb') as f:
	f.write(xor(c,one_byte))
```


## Improve the quality
> Description:
>
> 