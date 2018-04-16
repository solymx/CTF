#!/usr/bin/env python
from Crypto.PublicKey import RSA
import gmpy2
import libnum

c = open('encrypt.txt','rb').read()
key1 = RSA.importKey(open('recovered_1.key','rb').read())
key2 = RSA.importKey(open('recovered_2.key','rb').read())
p = int(gmpy2.gcd(key1.n, key2.n))
q = key2.n / p 
phi = (p-1)*(q-1)
e = key2.e
d = int(gmpy2.invert(e, phi))
print libnum.n2s(pow(c,d,key2.n))
