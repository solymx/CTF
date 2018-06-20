# CCTF 2016 - Notes

## pwn3

一開始先用 ltrace 看一下，可以知道他會把我們的輸入移位 1 個，之後要等於 `sysbdmin`

所以一開始要輸入 `rxraclhm`


然後用 IDA PRO 看一下，可以看到在get_file() 裡面有一個

```
return printf(&dest); // fmt vuln
```
