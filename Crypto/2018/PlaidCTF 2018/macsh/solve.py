#!/usr/bin/env python
from pwn import *
r = remote('macsh.chal.pwning.xxx',64791)

# tag1 = pad ^ cmd
info(r.recvuntil('|$|> '))
cmd = "cat ././flag.txt"
r.sendline("<|>tag " + "a"*2048 + cmd)
tag1 = int(r.recvuntil('\n')[:-1], 16)
info("tag1: " + hex(tag1) )


# tag2 = pad ^ trash
info(r.recvuntil('|$|> '))
trash = "x"*16
r.sendline("<|>tag " + "a"*2048 + trash)
tag2 = int(r.recvuntil('\n')[:-1], 16)
info("tag2: " + hex(tag2) )

# tag3 = nopad ^ trash
info(r.recvuntil('|$|> '))
r.sendline("<|>tag " + trash)
tag3 = int(r.recvuntil('\n')[:-1], 16)
info("tag3: " + hex(tag3) )

# tag4 = no_pad ^ cmd
tag4 = hex(tag1 ^ tag2 ^ tag3)[2:]

info("tag4: "+tag4)
info(r.recvuntil('|$|> '))

r.sendline(tag4 + "<|>" + cmd)

r.interactive()