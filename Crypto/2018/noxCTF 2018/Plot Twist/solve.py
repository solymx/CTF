#!/usr/bin/env python
from pwn import *
from MTRecover import MT19937Recover

HOST = 'chal.noxale.com'
PORT = 5115
r = remote(HOST, PORT)

print r.recvline()
tmp = '0'*16
for _ in range(625):
	print r.send(tmp)

k = []
for _ in range(625):
	r.recvuntil('Wrong! The key was: ')
	t = int(r.recvuntil('\n')[:-1])
	k.append(t)

mtb = MT19937Recover()
rand = mtb.go(k)
to_send = str(rand.getrandbits(32)).rjust(16, '0')
r.send(to_send)
print r.recvline()
r.interactive()