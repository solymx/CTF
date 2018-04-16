# Jarvis OJ - Write Up

## Smashes

這題有 Canary 但找不到繞過的方式，但透過 ida pro 可以看到 flag 直接放在程式裡面

那可以透過 SSP leak 的方式，蓋 flag 的位置到 argv[0] 來印出

但可以看到在觸發 canary 保護機制前，他會把放 flag 的地方清掉

但這題有 ELF remapping ，可以在其他位置上找到 flag 的地址


## Tell me Something

可以看到程式裡面有 good_game() 這個函數，會印出 flag

所以就是 buffer overflow 後跳函數即可

## [XMAN]level0

同 Tell me Something ， overflow 後跳函數即可

## [XMAN]level1 

沒有開任何保護，直接將 shellcode 塞到 buf 後跳過去即可

## [XMAN]level2

/bin/sh 和 system@plt 都可以直接在程式上找到

直接構造 rop 即可

## [XMAN]level2(x64)

/bin/sh 和 system@plt 都可以直接在程式上找到

直接構造 rop 即可

## [XMAN]level3

利用 write 來 leak base address 後，算出 system 和 /bin/sh 

之後 ROP

## [XMAN]level3(x64)

這題沒有給 system 

但有給 libc 

然後程式裡面也可以找到 sh

所以就是ret2libc ，用 write leak base address

之後算出 system 後執行 system(“sh”)


