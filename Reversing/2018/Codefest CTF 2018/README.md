# Codefest CTF 2018 - Notes

## Doki Doki
> Description:
>
> The literature club has a lot of mysterious things going on lately. Can you find the reason?

> Output Format

> codefestCTF{flag}

基本逆向題目，直接丟 ida pro ，簡單講就是有好幾關，都過了話會給 flag

但你不可以直接作弊用 gdb 跳到最後面，因為每關有些會改到 flag


第一關:
```
int __cdecl checkPoem(char *s1)
{
  sleep(1);
  if ( strcmp(s1, "My head is a hive full of words that won't settle") )
```

第一關答案是: `My head is a hive full of words that won't settle`

第二關在:
```c
int __cdecl checkHiddenMeaning(int a1)
{
  signed int v1; // ST1C_4
  signed int i; // [esp+18h] [ebp-10h]

  v1 = strlen(a1);
  if ( findHidden((char *)a1, v1) != 10 )
    gameOver();
  for ( i = 0; i <= 2; ++i )
    *(_BYTE *)(i + flg) = (*(_BYTE *)(flg + i) + 3) ^ 3;
  *(_BYTE *)(flg + 3) = 50;
  *(_BYTE *)(flg + 4) = 65;
  *(_BYTE *)(flg + 5) = 113;
  return 0;
}
```

`findHidden()` 只是做一個 check ，但不會改到 flg ，所以可以直接用 gdb 通過就好 

第三關在 posterTitle() 裡面的 checkTitle() 裡面的 doSomething() ，其他地方都可以不要理

最後一關 wrapUp() 沒動到 flag ，不會理他
