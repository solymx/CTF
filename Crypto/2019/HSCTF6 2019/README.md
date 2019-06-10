# HSCTF6 2019 - Notes

## Super Secure System
前言: 沒參加比賽，這邊直接看別人的 write up

看[這篇](https://blog.xarkangels.com/ctf/hsctf6/super_secure_system/)

簡單講就是，給你一個連線服務，然後輸入任何字會吐出加密後的資訊

這時想法有兩個，先看是不是相同的字加密後都一樣

然後發現失敗後，可以知道它應該是同一長度下加密的會相同

所以可以直接爆破

也就是假設密文是 `abcdefgh`

那一開始先輸入第一個字，假設發現 `C` 加密後是 `ab`

之後在 C 加上任意字，發現 `CT` 加密後是 `abcd`

這樣以此類推

## Welcome to Crypto Land
> Description:
> cipher text: KZ6UaztNnau6z39oMHUu8UTvdmq1bhob3CcEFdWXRfxJqdUAiNep4pkvkAZUSn9CvEvPNT5r2zt6JPg9bVBPYuTW4xr8v2PuPxVuCT6MLJWDJp84 

猜謎 .. 答案是 base58


## Massive RSA

給你 n,e,c ，直接用 RsaCtfTool 解

指令:
```python
python RsaCtfTool.py -n [n] -e 65537 --uncipher [c]
```

## Really Secure Algorithm

題目給了 rsa 的 n,e,c

這題重點在考 `p == q` 所以算 phi(n) 會不同

詳細可以參考[這個](https://www.slideshare.net/ssuseraba268/rsa-in-ctf) 第五頁

其他和一般解 rsa 沒什麼區別

