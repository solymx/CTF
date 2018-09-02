# asis ctf final 2014 - Notes

## lion-cub

直接開檔案會失敗

用 strace 看可以知道需要在當前目錄下放 flag

然後執行程式他會依你的 flag 產生一個 flag.enc

然後看一下可以知道他是 enc[i] = plain[i] ^ plain[i+1]

而這樣可以知道最後一個 byte 不會加密，不然會 overflow

所以可以以此來反推出整個 plaintext

enc[i] = p[i] ^ p[i+1]

所以:

p[i] = enc[i] ^ p[i+1]

所以寫個腳本解
```python

c = open('flag.enc','rb').read()[::-1]
p = c[0]
for i in range(1,len(c)):
	p += xor(c[i], p[-1])
p = p[::-1]
with open("plaintext","wb") as f:
	f.write(p)
```

解出來可以得到一張 flag.png 是 qr code

丟去 [webiste](zxing.org)

解出來得到
```
1f8b0808928d2f540003666c61672e706e67000192016dfe89504e470d0a
1a0a0000000d494844520000006f0000006f0103000000d80b0c23000000
06504c5445000000ffffffa5d99fdd0000000274524e53ffffc8b5dfc700
0000097048597300000b1200000b1201d2dd7efc0000012449444154388d
d5d431ae84201006e079b1a0d30b90cc35e8b8925e40e5027a253aae41e2
05b0a320ce1bb2bbef651b87668b25167e0501867f007a1bf01d4c004be8
76af0150e449650a71087aa1067afee9762aa36ae2a8746f7523674bbb2f
4de4250c12fd6ff2867cde2968fefe8e7f431e17943af155d81b26d06068
b3dd661a68d005987cfc219997e23b8ab3c24bc9a4808e3acab4da065204
a541e166506402e4592ec71148e499cbe0f914b42a99c91eb59221824591
e4613475b9dd93c804e4087a13472bf3ac05e7781f6b0b0326551be77147
02b35e38540a0064f2481c6fc2d3cbe4c472bc5dd613c9e45e98a10c19cf
576bdc915b9213cbbb524d9c88d73ab667ad44d667e419957b72ffdace79
bc8ccc47fff696eb2ff3734feea7f80bb686232e7a493424000000004945
4e44ae426082fb73fb8e92010000
```

把這個存檔後用 `xxd -r -p ` 來轉換可以得到另一個 qr code

在丟去上面網站可以得到 flag


## Numdroid

題目給了一個 apk 檔案



