# RCTF 2018 - Notes

## ECDH
> Description:
>
> nc ECDH.2018.teamrois.cn 42000

[ctftime_writeup](https://ctftime.org/task/6127)


首先連上去
```
# nc ECDH.2018.teamrois.cn 42000

Welcome to my GETFLAG system
1. visit Alice
2. visit Bob
3. about
input here: 3
ECDH.....https://github.com/esxgx/easy-ecc..secp128r1..AES...ECB.......
```
這邊輸入 3 ，可以知道:
1. 曲線是 secp128r1
2. 加密系統是 aes-ecb
3. 考 ECDH

我們這邊看一下 1. visit Alice 和 2. visit Bob

這邊輸入 1
```
Welcome to my GETFLAG system
1. visit Alice
2. visit Bob
3. about
input here: 1

Hello nobody...I'm Alice... you can:
1. ask for flag
2. ask me about my public key
3. ask me about Bob's public key
4. tell me Bob's public key
``` 

這邊輸入 2

```
Welcome to my GETFLAG system
1. visit Alice
2. visit Bob
3. about
input here: 2

Hello nobody...I'm Bob... you can:
1. ask for flag
2. ask me about my public key
3. ask me about Alice's public key
4. tell me Alice's public key
```

我們這邊可以知道，我們可以告訴對方他新的 public key

所以是考[ECDH Man-in-the-middle active attack](https://crypto.stackexchange.com/questions/35603/ecdh-man-in-the-middle-active-attack)


可以看一下和雙方要 flag 的過程
```
Welcome to my GETFLAG system
1. visit Alice
2. visit Bob
3. about
input here: 1

Hello nobody...I'm Alice... you can:
1. ask for flag
2. ask me about my public key
3. ask me about Bob's public key
4. tell me Bob's public key
input here: 1
Bob sent me something.Bob said: Just kidding~

Welcome to my GETFLAG system
1. visit Alice
2. visit Bob
3. about
input here: 2

Hello nobody...I'm Bob... you can:
1. ask for flag
2. ask me about my public key
3. ask me about Alice's public key
4. tell me Alice's public key
input here: 1
I'v already told Alice...bye

Welcome to my GETFLAG system
1. visit Alice
2. visit Bob
3. about
input here: 1

Hello nobody...I'm Alice... you can:
1. ask for flag
2. ask me about my public key
3. ask me about Bob's public key
4. tell me Bob's public key
input here: 1
Bob sent me something.Bob said: 1af4d666e906cd2b34075361daaaa6d61711e33fb6a47e8df99fceaaa8f4770a

``` 

上面的過程是，我先跟 alice 要 flag ，他說 bob 說: Just kidding~ ，然後我們跟 bob 要 flag

bob 說我送過去了，我們再和 alice 要，這邊就會給出加密過的 flag

所以解題過程應該是
1. 先告訴 bob 要更新 alice key 為我們的 key
2. 讓 bob 送 flag 過去
3. 跟 alice 拿 flag
4. 解密 flag


[參考](https://www.johannes-bauer.com/compsci/ecc/)，看曲線參數可以用 Openssl: 
```
$ openssl ecparam -param_enc explicit -conv_form uncompressed -text -noout -no_seed -name secp128r1
```

或者可以直接看這個[網站](http://www-cs-students.stanford.edu/~tjw/jsbn/ecdh.html)

## cpushop
給了 source code 

關鍵點
```python
signkey = ''.join([random.choice(string.letters+string.digits) for _ in xrange(random.randint(8,32))])
payment = 'product=%s&price=%d&timestamp=%d' % (items[n][0], items[n][1], time.time()*1000000)
sign = sha256(signkey+payment).hexdigest()

```

所以是考 Length Extension Attack


然後可以看到他拿參數是用
```
for k,v in parse_qsl(payment):
        if k == 'product':
            product = v
        elif k == 'price':
            try:
                price = int(v)
            except ValueError:
                print 'Invalid Order!'
                return
```

這樣如果你給 product=456&product=123 ，則最終會是 123

所以做法會有兩個
1. 改 price
2. 改 product

我這邊就改 price