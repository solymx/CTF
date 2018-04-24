# Timisoara CTF 2018 Quals - Notes

## SSS Part 1
> Description:
> 
> 3 math teachers agreed to a common secret password to access the exam answers. Luckily, one of them lost a note that seems related. They also talk all the time about some guy named Lagrange.
>
> NOTE: the coordinates are: 4612c90f5d8cd5d616193257336d92af1f66df92443b4ee69f5c885f0173ad80113844e393d194e3 8c25921e46b03e48b7cbe94c3267f41adf618abd16422f660b59df6fae81e8aff2242852be33db49 d2385b2d2fd3a6bb597ea041316255869f5c35e7e8490fe5775736805b9023dfd3100bc1e89621af

用 [python_library](https://github.com/blockstack/secret-sharing)

```python
from secretsharing import SecretSharer

text = ['1-4612c90f5d8cd5d616193257336d92af1f66df92443b4ee69f5c885f0173ad80113844e393d194e3','2-8c25921e46b03e48b7cbe94c3267f41adf618abd16422f660b59df6fae81e8aff2242852be33db49','3-d2385b2d2fd3a6bb597ea041316255869f5c35e7e8490fe5775736805b9023dfd3100bc1e89621af']

print SecretSharer.recover_secret(text).decode('hex')
```

## SSS Part 2
[參考](https://ctftime.org/task/5917)


## Not Your Average RSA
這題考多質數 rsa ，以實務面來說，可以透過 crt 做加速

但相對質數越多越不安全，也可以用一般的方式解密，只是沒加速效果而已

我這邊就用最一般的方式解就好，有[write up](https://github.com/diogoaj/ctf-writeups/tree/master/2018/Timisoara/crypto/NotYourAverageRSA) 用 CRT 解，可以參考

## Hush Hush

如果輸入兩個不同的字串，卻有相同的 md5 ，則給我們 flag

他的 hash 算法是
```
def my_hash(x):
    global n
    x += "piper"
    x = int(x.encode('hex'), 16)
    for i in range(32):
        x = pow(x, x, n)
        x +=1
    m = md5.new()
    m.update(hex(x))
    return m.hexdigest()
``` 

他會先將輸入和 piper 串接起來後，轉數字做 x^x mod n 之後做 md5

我們可以發現 '\x00piper'.encode("hex") 和'piper'.encode("hex") 是相同的

所以我們可以輸入 '' 和 \x00 即可


