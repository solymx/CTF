# TokyoWesterns CTF 4th 2018 - Notes

## scs7
> Description:
>
> nc crypto.chal.ctf.westerns.tokyo 14791
> Note: You can encrypt up to 100 messages "per once connection".

沒有給檔案，程式執行起來長這樣:
```
root@solymx:/tmp/p/revolutional-secure-angou# nc crypto.chal.ctf.westerns.tokyo 14791
encrypted flag: Ax3nqr4UYimwut22obJLe2ru7CTyjNo44k8tnDuVGXRHRf7NZgxLg3dHG1VoRgS2
You can encrypt up to 100 messages.
message: aaaaaaaaaaaaaaaa
ciphertext: Np6LnXMvDZM4vGXWiKFDme
message: asdasd
ciphertext: 83ArMLmC
message: fdfaf
ciphertext: mQz9zyL
message: asdsds
ciphertext: 83ArgySU
```

[參考這篇](https://ctftime.org/writeup/10861)
寫的很好...

簡單說先測試:
```
root@solymx:/tmp/p/revolutional-secure-angou# nc crypto.chal.ctf.westerns.tokyo 14791
encrypted flag: RNtSuoisUQhefHqqFa92Aqof40mGJTFiiPBHSXfVpbnWnZ4TcYN2YtEWpCVFnY8q
You can encrypt up to 100 messages.
message: 1111
ciphertext: Uverha
message: 1112
ciphertext: UverhB
message: 1113
ciphertext: UverhC
message: aaaa
ciphertext: KpA4dW
message: aaab
ciphertext: KpA4da
message: aaac
ciphertext: KpA4dB
```

古代加密只有兩個
1. 替換:這不可能，因為這樣 1111 加密結果應該都要一樣
2. 移位:這不可能，因為這樣 1111 加密結果應該會像 abcd 或 aaaa

就只剩下 encode ，或者也有可能他是把 移換和替換混合起來

這邊再看另一個:
```
root@solymx:/tmp/p/revolutional-secure-angou# nc crypto.chal.ctf.westerns.tokyo 14791
encrypted flag: QCM65HnThi1DtWRRqms03RHt84VBSrqnncpW6Ytwe9NdNF8r7AC0AMGdeXwqNAjR
You can encrypt up to 100 messages.
message: a
ciphertext: hf
message: b
ciphertext: hK
message: c
ciphertext: hY
message: d
ciphertext: hd
message: e
ciphertext: hm
message: f
ciphertext: hp
message: g
ciphertext: hX
```

這樣看起來應該就是一種 encode ，先找範圍可以知道是 base59 (少了 IOl)

這邊有先寫個 code 看
```
#!/usr/bin/env python
from pwn import *
import string
HOST = 'crypto.chal.ctf.westerns.tokyo' 
PORT = 14791
r = remote(HOST, PORT)

all_str = string.printable

print r.recvuntil('crypted flag: ')
flag = r.recvuntil('\n')[:-1]
print "encrypted flag: ",flag

d = {}

for k in all_str:
	r.sendlineafter('message: ',k)
	r.recvuntil('ciphertext: ')
	d[k] = r.recvuntil('\n')[:-1]
	print "m: %s    || c: %s" % (k, d[k])
r.interactive()
```

然後觀察一下加密規則，大概是先 base59 encode 後，在打亂

或者因為知道是 TWCTF{....} ，一個一個爆破就好


## Revolutional Secure Angou

關鍵點在這行
```
q = OpenSSL::BN.new(e).mod_inverse(p)
```

也就是 `q * e = p * k + 1`，而因為 p > q ，所以 k < e

可以改寫為
```
(q * e - 1 ) / k = p
```

可以做個化簡:
```
n = p * q

=> n  = ((q * e - 1 ) / k) * q 

=> n * k = (q * e - 1 )*q

=> 65537q^2 - q - kn
# 二元一次方程式，可以解
```

或者另一種:
```
qe = 1 + kp

q  = (1 + kp) / e

===

n = p*q

n = p * ((1 + kp) / e)

=> k*p^2 + p - en = 0
```


看 n 可以用 openssl:
```
$ openssl rsa -pubin -in publickey.pem -text
```


最後一個腳本解
```python
#!/usr/bin/env python
# -*- coding:utf-8 -*-
from sympy.solvers import solve
from sympy import Symbol
import libnum
def SolveQuadratic(a,b,c):
	x = Symbol('x')
	return solve(a*x**2 + b*x + c , x)


n = 16809924442712290290403972268146404729136337398387543585587922385691232205208904952456166894756423463681417301476531768597525526095592145907599331332888256802856883222089636138597763209373618772218321592840374842334044137335907260797472710869521753591357268215122104298868917562185292900513866206744431640042086483729385911318269030906569639399362889194207326479627835332258695805485714124959985930862377523511276514446771151440627624648692470758438999548140726103882523526460632932758848850419784646449190855119546581907152400013892131830430363417922752725911748860326944837167427691071306540321213837143845664837111
e = 65537

for k in range(30000,e):
	p, q = SolveQuadratic(k, 1, -e*n)
	print k
	if n % p == 0 or n % q == 0:
		print "yes!!"
		print "p = ",p 
		print "q = ",q
		raw_input("#")
# 跑超久= =
# k = 54080

if p < 0:
	p = n / q 
else:
	q = n / p 

d = int(libnum.invmod(e, (p-1)*(q-1)))
c = libnum.s2n(open("flag.encrypted","rb").read())
m = pow(c,d,n)
print libnum.n2s(m)
```

## Mixed cipher
> Description:
>
> I heard bulldozer is on this channel, be careful!
> nc crypto.chal.ctf.westerns.tokyo 5643





