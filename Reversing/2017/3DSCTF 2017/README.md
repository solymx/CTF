# 3DSCTF 2017 - Notes

## Scared Flag

題目給了一個 .hex ，用 hex2bin 轉 binary
```
hex2bin -b xxx.hex
```

之後用 strings
```
$ strings xxx.bin
#+$+%+a
f'w'
33 44 53 7B 62 79 20 4A 75 6C 69 6F 20 44 65 6C 6C 61 20 46 6C 6F 72 61 7D
33 44 53 7B 52 45 41 4C 4C 59 20 4D 52 2E 20 46 55 5A 5A 45 52 3F 20 49 73 20 74 68 61 74 20 61 6C 6C 20 79 6F 75 27 76 65 20 67 6F 74 3F 7D
if you can scare me...
I'll run away and leave the flag for you
not even close
I'm not scared yet
pretty scary, I left the flag here, you can catch

```

把上面的字串轉文字看看
```python
flag = [0x33,0x44,0x53,0x7B,0x62,0x79,0x20,0x4A,0x75,0x6C,0x69,0x6F,0x20,0x44,0x65,0x6C,0x6C,0x61,0x20,0x46,0x6C,0x6F,0x72,0x61,0x7D]
print ''.join(map(chr,flag))
```

可以看到答案

## Ransomware

> Description:
>
> WARNING! DON'T EXECUTE THIS SAMPLE IN YOUR OWN PERSONAL MACHINE!!!

這題給了一個惡意軟體讓我們分析


