# Pragyan CTF 2018

## Assemble your way to the flag
> Description:
>
> My friend was trying out assembly for the first time, he has no clue what he's doing, help him out and procure your reward in the form of a flag :)

直接 GDB 看

```
b *0x00005555555548cc
r
x/10s $rsp
## 可以看到他有存 flag 進去了
## 一個個看即可
```