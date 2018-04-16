# GreHack 2017

## New Dsa
> Description:
>
> I think I did a major breakthrough in cryptography: I managed to implement the DSA algorithm without any need of a random source. After all, all we need is a nonce, right ?
> 
> Don't you dare tell me it's insecure: I tested it!
>
> Don't you dare tell me it's insecure: I tested it! But if you think you're smarter than me, I dare you to sign sign_me with my key just knowing the signature of signed which is signature.

這題給了我們 public key(p,q,g,y) 和 signature(r,s) 和 一個要加密的 msg

dsa 中，如果可以獲取隨機數 k 則可以透過公式推導出私鑰: x

而這題的 k 的產生是透過 signed 和 public key(q) 來獲取的，所以我們可以直接計算出 k

並以此來推導出 x

```python
#!/usr/bin/env python
from Crypto.PublicKey import DSA
from Crypto.Hash import SHA
impor libnum

def nonce(msg, max_int):
	n = 0
	for i in msg:
	    n += i % max_int
	    n = 53*n % max_int
	n = (n - len(msg)) % max_int 
	return n


key = DSA.importKey(open("public.pem").read())
p = key.p
q = key.q
g = key.g
y = key.y

signed = open("signed.txt","rb").read()
sign_me = open("sign_me.txt","rb").read()
r,s = eval(open("signature.txt").read())

k = nonce(map(ord, signed), q)
h = libnum.s2n(SHA.new(signed).digest())
x = ((k*s - h) * libnum.invmod(r,q)) % q
h_new = libnum.s2n(SHA.new(sign_me).digest())
new_k = nonce(map(ord,sign_me), q)

new_r = pow(g,new_k,p) % q
new_s = libnum.invmod(new_k,q) * (h_new + x*new_r) % q

print "r=%d , s=%d" % (new_r, new_s)
```

