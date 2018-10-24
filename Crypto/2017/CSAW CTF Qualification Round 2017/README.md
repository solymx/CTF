# CSAW CTF Qualification Round 2017 - Notes

## Almost Xor
> Description:
>
> Can you decode this ciphertext?
> 
> `809fdd88dafa96e3ee60c8f179f2d88990ef4fe3e252ccf462deae51872673dcd34cc9f55380cb86951b8be3d8429839`



## Another Xor
> Description:
>
> Receiving a python script that encrypts a string using a user-chosen key, and an encrypted message- try to get the flag.

看 code 很簡單，第一個參數當 key

設 x = 第二個參數 + key

則 plaintext = x + md5(x)

之後將 key  xor plaintext = ciphertext

首先我們可以知道 plaintext 長度為 105 和她讓 key 補長到 137

且第二個參數開頭應該是 `flag{` 這樣可以先求出 key 的前五個 bytes: `A qua`

接下來就是要先想辦法知道 key 的長度，因為答案應該會是: `flag{.}` 最少會是 7

換句話說 key 長度應該會是 7 - 98 之間
```python
#!/usr/bin/env python
from pwn import *

k = 'A qua'
# c is ciphertext and cc is c[:105]

for i in range(98):
	print "now i: ",i
	tmp = k + "\x00"*i
	k_len = len(tmp)
	c_tmp = cc[-k_len:]
	gg = xor(tmp, c_tmp)[:5]
	if '\x00' in gg:
		print i 
		print
		raw_input()
```

從這裡可以看到有可能是: 15, 37, 38