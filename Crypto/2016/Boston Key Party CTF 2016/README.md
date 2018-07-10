# Boston Key Party CTF - Notes

## des-ofb-2

這題考 des 的 weak key，如果不考慮校驗位，des 總共有 8 個弱密碼

可參考 [wiki](https://en.wikipedia.org/wiki/Weak_key)

弱密碼即是 E(E(M)) = M

故一個個嘗試即可解掉

```python
#!/usr/bin/env python
from Crypto.Cipher import DES

iv = '13245678'
k = '\xE1\xE1\xE1\xE1\xF0\xF0\xF0\xF0'
des = DES.new(k, DES.MODE_OFB, iv)
c = open("ciphertext").read()
print des.decrypt(c)

```

