# ais3 final 2015 - Notes

## crypto2


先簡單看一下程式碼，他使用 OFB Mode ，然後 iv 和 key 雖然不知道，但是是寫死的

然後一開始會先用 aes-ofb 加密 flag 印給我們，之後無限迴圈加密 32 長度的隨機英文小寫給我們

我們知道在 OFB Mode 中:

C = P xor AES(iv, key)

因為 key 和 iv 是固定不變(單次連線不中斷的情況下)，所以只要同個連線下 AES(iv, key) 是固定的

那我們可以透過暴力窮舉 0 - 255 來求 AES(iv, key) 的值

假設我們先找第一個 byte 的值是多少好了，讓:

C[0] xor (0 ~ 255)
等於: P[0] xor AES(iv, key)[0] xor (0 ~ 255) 

如果剛好和 AES(iv, key)[0] 相同的話就會消掉只剩下 P[0]

因為我們知道 P 一定是英文小寫，所以可以以此判斷是否正確，當然如果你只用一筆資料一定不準

所以可以先收集大量的資料，如果每筆都符合就代表是正確的，這樣就可以暴力找 AES(iv, key) 了

全部找到後，再和 flag 的密文 xor 就等於 flag


```python
#!/usr/bin/env python
# -*- coding:utf-8 -*-
from pwn import *

HOST = '127.0.0.1'
PORT = 1234

r = remote(HOST ,PORT)

p = 'ais3{'

r.recvuntil('decode the cipher:\n')
c = r.recvuntil('\n')[10:-1]
# 因為我知道開頭就是 ais3{ ，所以我就先略過前五個

## 這裡先存 100 筆資料
l = []
for _ in range(100):
	r.sendlineafter('Calcuate the passcode...(Press any key to continue)\n', 'any')
	l.append(r.recvuntil('\n')[10:-1])

## 已經不需要連線了，就先關閉
r.close()

## pn 用來存找到的 AES(iv, key)
pn = []
tmp = True

## k 用來依次找後 27 個AES(iv, key)
## i 窮舉 0 - 255
## for t in l 這邊是比對 xor 出來是否符合再英文小寫範圍
for k in range(0, 54, 2):
	for i in range(256):
		for t in l:
			tt = int(t[k:k+2],16) ^ i
			if tt < 97 or tt > 122:
				tmp = False
				break
		if tmp:
			pn.append(i) 
		tmp = True

## 將 AES(iv, key) xor C = P
for i in range(0, 54, 2):
	p += chr(int(c[i:i+2],16) ^ pn[i/2])

# 97 - 122 # a - z
# ais3{......} # length = 32
```