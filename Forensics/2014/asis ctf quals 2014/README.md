# asis ctf quals 2014 - Notes



## forensic

用 Wireshark 打開後，Export Objects -> HTTP

然後用大小作排列之後會看到最大的檔案是 myfile

把她 export 出來後是一個 pcap 但是打不開要修復

可以使用 pcapfix

Linux 安裝:
```$ apt install pcapfix```

使用:
```$ pcapfix myfile.pcap```

之後打開這個 pcap ，搜尋 flag 會發現有三個符合

用 Follow TCP Stream 看可以知道是 postscript ，把她 直接 export 出來 
(格式預設是 ascii ，要改成 raw)

之後其中一個打開來會看到 flag 

## Prying ears

用 Wireshark 打開後，一個個看封包，看到第 195 個是 dns 詢問 89504e47040a1a.asis.io

89 50 4E 47 0D 0A 1A 0A 這是 png 的 file header 

那我們就開始收集 asis.io 前面這些怪怪的 hex

可以用 wireshark 的 filter 下:
```dns && ip.src == 192.168.110.2 && ip.dst == 192.168.11.4  && frame.len == 98```

直接用 tshark 過濾:
```
$ tshark -r a.pcap -2R 'dns && ip.src == 192.168.11.4 && ip.dst == 192.168.110.2 && frame.len == 98' -T fields -e _ws.col.Info | awk '{print $6}' | grep '.asis.io' > filter.txt

===
tshark 指令:
-r : 指定要讀的檔案
-R : 把用在 Wireshark 上面的 filter 放過來，但我這樣下會出錯，提示要加 2 ，所以上面是 -2R
-T : 選類型，我這裡選 fields ，要搭配 -e 選要顯示的，而我要看 info 

```

可以得到:
```
89504e470d0a1a.asis.io
0a0000000d4948.asis.io
44520000010a00.asis.io
00000d08030000.asis.io
006667d0f70000.asis.io
0069504c544500.asis.io
e60072700efe04.asis.io
00000000000001.asis.io
2a3eeec8cf4439.asis.io
00000000000002.asis.io
00000000000003.asis.io
f804c1e6864f3e.asis.io
00000000000004.asis.io
00000000000005.asis.io
00000000000006.asis.io
00000000000007.asis.io
49dff9906d15ae.asis.io
00000000000008.asis.io
0147ec1ee7b987.asis.io

...
...
```

把前面拿出來改好後

```xxd -r -p filter.txt flag.png```

打開即可看到 flag


## Sound Zoo

這題是一個 mp3 檔案，用 Audacity 打開來聽會發現他走得很緩慢

所以把他調快一點

Effect -> Change Tempo -> 1100 %

