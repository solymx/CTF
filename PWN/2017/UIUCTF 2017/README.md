# UIUCTF 2017 - Notes

## goodluck

看 ida pro 漏洞:
```
__isoc99_scanf("%ms", &format);
...
...
printf(format);  // fmt vuln
```

直接 %9$s 即可

可以直接 gdb 然後
b printf
r
輸入 123456

之後看 stack 上面的位置，會發現flag 在 123456 下面第三個

因為 x64 前六個是暫存器，第七個是 format ，所以可以算出是第九個

也可以用 angelboy 的 pwngdb 下 fmtarg 來看
```
fmtarg 0x7fffffffe498
```
