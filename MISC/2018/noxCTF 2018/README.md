# noxCTF 2018 - Notes

## Marcode
> Description:
>
> Marcode (Mr. Code in Hebrew), Ineed your help!
> I got a movie but I cant see it. It hypnotizes me.
> please help me!
> yours,
> Gveretcode (Mrs. Code in Hebrew)
> 
> P.S.
> change NOXCTF to noxCTF.
> https://drive.google.com/open?id=1GkalBntU1s6d_sw_S5I4GinD8hBrh-C-

這題給了一個影片 (mp4)，先用 ffmpeg 拉出 frame
```
$ ffmpeg -i Marcode.mp4 -r 25 -f image2 'img-%03d.png'
# -i 指定檔案
# -r fps
# -f 強迫輸出的檔案格式 image2 for png
```

這樣可得到超多 qr-code ，然後打開裡面是一個 google drive 連接到一張圖片

那就每個打開來看看
```python
#!/usr/bin/env python
import requests
from bs4 import BeautifulSoup
import sys, zbarlight
from PIL import Image


for i in range(1,3491):
	with open("img-%03d.png" % i,'rb') as f:
		image = Image.open(f)
		image.load()
	res = zbarlight.scan_codes('qrcode',image)
	r = requests.get(res[0])
	soup = BeautifulSoup(r.text, 'html.parser')
	print (soup.title)
```
