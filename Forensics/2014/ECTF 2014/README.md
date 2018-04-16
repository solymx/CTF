# ECTF 2014 - Notes

## Pixel Princess

題目給了一個 jpg ，用 binwalk 可以看到裡面藏有一個 zip 

拿出來解壓縮又是一個 jpg ，打開看這個 jpg 顯示一個 Passphrase:BaD_DR4G0N

可是看這個 jpg 沒有藏 zip ，所以用 steghide 看一下

```$ steghide info MarioCastle.jpg  -p BaD_DR4G0N```

他說沒東西，那我們把這個用在最一開始的文件，

```$ steghide extract -sf ./bowser.jpg -p BaD_DR4G0N```

可以得到一個 ```l.tar.gz``` ，解壓縮可以得到一個圖片，打開就是 flag


## H4cker Message

解壓縮後可以得到一個 tcpdump capture file ，先用 binwalk 可以看到裡面有一個 png

```$ dd if=hacker_msg of=flag.png bs=1 skip=69792```

這樣就可以得到 flag 