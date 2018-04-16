# Angstrom CTF 2018 - Notes

## OFB
> Description:
>
> defund made a simple OFB cipher, if you can even call it that. Here's the [source](./OFB/encrypt.py) and the [encrypted flag](./OFB/flag.png.enc).

首先看一下加密程式，流程:
1. 讀取 flag.png ，如果長度不足 4 的倍數，就在尾部補 \x00 
2. 分組，一個 block 的長度是 4
3. p32( u32(block[i]) ^ x ) ## x 透過 lcg 產生

但最一開始的數值我們不知道，之道就可以解密了

而我們知道他是 png ，其前面 16 個是一樣的
```
89 50 4E 47    0D 0A 1A 0A    00 00 00 0D   49 48 44 52
```

而 x 的算法是

```
x[n + 1] = (a * x[n] + c) % m
```

我們缺少 a 和 c ，但因為我們已經知道最一開始的 4 個 block ，所以可以試著反推一下

```
x[0] = 0x89504e47 ^ u32("\x18\x9amE")

所以可以得到 x[0] = 2445943554
這樣依次推出:

x[0] = 2445943554
x[1] = 2225636917
x[2] = 1320590709
x[3] = 4196912501
===
求 a:

x[1] = a * x[0] + c (mod m)
x[2] = a * x[1] + c (mod m)
把上述式子代換一下:
x[2] - x[1] = a*x[1] - a*x[0]
=> x[2] - x[1] = a(x[1] - x[0])
=> a = (x[2] - x[1]) / (x[1] - x[0]) (mod m)
=> a = 3204287424
=> 這邊是 模數除法，要注意一下

備註:
假設 5 / 2 (mod 7) ，會等於是 5 * (2 在 mod 7 的乘法反元素) 之後再 mod 7
=> (5 * libnum.invmod(2,7)) % 7
===
求 c:

有 a 就可以求 c ，直接把式子轉一下即可

x[1] = a * x[0] + c (mod m)
=> c = x[1] - a*x[0] (mod m)
=> c = 1460809397

===

最初始的三個數字 a , c , x[0] 都有後，就可以求解了
(基本都複製他的 code 即可)

#!/usr/bin/env python
from pwn import *

import struct

def lcg(m, a, c, x):
        return (a*x + c) % m

m = pow(2, 32)
c = 1460809397
a = 3204287424
x = 2445943554

d = open("flag.png.enc").read()

d = [d[i:i+4] for i in range(0, len(d), 4)]

e = ''
for i in range(len(d)):
        e += struct.pack('>I', x ^ struct.unpack('>I', d[i])[0])
        x = lcg(m, a, c, x)

with open('flag.png', 'w') as f:
        f.write(e)
        f.close()
```


