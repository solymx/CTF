# tinyCTF 2014 - Notes


## WTC RSA BBQ
> hint: WTC refers to the Twin Towers

這題考 twin prime

代表 p 和 q 差值為 2

可以看成 ```n = (p+1)*(p-1) = p^2 - 1```


```python
#!/usr/bin/env python
from Crypto.PublicKey import RSA
import libnum

pub = RSA.importKey(open('key.pem').read())
n = pub.n
e = pub.e
c = libnum.s2n(open('cipher.bin').read())
tmp = libnum.nroot(n+1, 2)
p = tmp+1
q = tmp-1
phi = (p-1)*(q-1)
d = libnum.invmod(e, phi)
m = libnum.n2s(pow(c,d,n))
print m
```
