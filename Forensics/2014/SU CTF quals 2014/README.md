# SU CTF quals 2014 - Write Up

## Hear With Your Eyes

直接用 Audacity 開起來轉頻譜圖就好

![image](https://github.com/solymx/CTF/blob/master/Forensics/SU%20CTF%20quals%202014/src/hear_with_your_eyes_1.png)

## Recover Deleted File

```
root@lubun:/tmp/p# binwalk disk-image

DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
0             0x0             Linux EXT filesystem, rev 1.0, ext3 filesystem data, UUID=bc6c2b24-106a-4570-bc4f-ae09abbdabbd
1160          0x488           Unix path: /root/recover-deleted-files/stuff/fs
65536         0x10000         Linux EXT filesystem, rev 1.0, ext3 filesystem data, UUID=bc6c2b24-106a-4570-bc4f-ae09abbdabbd
66696         0x10488         Unix path: /root/recover-deleted-files/stuff/fs
72704         0x11C00         Linux EXT filesystem, rev 1.0, ext3 filesystem data, UUID=bc6c2b24-106a-4570-bc4f-ae09abbdabbd
73864         0x12088         Unix path: /root/recover-deleted-files/stuff/fs
1113088       0x10FC00        ELF, 64-bit LSB executable, AMD x86-64, version 1 (SYSV)

root@lubun:/tmp/p# dd if=./disk-image of=flag bs=1 skip=1113088

root@lubun:/tmp/p# chmod +x ./flag
root@lubun:/tmp/p# ./flag
your flag is:
de6838252f95d3b9e803b28df33b4baa
```

## Avatar

他說有藏訊息到 jpg 裡面，然後 outguess 可以從 jpeg 中提取裡面的隱藏訊息

```
root@lubun:/tmp/p# outguess -r lamb.jpg flag.txt
Reading lamb.jpg....
Extracting usable bits:   28734 bits
Steg retrieve: seed: 94, len: 41

root@lubun:/tmp/p# cat flag.txt
We should blow up the bridge at midnight
```

## What is this

給兩個圖片，用 Stegsolve -> Analyse -> Image Combiner 即可

## Hidden Message

用 wireshark 打開 pcap ，可以看到 80 個 udp 的封包

每一個 src port 是 3401 和 3400 ，把 3401 當成 0 和 3400 當成 1

用 python 直接跑
```python
msg = [0b01001000,0b01100101,0b01101001,0b01110011,0b01100101,0b01101110,0b01100010,0b01100101,0b01110010,0b01100111] 

print ''.join([chr(i) for i in msg]) 
```

## Network Traffic

我直接把 pcap 拉到 network minor 中，可以看到所有的檔案都是 index.html

然後有一個 source host 上寫的是 95.211.183.24[flag.com:8080]

把這個 index.html 打開來看可以看到

```find the ip of this server. Flag is md5(ip)```

