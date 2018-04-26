# pwnable.tw - Notes

> 目錄:
> * [start](#start)
> * [orw](#orw)
> * [calc](#calc)
> * [dubblesort](#dubblesort)
> * [Silver_Bullet](#silver_bullet)
> * [hacknote](#hacknote)
> * [criticalheap](#criticalheap)

start
---
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

orw
---
單純寫 x86 的 open-read-write

calc
---
保護:
```
    Arch:     i386-32-little
    RELRO:    Partial RELRO
    Stack:    Canary found
    NX:       NX enabled
    PIE:      No PIE (0x8048000)
```

丟到 ida 來看 src code，一開始將輸入丟到 get_expr() 做檢測，

只允許 + , - , * , / , % 和數字，之後再給 parse_expr() 處理

整個漏洞在處理數字和邏輯時，可以 overflow

dubblesort
---
這題保護全開，先丟 ida pro ...

一開始先輸入，之後丟給 sort() 做氣泡排序，之後給結果

這題因為他不會限制你可以輸入幾個數字，所以可以 overflow

起始位置在
```
lea     edi, [esp+1Ch]
mov     esi, 0
```

canary 放在 esp+0x7c 的地方
```
mov     eax, large gs:14h
mov     [esp+7Ch], eax
```

所以可以知道，輸入第 24 個會蓋到 canary ，第 32 個會蓋到 ret (ebp+4)


而這題考的 trick 是 scanf("%u") ，如果給他 + ，則不會蓋到本來記憶體的地方

這樣就可以 overflow 來控 eip 


然後在最一開始輸入名字的地方
```
  read(0, buf, 0x40u);
  __printf_chk(1, "Hello %s,How many numbers do you what to sort :");
```
他的 printf("%s") ， %s 是吃到 \x00 結束，而我們輸入 user 進去會是 user\n

所以他會繼續印到 \x00 為止，然後他位址是在 esp+0x3c ，也就是他會一直印 64 個 bytes

或中間出現 \x00 為止，會有這漏洞是因為他的 name 並沒有先清零

用 gdb 看一下，在他旁邊是一個 f7 開頭的，應該可以透過相對位置

來獲取 libc 的位址 ，之後就是跳 system('sh')

system 位址一定比 sh 還小，不過偶爾 canary 比這兩個大就會失敗

Silver_Bullet
---
有給 libc 且保護只有 NX 和 FULL RELRO ，應該是 ret2libc 且不可以 GOT Hijack


這題應該有個結構是
```c
{
    char buf[48];
    int length;
}
```

漏洞在 strncat 在串接後會補零，所以一開始我們先 create 一個長度是 47 的 bullet

之後用 power_up() 在串一個字進去，則因為 strncat 自動補零的關係，會蓋到 length

使其變成 0 ，這樣在 power_up() 一次可以把它改很大，來 beat 成功並造成 overflow

這裡 rop 先做 leak 之後再返回 main 重做一次，跳 system('sh') 來 get shell 


hacknote
---
用 ida pro 看，在 delete_note() 中
```
 if ( *(&ptr + idx) )
  {
    free(*((void **)*(&ptr + idx) + 1));
    free(*(&ptr + idx));
    puts("Success");
  }

```

free() 掉沒設 NULL，所以有 Use After Free

而在 add_note() 中，每新增一個chunk ，會先 malloc 0x8

前 0x4 指向一個用來印出內容的函數，後 4 byte 存指向其 content 的 pointer


簡單思路是，add 兩個 fastbin ，content 大小不可以是 16 ，假設 content 給 24 好了

(x86 下，最小分配 16 bytes, x64 則是最小分配 32 bytes)

(他雖然一開始是 malloc(8) ，但實際上分配 16 bytes)

這樣heap 上應該是
```
+-------------------------+
|    note_0 : 16 bytes    |
+-------------------------+
|    content_0 : 32 bytes |
+-------------------------+
|    note_1 : 16 bytes    |
+-------------------------+
|    content_1 : 32 bytes |
+-------------------------+
```
之後 delete 這兩個 chunk 後，在新增一次並把 content 大小設為 16

這時就可以蓋到 note_0 上指向函數的位址了

所以第一次可以先 leak ，之後再用 system 來 get shell

不過這邊要看一下 print_note()
```
  if ( ptr[v1] )
    (ptr[v1]->function_ptr)(ptr[v1]);
```

他傳入的是 note* 本身，所以蓋成 system 後，執行的是 note* 自身

而 system 的參數是可以用 ; 或 || 這種，比如


```
system("gg ; sh");
or
system("gg || sh");
```

所以 leak 完後，再 delete_note(2) 一次，給大小 8 ，content 為

system_addr + "||sh" 即可


criticalheap
---

有三個結構

漏洞:
1. 程式在一開始先用 ```srand(time(0))``` 來初始化
```
	v0 = time(0LL);
	srand(v0);
```
我們可以創建 clock_heap ，如果夠快或許可以抓到時間，
```
	timer = time(0LL);
	h->d.clock.timestamp = (__int64)localtime(&timer);
```

然後 system_heap 的 rand()，就可以預測了

2. localtime 和 setenv 配合，就可以將任意文件寫到 heap 上了

這是本題考的 trick ，因為有 localtime ，所以可以透過

設定 TZ 這個環境變數來載入任何檔案到 heap 中，再搭配 fmt vuln 的任意讀來獲取 flag

3. chunk_system 的 detail 在 offset 0x20， chunk_normal 的 content 在

offset 0x18 的位置，content 讀取時沒有截斷，而detail 在 stack 上，

所以可以 leak heap

4. normal_heap 的 play 有一個 printf_chk 的 format string vuln
```
if ( v1 == 1 )
    {
      printf("Content :");
      _printf_chk(1LL, (__int64)&a1->d);        // format string vuln
```

配合 normal_heap 的 play 的 change_content 就可以在 stack 上留下東西

然後來任意位址讀，因為他用的是 printf_chk() ，所以不能用 %n 作任意位址寫


紀錄幾個程式地方:

程式中，在 playsystem()
```
if ( setenv(s, value, 0) )
            puts("Failed !");
          else
            puts("Done !");
```

man 裡面有說明
```
setenv(const char *name, const char *value, int overwrite);

  The  setenv()  function  adds  the variable name to the environment with 
  the value value, if name does not already exist.  If name does exist in the
       environment, then its value is changed to value if overwrite is nonzero;
        if overwrite is zero, then the value of name is not changed  (and  setenv()
       returns a success status). 
```
簡單講，這題的 overwrite 給 0 ，也就是如果我們要改已經存在的 env ，必須先 unset 才可以
，直接改不行


程式中有用到 strdup() ，在一開始 create_heap() 中
```
    char name[168];
    printf("Name of heap:");
    readline(name, 160u);
    Heaps[i].name = strdup(name);
```
看一下 man
```
char * strdup(const char *s);

他會先用 malloc 分配一個和 *s 一樣大小的空間，並且把 *s 的內容複製到該空間後，之後再把該地址返回。

傳回的空間要記得之後用 free()

*重點: 他會用到 malloc()*
```


整個解題步驟:
1. 先 leak heap base
2. 設定環境變數 TZ 和 TZDIR ，將文件載入到 heap 中
3. format string vuln 做任意讀


