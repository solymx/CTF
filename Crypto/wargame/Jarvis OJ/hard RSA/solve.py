#!/usr/bin/env python
from Crypto.PublicKey import RSA
import libnum
key = RSA.importKey(open("pubkey.pem").read())
e = key.e
n = key.n
c = libnum.s2n(open("flag.enc").read())
p = 275127860351348928173285174381581152299
q = 319576316814478949870590164193048041239

mp = pow(c, (p+1) / 4, p)
mq = pow(c, (q+1) / 4, q)
yp, yq, _ = libnum.xgcd(p, q)

r = (yp*p*mq + yq*q*mp) % n
s = (yp*p*mq - yq*q*mp) % n
_r= n-r
_s=n-s

print libnum.n2s(r)
print libnum.n2s(s)
print libnum.n2s(_r)
print libnum.n2s(_s)