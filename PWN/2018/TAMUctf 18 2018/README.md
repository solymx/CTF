# TAMUctf 18 - Notes

## pwn1
用 checksec 可以看到只有開 DEP

用 IDA PRO 看
```
int __cdecl main(int argc, const char **argv, const char **envp)
{
  char s; // [sp+5h] [bp-23h]@1
  int v5; // [sp+1Ch] [bp-Ch]@1

  setvbuf(_bss_start, (char *)2, 0, 0);
  puts("This is a super secret program");
  puts("Noone is allowed through except for those who know the secret!");
  puts("What is my secret?");
  v5 = 0;
  gets(&s);
  if ( v5 == -267929071 )
    print_flag();
  else
    puts("That is not the secret word!");
  return 0;
}
```

用 gets() 有 overflow ，然後蓋到 v5 ，將其改成 -267929071 即可

## pwn2

這題跟第一題差不多，只是從蓋變數改成蓋 eip 跳函數而已

```
$ python -c 'from pwn import * ; print "a"*243+p32(0x0804854b)' | nc pwn.ctf.tamu.edu 4322
```

## pwn3

一開始可以看到完全沒任何保護，然後跟第二題差別在沒函數可以跳

然後一開始又告訴我們 buffer 的位址，所以很明顯是 return to shellcode


## pwn4

這題只開 DEP ，且可以直接找到 sh 和 system@plt

所以可以直接開shell

[exploit.py](./pwn4/exploit.py)

## pwn5

這題的漏洞在 change major 中，用的是 gets() 可以 overflow 來做 rop

然後他是 statically linked ，有足夠的 gadget

所以一開始先讓程式執行到 change major 那，然後 overflow 後 rop 來 get shell

[exploit.py](./pwn5/exploit.py)




