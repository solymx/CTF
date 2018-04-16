# 3DSCTF 2017 - Notes

## Optimus Prime

這題把 n 拿去 factordb.com 分解後解 ciphertext 得到 Try harder 

把其中一個質數轉明文可以看到開頭是 PK ，把它存出來得到 zip 檔案

解他要密碼，直接爆破

[別人 write up - 爆破用 john](https://ctftime.org/writeup/8417)

我這裡因為知道密碼是 123123 ，我們改用 fcrackzip 試試看

```
$ fcrackzip -b -c '1' -l 6 -u g.zip

## -b 指定是 brute force
## -c 後面接爆破用的是什麼，1 代表數字， a 代表小寫 ，-c 'a1' 指數字和小寫英文
## -l 接長度， ex: -l 6-10
## -u 後面接要爆的 zip 
```