#!/usr/bin/env python
from Crypto.PublicKey import RSA
import libnum

key = RSA.importKey(open("pubkey.pem").read())
e = key.e 
n = key.n
c = libnum.s2n(open("flag.enc").read())

p = 275127860351348928173285174381581152299
q = 319576316814478949870590164193048041239
d = libnum.invmod(e, (p-1)*(q-1))
print libnum.n2s(pow(c,d,n))