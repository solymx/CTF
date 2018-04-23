# DEFCON CTF Quals 2015 - Notes

## r0pbaby
這題程式裡面就給我們 libc addr 和 可以任意求任何函數位置

而選項 3 會將我們輸入的放到 ebp 中，換句話說，只要在蓋 8 個後

就會蓋到 ret 了

所以現在就缺 pop rdi ; ret 和 sh\x00

sh\x00 直接用 gdb-peda 在裡面 find '/sh\x00' 求其和 libc 的相對位置即可

我找 pop rdi ; ret 怪怪的，一直找不到，所以先 leak 兩個函數後，去網路上找

libc database 來下載，之後 ```objdump -D -M intel ./libc```

因為我們知道 "pop rdi ; ret" = 5f c3

可以在裡面找到，並求其和 libc addr 的相對位置即可


