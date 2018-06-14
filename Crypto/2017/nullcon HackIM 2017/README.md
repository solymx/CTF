# nullcon HackIM 2017 - Notes

## crypto-question1

給一個 qr code ，先丟到 [zxing](https://zxing.org/w/decode.jspx)

可以得到 `17iUnGoZbFrGS7uU9z2d2yRT9BKgVqnKnn`

這張圖片是源自[BrainWallets](https://brainwalletx.github.io/#generator)

我們有:
1. public key (也就是這張 qr code)
2. 部分的 passphrase


目標: 找到 private key

google 可以知道: [brainwallet's private key is the sha256 of the password](https://filippo.io/brainwallets-from-the-password-to-the-address/)

`private_key = sha256(password)`

換句話說，只要可以找到整串 passphrase ，就可以得到 flag

所以這邊就需要做暴力破解，那看一開始的那張圖片，可以猜測暴力需要的字從 `nullcon8itsgr8` 裡面找 


那這邊已經有一個 [github](https://github.com/dan-v/bruteforce-bitcoin-brainwallet/) 寫好攻擊的程式碼

找到後，再用剛剛的網站[BrainWallets](https://brainwalletx.github.io/#generator)

放入 passphrase 即可


## crypto-question2
> Hint 1 : in the range `(1 to g*q)`, there are couple of pairs yielding common secrete as 399. 
> Hint 2 : 'a' and 'b' both are less than 1000 
> Flag Format: flag{a,b}


因為提示說 a , b 都是小於 1000，直接爆破即可


```python
#!/usr/bin/env python
import itertools

q = 541
g = 10

# pow(g,a,q) = 298
# pow(g,b,q) = 330
# pow(g,a*b,q) = 399

a_list = []
b_list = []
for i in range(1000):
	if pow(g,i,q) == 298:
		a_list.append(i)

for i in range(1000):
	if pow(g,i,q) == 330:
		b_list.append(i)

for i in itertools.product(a_list, b_list):
	tmp = i[0] * i[1]
	if pow(g, tmp, q) == 399:
		print "flag{%d,%d}" % (i[0],i[1])
```

最終答案: `flag{170,808}`



## crypto-question3

這題一開始給了一個 rsa priv key 和一個被加密的訊息，那先解密看看
```
$ openssl rsautl -decrypt -inkey ./HackIM.key -in message.new -out xxx
Enter pass phrase for ./HackIM.key:

```

題目一開始有說密碼是 1 + 五個數字，所以可以很快的去爆破


密碼是 141525


```
$ cat xxx
Now that u r here. Go 2 the digit's page No.["password u found to decrpt the key"],
out of all Logos this Brand (case sensitive) has MD5 : 8c437d9ef6c7786e9df3ac2bf223445e
```

隨便找個解 md5 的網站解出來 clearTax

答案: flag{clearTax}
