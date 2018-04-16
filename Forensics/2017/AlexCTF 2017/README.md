# AlexCTF 2017 - Notes

## Fore3: USB probing

這題用 foremost 和 wireshark 的 export object 都沒結果

用 binwalk 看可以看到一個 png 

```
$ dd if=./fore2.pcap of=a.png bs=1 skip=62299
```

打開看即有 flag