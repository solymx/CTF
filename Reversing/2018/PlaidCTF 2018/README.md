# PlaidCTF 2018 - Notes

## coconut
> Description:
>
> My compiler is a coconut...
>
> Warm-up at coconut.chal.pwning.xxx:5548
> 
> Main at coconut.chal.pwning.xxx:6817

先來看一下 Warm-up，連上去的樣子是

```
Testing a93605fa1b190e5fdb29b6754525ac4f, threshold required <= 10
Function to optimize:
1       .globl  myfunction
2       myfunction:
3       pushq   %rbp
4       movq    %rsp, %rbp
5       movl    $1930534792, -20(%rbp)
6       movl    $-643475228, -16(%rbp)
7       movl    -16(%rbp), %eax
8       movl    -20(%rbp), %edx
9       andl    %edx, %eax
10      movl    %eax, -12(%rbp)
11      movl    -16(%rbp), %eax
12      movl    %eax, -8(%rbp)
13      movl    -8(%rbp), %eax
14      movl    -20(%rbp), %edx
15      xorl    %edx, %eax
16      movl    %eax, -4(%rbp)
17      movl    -8(%rbp), %eax
18      popq    %rbp
19      ret
<<<EOF>>>
Input on each line either a single line number to remove or a range to remove.
A range is represented by "N-M", where lines N to M (inclusive) are the lines to remove.
A line is represented by "N", where N is the line number to remove.
A single "#" represents the end of input.

Example:

    A range deleting lines 10 to 14

    10-14

    A remove a single line 100

    100

Example input:

4
5
10-15
18-20
28
#

Note: Line numbers to delete can only be >=5 and <=17:
```

就是要優化，然後只可以刪掉 >=5 和 <=17 這個 range 裡面的 code

且最終剩下的行數需要 <= 10，看 AT&T 真的噁心，就先人工轉 intel ，大概如下

```
push rbp 			
mov rbp, rsp			
mov [rbp-20], 1930534792	// delete
mov [rbp-16], -643475228	
mov eax, [rbp-16]			// delete
mov edx, [rbp-20]			// delete		
and eax, edx				// delete
mov [rbp-12], eax			// delete
mov eax, [ebp-16]			
mov [rbp-8], eax			
mov eax, [rbp-8]			// delete
mov edx, [ebp-20]			// delete
xor eax, edx				// delete
mov [rbp-4], eax			// delete
mov eax, [rbp-8]
pop rbp
ret
```

所以可以刪掉的是 5, 7-10, 13-16，最終連上去如下 (只貼最後一小部分)
```
Note: Line numbers to delete can only be >=5 and <=17:
5
7-10
13-16
#
Processing Deletions...
Compiling...
Running...
Result: a93605fa1b190e5fdb29b6754525ac4f:Success!
Congrats! Your flag is PCTF{iN3ffic1eent__A5m_K1ll5}
```


## APLunatic
> Description:
> 
> APL (ˌæ'pɪel) n. A Programming Language 
> See: http://tryapl.org/ 
> https://tio.run/#apl-dyalog 
> https://ngn.github.io/apl/ 
> 
> lunatic (ˈluːnətɪk) n. A person who is insane 
> See: APL Programmers 
> 
> aplunatic (ˌæpluːnətɪk) n. This challenge 
> 
> 4o6VSU/ihpAw4ouEJ0JJRcKwP8K9PklMwr1FLiEhPEUhOkU4NMKlwrjCskUyM8OFOMK7OTY4J3t74o21KH7ijbUpLydzdWNjZXNzJyAnZmFpbCd94oqDKCsv4o26PeKOlVVDUyAxMyt7Ky/ijbUv4oy9MirijbPijbTijbV9wqgsLzMzIDjijbQoOMOX4o204o21KeKNtDfijL3ijYkoLeKMiijijbQnZjB4dHIwdCcpw7cyKeKMveKNiTExIDI04o204oiKe2HiiaA44oaRKDAsYeKGkCg44o20MiniiqTijbUpfcKo4oy94o6VVUNTIOKNtSk94o204o26fSdJTlBVVCBIRVJFJwo=


[參考](https://monosource.github.io/writeup/2018/05/08/plaidctf-aplunatics/)
[ctftime](https://ctftime.org/task/6084)

