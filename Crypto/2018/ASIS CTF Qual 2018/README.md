# ASIS CTF Quals 2018 - Notes

## Uncle Sam

考 [Schmidt-Samoa Cryptosystem](https://en.wikipedia.org/wiki/Schmidt-Samoa_cryptosystem)

給一張圖片 = =... ，使用 [online_ocr](https://www.onlineocr.net/)

如果知道是考 Schmidt-Samoa Cryptosystem 這個就很簡單

但這次不知道，但根據題目給的資訊，有 n 和 d 和 e = n

所以可以思考的方向是，如果 e = n 會不會有啥攻擊，但沒結果

另一個思考方向是，透過 d 和 e 解 n

可以看這篇 [RSA: how to factorize N given d](https://www.di-mgt.com.au/rsa_factorize_n.html)

這樣可以獲取 p 和 q ，而有了 p , q 要怎解 ```pow(m,p*p*q,p*p*q)```

從這邊要思考一下 rsa 解密的證明

```
因為 ed ≡ 1 + kϕ(N)

然後歐拉函數的一個基本是 3^13471 mod 11 可以先算 ϕ(11) = 10，13471 % 10 = 1

所以可以寫成 3^1 mod 11 = 1，知道這兩個就可以證明 rsa 的解密

C = m^e mod n 

C^d mod n = m^ed mod n 

那我們知道 ed mod ϕ(N) = 1 ，所以可以知道 m^ed mod n = m^1 mod n = m
```

所以當我們得到 p , q 之後，一樣要想辦法做到 rsa 本來解密的那樣

這題是 `m^(p*p*q) mod p*p*q` ，那 `mod p*p*q` 等同於 `mod p*q` 

所以一樣，我們希望可以寫成 `m^ϕ(N) mod N`

所以本來 RSA 公式是
```
ed ≡ 1 mod ϕ(N)

右邊確定是  mod ϕ(N)

而本來是 m^p*p*q ，左邊給 pq

可以寫成 d*(pq) ≡ 1 mod ϕ(N) 等於 d*(pq) = 1 + kϕ(N)

所以計算 c^(d*d*q) mod pq = m^p*p*q*q*d*d mod pq = m^1 mod pq = m
```

## OPEC

這題考 [Okamoto–Uchiyama cryptosystem](https://en.wikipedia.org/wiki/Okamoto%E2%80%93Uchiyama_cryptosystem)

這題 `N = p*p*p` ，所以可以很簡單的獲取 p

有 p 就直接照著 wiki 解密即可

```python
import libnum

l = lambda x: (x-1) / p

m = (l(pow(c,p-1,p*p)) * libnum.invmod(l(pow(g,p-1,p*p)), p)) % p
print libnum.n2s(m)
```



