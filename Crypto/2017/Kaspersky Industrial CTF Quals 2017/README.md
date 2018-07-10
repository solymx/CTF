# Kaspersky Industrial CTF Quals 2017 - Notes

## Security Home Cameras

這題給一個圖片說是 png ，但 Header 被改了

正確的 header 應該是 ```89 50 4E 47 0D 0A 1A 0A```

這樣我們把現在加密過的 header 和正確的 header xor 就可以得到 key 就可以解密

xor 後會發現 key = '\xff'

```python
from pwn import *

c = open('sec.png', 'rb').read()
p = xor(c, '\xff')

with open('plain.png', 'wb') as f:
	f.write(p)
```

