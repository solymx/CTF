# 34C3 Junior CTF 2017 - Notes

## ecoin

[參考](https://ctftime.org/writeup/8508)

用 binwalk 可以看到有很多東西在裡面，用 foremost 一次拉出來

得到一個 jpg 和 一個有密碼的zip

點開 jpg 可以看到 Pure_Funk << zip 密碼，解壓縮 zip 後

可以得到 hint.pdf ，但在一開始 binwalk 看 pdf 是有兩個 zip 和存有 flag.png 跟 hint.pdf

所以重新回來修一下 foremost 得到的 zip 

```zip -FF ./input.zip --output=output.zip```

相關可以[參考](https://superuser.com/questions/23290/terminal-tool-linux-for-repair-corrupted-zip-files)

再重新一次解壓所可以得到 flag.png


打開 hint.pdf ，會發現好像最上面有東西被截掉，然後中間顯示 ```AngeWouldLoveIt!```

用 binwalk 看是沒東西

那我把他轉成網頁 ```pdftohtml hint.pdf``` ，可以得到 ```AES IV: F01D86CDBB7E1CD88815BEB4106A558C```


```python
#!/usr/bin/env python
from Crypto.Cipher import AES
import libnum

key = "AngeWouldLoveIt!"
iv = libnum.n2s(0xF01D86CDBB7E1CD88815BEB4106A558C)
c = open('flag.png','rb').read()
aes = AES.new(key, AES.MODE_CBC, iv)

with open('output.png','wb') as f:
	f.write(aes.encrypt(c))
```

最後把兩張 png 合併就可以了

## dotr
> Description:
>
> I implemented some crypto and encrypted my secret: 03_duCbr5e_i_rY_or cou14:L4G f313_Th_etrph00 Wh03UBl_oo?n07!_e
> 
> Can you get it back?

## kim

這題給了一個網站和 .py

看一下該網站是

http://35.198.133.163:1337/files/952bb2a215b032abe27d24296be099dc3334755c/?f=sample.gif

往前看該網址
http://35.198.133.163:1337/files/

可以看到有三個檔案
1. flag
2. dont.gif
3. sample.gif

看 CODE 可以知道他考的是 LEA，我們要算出 f=flag 的 sha1 值

現在知道的是 f=sample.gif 的 salt 值是 952bb2a215b032abe27d24296be099dc3334755c

但這裡有一個問題是，我們不知道 secret 的長度是多少

所以網址改成 ?f=sample.gif&f=flag ，然後暴力嘗試 secret 的長度

我本來都是用 hashpump ，不過看 ctftime 的 write up 用 hlextend

感覺比 hashpump 還直觀一點

[參考 1](https://robinverton.de/ctf/34c3-junior-kim-crypto/)
[參考 2](https://github.com/AdityaVallabh/ctf-write-ups/tree/master/34C3%20-%20JuniorsCTF/kim)


## Megalal
> Description:
>
> You can reach a strange authentication system here: nc 35.197.255.108 1337
> 
> I'm sure you know what you have to do.

[參考 CTFTime](https://ctftime.org/task/5145)


這題考 ElGamal ，可以參考 wiki
```
ElGamal encryption is unconditionally malleable, and therefore is not secure under chosen ciphertext attack. For example, given an encryption (c1 , c2) of some (possibly unknown) message m, one can easily construct a valid encryption ( c1 , 2 * c2 ) of the message 2 * m.
```

題目一開始給兩個選單:
1. login
2. register

選 login 要給 token ，如果 role = overlord ，則可以得到 flag
選 register 要給 username 和 role 並會給我們一個 token (不能註冊 role = overlord)

他的 token 是 enc(username#role) 回傳 c1_c2


而一開始維基百科有寫，只要我們偽造 role = n2s("#overlord") / 2 

之後將 c2 * 2 再丟回去即可



