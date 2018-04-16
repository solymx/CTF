# NeverLan CTF 2018 - Notes

## SHA-1

純粹看別人的照做 & 紀錄

[src](https://rot26.team/CTF/NeverlanCTF/2018/passwords/sha1/)

這題只有開頭說第一個是數字

```
$ echo 'admin:05d3693c0781227771b97a9e3cf972d44c2d4439' > hash

$ john -max-len=10 -mask="?d[a-zA-Z0-9]" --format=Raw-SHA1 --fork=32 ./hash
##
## --format 指定 hash type 
## --fork=N fork N processes ，用以分散式運算，加快速度
##
## ?u is uppercase
## ?l is lowercase
## ?d are digits
```

## The WIFI Network
> Description:
>
> So we're still trying to get into the Jedi Archives. Let's try cracking the WiFi. Here's a WPA2 Handshanke I picked up while near the building.

使用 aircrack-ng 做爆破

```
$ aircrack-ng ./neverlan.cap -w /usr/share/wordlists/rockyou.txt
## 
```


## Story Time!
> Description:
>
> Are you ready for a story?
>
> ```-5.;56 76†† ?)8† ;48 3‡0† 2?3 -6.48( ;‡ 46†8 ;48 0‡-5;6‡ ‡1 46) ;(85)?(8 6 5 );‡(: ](6;;8 2: 8†35( 5005 .‡8 6 1053 6) .6(5;8)5*††5338()```


[gold-bug cipher_wiki](https://en.wikipedia.org/wiki/The_Gold-Bug)

[online_tool_decoder](https://dcode.fr/gold-bug-poe)

## Zip Attack
> Description:
>
> We intercepted this encrypted zip. And we noticed it had a file inside that we have previously seen. Will that help you crack it open?

可以到這裡下載 [pkcrack](https://www.unix-ag.uni-kl.de/~conrad/krypto/pkcrack/download1.html)

之後到 src/ 底下，下指令 make 即可

```
$ zipinfo encrypted.zip
Archive:  encrypted.zip
Zip file size: 186312 bytes, number of entries: 3
drwxr-xr-x  3.0 unx        0 bx stor 18-Feb-23 09:53 supersecretstuff/
-rw-r--r--  3.0 unx       34 TX stor 18-Feb-23 09:53 supersecretstuff/flag.txt
-rw-r--r--  3.0 unx   220680 BX defX 18-Feb-23 09:48 supersecretstuff/sw-iphone-wallpaper-first-order.jpg
3 files, 220714 bytes uncompressed, 185662 bytes compressed:  15.9%

$ zipinfo known-file.zip
Archive:  known-file.zip
Zip file size: 185848 bytes, number of entries: 1
-rw-r--r--  3.0 unx   220680 bx defX 18-Feb-23 09:40 sw-iphone-wallpaper-first-order.jpg
1 file, 220680 bytes uncompressed, 185628 bytes compressed:  15.9%

## 可以先用 zipinfo 看zip 裡面的檔案
## 之後用 pkcrack

$ ../pkcrack -C encrypted.zip -c supersecretstuff/sw-iphone-wallpaper-first-order.jpg -P known-file.zip -p sw-iphone-wallpaper-first-order.jpg -a -d clean.zip

```
