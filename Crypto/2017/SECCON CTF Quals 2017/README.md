# SECCON CTF Quals 2017

## Vigenere3d

> Description:
> ----- Vigenere3d.py
```python
import sys
def _l(idx, s):
    return s[idx:] + s[:idx]
def main(p, k1, k2):
    s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz_{}"
    t = [[_l((i+j) % len(s), s) for j in range(len(s))] for i in range(len(s))]
    i1 = 0
    i2 = 0
    c = ""
    for a in p:
        c += t[s.find(a)][s.find(k1[i1])][s.find(k2[i2])]
        i1 = (i1 + 1) % len(k1)
        i2 = (i2 + 1) % len(k2)
    return c
print main(sys.argv[1], sys.argv[2], sys.argv[2][::-1])
-----
$ python Vigenere3d.py SECCON{**************************} **************
POR4dnyTLHBfwbxAAZhe}}ocZR3Cxcftw9
```

來看一下他的 code ，第一個參數放 flag ，第二個是 seed ，第三個參數是第二個的反轉
第一個函數
```python
def _l(idx, s):
    return s[idx:] + s[:idx]
```

這個函數是左移，如果輸入 ```_l(1,"abc")``` 則會得到 bca 



光看題目名稱就知道考 Vigenere Cipher 

他是先生成一個表 (t) ，然後看迴圈可以知道，key 總長度是 14 

他用 前 7 個當k1 ，後7 個做 k2 ，而剛好 SECCON{ 也是七個，可以先把 KEY 算出來

有 KEY 就可以直接解密了

## Ps and Qs

考 common factor attack

直接做 gcd 可以得到 p 

之後一樣流程解 c (用 pub1.pub)

## SHA-1 is dead

> Description 
> SHA-1 is dead
> http://sha1.pwn.seccon.jp/
> Upload two files satisfy following conditions:
> 
> file1 != file2
> SHA1(file1) == SHA1(file2)
> SHA256(file1) <> SHA256(file2)
> 2017KiB < sizeof(file1) < 2018KiB
> 2017KiB < sizeof(file2) < 2018KiB
> * 1KiB = 1024 bytes

題目給了一個網站，打開來是給我們上傳用的，蠻友善的XD

![image](https://github.com/solymx/CTF/blob/master/Crypto/SECCON%20CTF%20Quals%202017/img/sha1_upload.png)

依照題目敘述，直接抓 google 找到的那兩個 pdf ，之後利用 LEA 把大小擴展到題目要求的即可
```python
#!/usr/bin/env python
import hashlib
import hashpumpy

a = open('a.pdf').read()
aa = open('aa.pdf').read()
hash = hashlib.sha1(a).hexdigest()
need_number = 2017*1024 - len(a) + 50

_, add = hashpumpy.hashpump(hash, a[-1], 'a'*need_number, len(a)-1)

with open('a','w') as f:
	f.write(a+add)
with open('aa','w') as f:
	f.write(aa+add)
```

之後把得到的 a 和 aa 拿去上傳 ，可以得到

SECCON{SHA-1_1995-2017?}

## Simon and Speck Block Ciphers

> Description
> Simon and Speck Block Ciphers
> https://eprint.iacr.org/2013/404.pdf
> Simon_96_64, ECB, key="SECCON{xxxx}", plain=0x6d564d37426e6e71, cipher=0xbb5d12ba422834b5

簡單看一下題目給的 pdf ， google 找到一個 [github](https://github.com/inmcm/Simon_Speck_Ciphers/tree/master/Python)

大致看一下 github ，寫一個程式爆破
```python
import libnum
import string
from simon import SimonCipher
word = string.printable

plain=0x6d564d37426e6e71
cipher=0xbb5d12ba422834b5
for i in word:
	for j in word:
		for k in word:
			for l in word:
				key = "SECCON{%s}" % (i + j + k +l)
				key = libnum.s2n(key)
				my_simon = SimonCipher(key, key_size=96, block_size=64)
				if cipher == my_simon.encrypt(plain):
					print libnum.n2s(key)
					print key
					raw_input("@")
```
答案: SECCON{6Pz0}

## Very smooth

> Description:
> 
> Decrypt index.html from PCAP.
> Please, submit the flag in the format: "SECCON{" + Answer + "}"
> * Answer is written in index.html

題目給了一個 pcap ，檔案很小，只有 tcp 和 tls 

裡面有三個有 server hello ，隨便選一個如(編號 58) ，對該憑證按右鍵選 export packet bytes

![image](https://github.com/solymx/CTF/blob/master/Crypto/SECCON%20CTF%20Quals%202017/img/s_pcap.png)

把憑證給匯出，或是直接用 network minor 就出來了= =

先用 openssl 轉其格式
```
$ openssl x509 -inform DER -in a.cer -pubkey -noout > key.pub
```

可以看一下 n 和 e 
```
root@lubun:/tmp/p# openssl rsa -pubin -in key.pub -text -modulus
Public-Key: (1024 bit)
Modulus:
    00:d5:46:aa:82:5c:f6:1d:e9:77:65:f4:64:fb:fe:
    48:89:ad:8b:f2:f2:5a:21:75:d0:2c:8b:6f:2a:c0:
    c5:c2:7b:67:03:5a:ec:19:2b:37:41:dd:1f:4d:12:
    75:31:b0:7a:b0:12:eb:86:24:1c:09:c0:81:49:9e:
    69:ef:5a:ea:c7:8d:c6:23:0d:47:5d:a7:ee:17:f0:
    2f:63:b6:f0:9a:2d:38:1d:f9:b6:92:8e:8d:9e:07:
    47:fe:ba:24:8b:ff:df:f8:9c:df:af:47:71:65:89:
    19:b6:98:1c:9e:14:28:e9:a5:34:25:ca:2a:31:0a:
    a6:d7:60:83:31:18:ee:0d:71
Exponent: 65537 (0x10001)
Modulus=D546AA825CF61DE97765F464FBFE4889AD8BF2F25A2175D02C8B6F2AC0C5C27B67035AEC192B3741DD1F4D127531B07AB012EB86241C09C081499E69EF5AEAC78DC6230D475DA7EE17F02F63B6F09A2D381DF9B6928E8D9E0747FEBA248BFFDFF89CDFAF4771658919B6981C9E1428E9A53425CA2A310AA6D760833118EE0D71
writing RSA key
-----BEGIN PUBLIC KEY-----
MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDVRqqCXPYd6Xdl9GT7/kiJrYvy
8lohddAsi28qwMXCe2cDWuwZKzdB3R9NEnUxsHqwEuuGJBwJwIFJnmnvWurHjcYj
DUddp+4X8C9jtvCaLTgd+baSjo2eB0f+uiSL/9/4nN+vR3FliRm2mByeFCjppTQl
yioxCqbXYIMxGO4NcQIDAQAB
-----END PUBLIC KEY-----
```

用 RsaCtfTool 做攻擊
```
root@lubun:/tmp/p# /tool/RsaCtfTool/RsaCtfTool.py --publickey ./key.pub --verbose --private

```

或者用 python 的 library - primefac
```python 
#!/usr/bin/env python 
from Crypto.PublicKey import RSA 
import primefac 
k = RSA.importKey(open('key.pub').read())
n = k.n 
e = k.e 
p = int(primefac.williams_pp1(n))
q = n / p 
```
這樣我們得到 p 和 q 可以用 rsatool 產生 key 

```
# rsatool.py -p 11807485231629132025602991324007150366908229752508016230400000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001 -q 12684117323636134264468162714319298445454220244413621344524758865071052169170753552224766744798369054498758364258656141800253652826603727552918575175830897 -o priv.key
```
之後把 priv.key 匯入到 wireshark 

![image](https://github.com/solymx/CTF/blob/master/Crypto/SECCON%20CTF%20Quals%202017/img/dec_pcap.png)

然後用 export object - HTTP 可以看到有 index.html ，匯出打開來可以看到 flag 

Answer: One of these primes is very smooth.

SECCON{One of these primes is very smooth.}



## Man-in-the-middle on SECP384R1

> Description:
> Steal the conversation between dev0 and dev1.
> Host : mitm.pwn.seccon.jp
> Port : 8000
> 
> sample code for MITM is below.



