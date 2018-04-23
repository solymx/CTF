# pwnable.tw - Notes

## start

保護完全沒開，就會想到 ret2sc，直接用 objdump 看，可以知道大概程式碼是
```c
char buf[20];
write(1, "Let's start the CTF:", 0x14);
read(0, buf, 60);
```

所以可以看到這裡有一個 overflow ，然後 stack 大概整個長相如下，還沒 read 前

```                
            <--- esp    
|0x2774654c|
|0x74732073|
|0x20747261|
|0x20656874|
|0x3a465443|
|ret|
|save esp|
```
而在 ret 前，會先 add esp, 0x14

所以 stack ret 後，會是
```
|0x2774654c|
|0x74732073|
|0x20747261|
|0x20656874|
|0x3a465443|
|ret|
|save esp|   <---- esp

```

所以如果 ret 跳到 mov ecx, esp ，則可以 leak 出 esp 的值，之後再一次 overflow

做 ret2shellcode 即可

## orw
單純寫 x86 的 open-read-write

