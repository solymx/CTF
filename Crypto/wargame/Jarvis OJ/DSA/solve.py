#!/usr/bin/env python
from Crypto.PublicKey import DSA
import libnum
import hashlib
key = DSA.importKey(open("dsa_public.pem").read())

m3 = open("message3").read()
m4 = open("message4").read()
h3 = int(hashlib.sha1(m3).hexdigest(),16)
h4 = int(hashlib.sha1(m4).hexdigest(),16)
r = 0x5090DA81FEDE048D706D80E0AC47701E5A9EF1CC
s3 = 0x30EB88E6A4BFB1B16728A974210AE4E41B42677D
s4 = 0x5E10DED084203CCBCEC3356A2CA02FF318FD4123

k = ((h3 - h4) * libnum.invmod(s3 - s4, key.q)) % key.q
x = ((k*s3 - h3)*libnum.invmod(r, key.q) ) % key.q
print "CTF{%s}" % (str(x))