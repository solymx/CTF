# nullcom HackIM 2018 - Notes

## What did he said?
> Description:
>
> Decrypt RSA

描述寫 rsa ，直接看他給的 zip ，有兩把 key 和一個密文

看這兩把 key 的 n 不同，直接 gcd 發現不是 1 ，代表是 common factor attack

接下來直接解密即可，用 key1 不行 ，用 key2 可以

[solve.py](./solve.py)
