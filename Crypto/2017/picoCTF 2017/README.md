# picoCTF 2017 - Notes

## WeirderRSA

這題考模運算

dp = d % p-1


而 d * e = 1 (mod phi )

phi = (p-1) * (q-1)

所以可以寫成 d * e = 1 (mod p-1)

在模運算裡面有一個是:

```(a * b ) (mod n) = [(a mod n)*(b mod n)] mod n```

所以上面可以寫成:

```
[(d mod p-1)*(e mod p-1)] mod p-1 = 1 mod p-1

等於: dp * e = k*(p-1) + 1
```

1 很小忽略不看，dp 比 p-1 小 => e 比 k 大

也就是可以爆破求 k


```python
import libnum

e = 65537
n = 248254007851526241177721526698901802985832766176221609612258877371620580060433101538328030305219918697643619814200930679612109885533801335348445023751670478437073055544724280684733298051599167660303645183146161497485358633681492129668802402065797789905550489547645118787266601929429724133167768465309665906113
dp = 905074498052346904643025132879518330691925174573054004621877253318682675055421970943552016695528560364834446303196939207056642927148093290374440210503657

c = 140423670976252696807533673586209400575664282100684119784203527124521188996403826597436883766041879067494280957410201958935737360380801845453829293997433414188838725751796261702622028587211560353362847191060306578510511380965162133472698713063592621028959167072781482562673683090590521214218071160287665180751

tmp = (dp*e)-1
for k in range(1,e):
	if tmp % k == 0:
		p = tmp / k + 1
		if n % p == 0:
			q = n / p
			if p*q == n:
				phi = (p-1)*(q-1)
				d = libnum.invmod(e,phi)
				print libnum.n2s(pow(c,d,n))


```

## ComputeAES
> Problem:
> 
> Encrypted with AES in ECB mode. All values base64 encoded
> ciphertext = rW4q3swEuIOEy8RTIp/DCMdNPtdYopSRXKSLYnX9NQe8z+LMsZ6Mx/x8pwGwofdZ
> key = 6v3TyEgjUcQRnWuIhjdTBA==

單純練習

```python
#!/usr/bin/env python
from base64 import b64decode as b64d 
from Crypto.Cipher import AES

k = b64d("6v3TyEgjUcQRnWuIhjdTBA==")
c = b64d("rW4q3swEuIOEy8RTIp/DCMdNPtdYopSRXKSLYnX9NQe8z+LMsZ6Mx/x8pwGwofdZ")
print AES.new(k, AES.MODE_ECB).decrypt(c)
```

## SoRandom
> Description:
>
> We found sorandom.py running at shell2017.picoctf.com:16768. It seems to be outputting the flag but randomizing all the characters first. Is there anyway to get back the original flag?
> ---
> $ nc shell2017.picoctf.com 16768
> Unguessably Randomized Flag: BNZQ:449xg472190mwx6869b8pt10rwo92624


因為她的亂數有設種子，所以順序是固定的，簡單拿他 CODE 來改就好
```python
import random,string

flag = "BNZQ:449xg472190mwx6869b8pt10rwo92624"
encflag = ""
random.seed("random")
for c in flag:
  if c.islower():
    #rotate number around alphabet a random amount
    encflag += chr((ord(c)-ord('a')-random.randrange(0,26))%26 + ord('a'))
  elif c.isupper():
    encflag += chr((ord(c)-ord('A')-random.randrange(0,26))%26 + ord('A'))
  elif c.isdigit():
    encflag += chr((ord(c)-ord('0')-random.randrange(0,10))%10 + ord('0'))
  else:
    encflag += c
print "Unguessably Randomized Flag: "+encflag
```

## Broadcast

中國剩餘定理 / Hastad Broadcast attack

## smallRSA

看到 e 很大就可以猜是 wiener attack


https://writeups.amosng.com/2017/picoctf_2017/cryptography/smallsign_140/