# id0-rsa.pub - Notes

## Cut and Paste Attack On AES-ECB

簡單說就是給你三個明文和其對應的密文，
然後請你構造出 “Deposit amount: One million dollars”的密文是什麼


三個明文密文對分別是
```
m1 = Deposit amount: 5 dollars
c1 = 0x5797791557579e322e619f12b0ccdee8802015ee0467c419e7a38bd0a254da54
m2 = One million dolls is quite the collection
c2 = 0xb1e952572d6b8e00b626be86552376e2d529a1b9cafaeb3ba7533d2699636323e7e433c10a9dcdab2ed4bee54da684ca
m3 = Hey nice binoculars
c3 = 0x35d0c02036354fdf6082285e0f7bd6d2fdf526bd557b045bce65a3b3e300b55e
```

所以我們只要取 c1 的前 16 bytes 加上 c2 的前 16 bytes 加上 c3 的後 16 bytes 就是答案

```
5797791557579e322e619f12b0ccdee8b1e952572d6b8e00b626be86552376e2fdf526bd557b045bce65a3b3e300b55e
``` 

## Intro to RSA
題目給我們:
```
(e, N) = (0x3, 0x64ac4671cb4401e906cd273a2ecbc679f55b879f0ecb25eefcb377ac724ee3b1)
d = 0x431d844bdcd801460488c4d17487d9a5ccc95698301d6ab2e218e4b575d52ea3
c = 0x599f55a1b0520a19233c169b8c339f10695f9e61c92bd8fd3c17c8bba0d5677e
```

求 m 的 hex 沒前面的 0x

直接 `pow(c, d, n)` 即可

## Ps and Qs
感覺是超 seccon qual 2017 的吧@@

很單純的 common factor attack 

## AES-CTR with Nonce Reuse


ctr mode 的加密: c = aes(iv, key) xor p

而今天題目說 key 和 iv 都相同了，設 aes(iv, key) = x

則:
c1 = x xor p1
c2 = x xor p2
所以:
c1 ^ c2 = p1 ^ p2

這樣可得到 p1 ^ p2 ，然後題目說答案有很多種，要想辦法猜出 p1 , p2 @@

[參考](https://github.com/rahiel/id0-rsa.pub/blob/master/04-AES-CTR-with-nonce-reuse.py)

懶得想了...

## CCA on Textbook RSA

給我們一個公鑰，然後可幫我們解密任何訊息，但不可以解密 flag 的密文

剛好 [ctf wiki](https://ctf-wiki.github.io/ctf-wiki/crypto/asymmetric/rsa/rsa_chosen_cipher/) 有

根據 wiki: 作法

1. 先找一個和 n 互質的數: 2 , x = 2
2. 算 y = (pow(x, e, n) * c ) % n
3. 把 y 拿去給他解密得到 z = pow(y, d, n)
4. p = z * invmod(x, n) (mod n)
