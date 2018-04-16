# SECCON CTF 2017 - Notes

## Run me 

> Description:
> -----  RunMe.py
> import sys
> sys.setrecursionlimit(99999)
> def f(n):
>     return n if n < 2 else f(n-2) + f(n-1)
> print "SECCON{" + str(f(11011))[:32] + "}"
> -----

看這個[網站](http://calculus.nctu.edu.tw/upload/calculus_web/maple/Site/carnival/fibonacci/02.htm)

題目要求是費式數列的第 11011 項 = 5505項的平方 + 5506項的平方

可以用這個[網站](https://it.numberempire.com/fibonaccinumbers.php)

結果: SECCON{65076140832331717667772761541872}

## putchar music

> Description:
> This one line of C program works on Linux Desktop. What is this movie's title? 
> Please answer the flag as SECCON{MOVIES_TITLE}, replace all alphabets with capital letters, and spaces with underscores.

```c 
main(t,i,j){unsigned char p[]="###<f_YM\204g_YM\204g_Y_H #<f_YM\204g_YM\204g_Y_H #+-?[WKAMYJ/7 #+-?[WKgH #+-?[WKAMYJ/7hk\206\203tk\\YJAfkkk";for(i=0;t=1;i=(i+1)%(sizeof(p)-1)){double x=pow(1.05946309435931,p[i]/6+13);for(j=1+p[i]%6;t++%(8192/j);)putchar(t>>5|(int)(t*x));}}
```

直接複製上面的然後 ```gcc a.c -o a``` 會說不知道 pow

故幫她加了 ```#include <math.h>``` ，然後 ```gcc a.c -o a -lm```

依照題目敘述，可能是一首歌，用 aplay 來撥音樂

```./a | aplay```

是 [star wars](https://www.youtube.com/watch?v=_D0ZQPqeJkk)

