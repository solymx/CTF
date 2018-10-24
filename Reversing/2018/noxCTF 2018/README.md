# noxCTF 2018 - Notes

## Guess The String
> Description:
>
> Would you like to test your luck?
> Let's see if you can guess the correct string.
> nc chal.noxale.com 22234

直接丟 ida pro ，看 main() 可以看到他會把我們的輸入丟到一個函數裡面最檢測

然後這個檢測裡面有 11 個檢查:
```c
_BOOL8 __fastcall check(__int64 input, int _n)
{
  char v2; // dl
  char v3; // dl

  return (unsigned int)check1(input)
      && (unsigned int)check2(input)
      && (unsigned int)check3(input)
      && (unsigned int)check4(input)
      && (unsigned int)check5(input)
      && (unsigned int)check6(input)
      && (unsigned int)check7(input)
      && (unsigned int)check8(input)
      && (unsigned int)check9(input, _n, v2)
      && (unsigned int)check10(input)
      && (unsigned int)check11(input, _n, v3);
}
```

先看第一個 check1:
```c
_BOOL8 __fastcall check1(const char *a1)
{
  return strlen(a1) == 11;
}
```

所以長度要是 11，再來看 check2:
```c
__int64 __fastcall check2(_BYTE *a1)
{
  char *v2; // [rsp+0h] [rbp-18h]
  _BOOL4 i; // [rsp+14h] [rbp-4h]

  v2 = a1;
  for ( i = 1; i && *v2; i = check_input_bigger_than_32(*v2++) )
    ;
  return (unsigned int)i;
}
```

這個檢查要求所有的字轉 ascii 需要大於 32，再來看 check3:
```c
__int64 __fastcall check3(char *input)
{
  unsigned int v2; // [rsp+14h] [rbp-4h]

  v2 = 1;
  if ( *input == 'B' )
  {
    v2 = 0;
  }
  else if ( *input * input[1] != 3478 )
  {
    v2 = 0;
  }
  return v2;
}
```

這個要求是第一個字不可是 B ，且第一個乘第二個是 3478，再來看 check4:
```c
__int64 __fastcall check4(_BYTE *input)
{
  unsigned int v2; // [rsp+14h] [rbp-4h]

  v2 = 1;
  if ( ((input[1] ^ *input) ^ input[2]) != 49 )
    v2 = 0;
  return v2;
}
```
這個要求是第一個到第三個字做 xor 答案要是 49 ，再來看 check5:
```c
__int64 __fastcall check5(__int64 input)
{
  unsigned int v2; // [rsp+14h] [rbp-4h]

  v2 = 1;
  if ( *(_BYTE *)(input + 3) > *(_BYTE *)(input + 2) )
  {
    if ( *(_BYTE *)(input + 2) * *(_BYTE *)(input + 2) != *(_BYTE *)(input + 3) * *(_BYTE *)(input + 3) )
      v2 = 0;
  }
  else
  {
    v2 = 0;
  }
  return v2;
}
```

第四個要大於第三個，且第三個的平方的最低位元要等於第四個的平方的最低位元

繼續看 check6:
```c
__int64 __fastcall check6(__int64 input)
{
  unsigned int v2; // [rsp+14h] [rbp-4h]

  v2 = 1;
  if ( isPrime(*(input + 4)) )
  {
    if ( isPrime(*(input + 5)) )
    {
      if ( (*(input + 4) ^ *(input + 5)) != 126 )
        v2 = 0;
    }
    else
    {
      v2 = 0;
    }
  }
  else
  {
    v2 = 0;
  }
  return v2;
}
```

第五和第六個的 ascii 需要是質數，且 xor 後要等於 126，再來看 check7:
```c
__int64 __fastcall check7(__int64 input)
{
  unsigned int v2; // [rsp+14h] [rbp-4h]

  v2 = 1;
  if ( isPrime(*(input + 6) / 2) )
  {
    if ( *(input + 6) != 2 * (*(input + 5) - 42) )
      v2 = 0;
  }
  else
  {
    v2 = 0;
  }
  return v2;
}
```

第七個字元的 ascii / 2 要是質數，且要等於第六個 ascii - 42) 後乘以 2
```c
__int64 __fastcall check8(__int64 input)
{
  unsigned int v2; // [rsp+14h] [rbp-4h]

  v2 = 1;
  if ( *(input + 7) <= 47 || *(input + 7) > 57 )
    v2 = 0;
  if ( 4 * (*(input + 7) >> 2) != *(input + 7) )
    v2 = 0;
  return v2;
}
```

第八個 ascii 範圍需要介在 48 ~ 56 ，且可以被 4 整除，再來看 check9:
```c
_BOOL8 __usercall check9@<rax>(unsigned __int8 a1@<efl>, __int64 a2, __int64 a3)
{
  return *(a3 + 8) == (a1 ^ *(a3 + 7));
}
```

這個要直接看組合語言...，拿別人寫的:
```
The lahf instruction loads the status flags into AH register. Then, the function checks whether the 9th character is equal to (AH xor (8th character)).
```

再來看 check10
```c
__int64 __fastcall check10(__int64 a1)
{
  unsigned int v2; // [rsp+14h] [rbp-4h]

  v2 = 1;
  if ( 2 * *(a1 + 8) != *(a1 + 9) )
    v2 = 0;
  return v2;
}
```

第九個乘以 2 要等於第十個，最後一個 check11 說第十一個要等於第十個乘以第十個 ascii + 1 後除2


以後上看完後，就可以來填空了，最終答案: `J/TtC=&8*TJ`

## Att3nti0n
> Description:
> 
> For this challenge you need your full attention, it will be very helpful ;)
> 
> Note: the flag format for this challenge is slightly different.


