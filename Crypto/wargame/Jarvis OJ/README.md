# Jarvis OJ - Notes

> 目錄:
> * [简单ECC概念](#简单ECC概念)
> * [medium_rsa](#medium_rsa)
> * [hard_rsa](#hard_rsa)
> * [very_hard_rsa](#very_hard_rsa)
> * [61dctf_bbencode](#61dctf_bbencode)
> * [61dctf_rsappend](#61dctf_rsappend)
> * [dsa](#dsa)
> * [BrokenPic](#BrokenPic)
> * [神秘的压缩包](#神秘的压缩包)
> * [superexpress](#superexpress)

简单ECC概念
---
> Description:
>
> 已知椭圆曲线加密Ep(a,b)参数为
> 
> p = 15424654874903
> 
> a = 16546484
> 
> b = 4548674875
> 
> G(6478678675,5636379357093)
> 
> 私钥为
> 
> k = 546768
> 
> 求公钥K(x,y)
> 
> 提示：K=kG
> 
> 提交格式XUSTCTF{x+y}(注意，大括号里面是x和y加起来求和，不是用加号连接)
> 注：题目来源XUSTCTF2016


這題是單純算公鑰，看給的參數是質數體，直接帶公式即可

```python
#!/usr/bin/env python
import libnum

G = (6478678675,5636379357093)
P = (0,0)
a = 16546484
p = 15424654874903
k = 546768

def p_add(G,P):
	if G == (0, 0):
		return P
	if P == (0, 0):
		return G
	x1, y1 = G
	x2, y2 = P
	if G == P:
		t = (3*x1*x1+a) * libnum.invmod(2*y1, p)
	else:
		t =  (y2 - y1) * libnum.invmod((x2 - x1), p)
	x = (t*t - x1 - x2) % p
	y = (t*(x1 - x) - y1) % p
	return (x, y)

for _ in range(k):
	P = p_add(G, P)

print "XUSTCTF{%s}" % (str(P[1] + P[0]))
```

medium_rsa
---
n 可以直接分解

hard_rsa
---
看到 e = 2 就會想到 rabin 密碼

[參考](http://www.cnblogs.com/iptables/p/5598049.html)

very_hard_rsa
---

看到 N 相同，e 互質就知道是考共模攻擊


61dctf_bbencode
---

看題目 flag 長度是 32 ，自己測試一下 `flag = "a"*32` ，會發現將加密過的再加密一次，可以得到原本的

所以直接爆破就好，可以這樣是因為他是 xor 


61dctf_rsappend
---

相同 n ，不同 e 且互質，一看就知道是 common modulus attack


dsa
---
> Description:
>
> 签名与验证：
> openssl dgst -sha1 -sign dsa_private.pem -out sign.bin message.txt

> openssl sha1 -verify dsa_public.pem -signature sign.bin message.txt

> 本题的攻击方法曾被用于PS3的破解，答案格式：CTF{x}(x为私钥，请提交十进制格式)


首先可以知道 hash 是 sha1，用 openssl 讀一下簽名的值

```
root@solymx:/tmp/p# openssl asn1parse -inform der -in sign1.bin
    0:d=0  hl=2 l=  45 cons: SEQUENCE
    2:d=1  hl=2 l=  21 prim: INTEGER           :8158B477C5AA033D650596E93653C730D26BA409
   25:d=1  hl=2 l=  20 prim: INTEGER           :165B9DD1C93230C31111E5A4E6EB5181F990F702
root@solymx:/tmp/p# openssl asn1parse -inform der -in sign2.bin
    0:d=0  hl=2 l=  44 cons: SEQUENCE
    2:d=1  hl=2 l=  20 prim: INTEGER           :60B9F2A5BA689B802942D667ED5D1EED066C5A7F
   24:d=1  hl=2 l=  20 prim: INTEGER           :3DC8921BA26B514F4D991A85482750E0225A15B5
root@solymx:/tmp/p# openssl asn1parse -inform der -in sign3.bin
    0:d=0  hl=2 l=  44 cons: SEQUENCE
    2:d=1  hl=2 l=  20 prim: INTEGER           :5090DA81FEDE048D706D80E0AC47701E5A9EF1CC
   24:d=1  hl=2 l=  20 prim: INTEGER           :30EB88E6A4BFB1B16728A974210AE4E41B42677D
root@solymx:/tmp/p# openssl asn1parse -inform der -in sign4.bin
    0:d=0  hl=2 l=  44 cons: SEQUENCE
    2:d=1  hl=2 l=  20 prim: INTEGER           :5090DA81FEDE048D706D80E0AC47701E5A9EF1CC
   24:d=1  hl=2 l=  20 prim: INTEGER           :5E10DED084203CCBCEC3356A2CA02FF318FD4123
```

可以看到 sign3.bin 和 sign4.bin 的 r 一樣 => k 重用

所以我們可以把 k 求出再來求 x



BrokenPic
---
> Description:
>
> 这里有个图片，可是好像打不开？
> Hint1: 图片大小是1366*768


看到檔案名可以知道是 bmp，但少了 file header，可以在網路上找到別人寫的 code
```python

# -*- coding:utf-8 -*-
def header():
    btype='424d' #头标识
    bsize='360c 3000' #大小
    bapp1='0000' #指定应用
    bapp2='0000' #指定应用
    boffset='3600 0000' #偏移量这里是54
    biSize='2800 0000' #位图信息头的大小40
    biWidth='5605 0000' #宽度，本题1366
    biHeight='0003 0000' #高度，本题768
    biPlanes='0100' #颜色平面数，总为1
    biBitCount='1800' #比特数/像素，本题24位
    biCompression='0000 0000' #压缩类型，0为不压缩
    biSizeImage='0000 0000' #图像的大小，本题多少无所谓
    biXPelsPerMeter='0000 0000' #水平分辨率，缺省
    biYPelsPerMeter='0000 0000' #垂直分辨率，缺省
    biClrUsed='0000 0000' #使用的颜色索引数，本题多少无所谓
    biClrImportant='0000 0000' #重要的颜色索引数，本题多少无所谓
    BMPheader=btype+bsize+bapp1+bapp2+boffset+biSize+biWidth+biHeight+biPlanes+biBitCount+biCompression
    BMPheader=BMPheader+biSizeImage+biXPelsPerMeter+biYPelsPerMeter+biClrUsed+biClrImportant
    return BMPheader.replace(' ','')
ciphertext=open('./loss.bmp','rb').read()
f=open('out.bmp','wb')
f.write(header().decode('hex')+ciphertext)
f.close()
```

這樣加上 header 後，可以打開圖片看到 key 和一個很模糊的 qr code

因為 key 是 16 長度，猜是 AES ，然後這模糊程度可以直接猜是 ECB

所以直接拿回最一開始還沒加上 header 的圖片先解密在重新加上 header 打開

就可以看到清楚的 qr code，掃描後就可以得到 flag



神秘的压缩包
---
> Description:
>
> 就不告诉你密码，看你怎么办。
> 注：题目来源XUSTCTF2016


打開壓縮檔的內容可以先猜是 crc32 爆破

這邊有 [6位元的工具](https://github.com/theonlypwner/crc32)

只是這邊是 5 位元，可以[參考這邊](https://github.com/veritas501/hctf_wp/blob/master/misc_level1_big_zip/misc_level1_big_zip.md)


算出來可以得到密碼: `f~Z-;lapEwF\<0ZkhyAo5`


superexpress
---
> Description:
>
> 题目来源：TWCTF2016


來看一下程式碼，可以知道加密是 `a*c + b mod 251` ，這算是 affine cipher

不過這題不同於本來的 affine cipher ，他的參數因為 for 迴圈的關係都亂掉了

所以可以先爆破出 a 和 b ，之後窮舉所有的字元作加密判斷是否和題目的密文一樣，是就代表找到了。