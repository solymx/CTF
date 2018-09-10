# hackme.inndy.tw - Notes

## not hard
> Description:
>
> Nm@rmLsBy{Nm5u-K{iZKPgPMzS2I*lPc%_SMOjQ#O;uV{MM*?PPFhk|Hd;hVPFhq{HaAH<
> Tips: pydoc3 base64

python3 比 python2 多了 base64.b85decode ，所以可以試試看

```python
import base64
a = 'Nm@rmLsBy{Nm5u-K{iZKPgPMzS2I*lPc%_SMOjQ#O;uV{MM*?PPFhk|Hd;hVPFhq{HaAH<'
a = base64.b85decode(a)
a = base64.b32decode(a)
```

## classic cipher 2	
> Description:
>
> Solve this vigenere cipher

太長用 quipqiup.com 沒結果改用另一個 https://www.guballa.de/vigenere-solver

Key 長度是 51 @@ ...

## easy AES
> Description:
>
> Can you encrypt things with AES?
> Tips: What is symmetric cipher?

看 code 很好理解，一開始給你第一把金鑰，要求你解密密文: `Good Plain Text!`

解出密文的明文是第二把金鑰，就可解出其圖片


## one time padding
> Description:
>
> You will never see flag?!

直接看程式碼有一句話是
```php
// X ^ 0 = X, so we want to avoid null byte to keep your secret safe :)
```

意思是說，她為了不要有 null byte ，所以 random 出來的東西不會有和 flag 一樣的字元，

那只要窮舉每個字元 `0-255` ，看哪個沒出現就知道了 

## login as admin 2
> Description:
>
> Please login as admin.
> Tips: length extension attack

提示已經說明要考 Length Extension Attack 了，先來看一下 code






