# H1-702 CTF 2017 - Notes

android level 1 ~ level 4 的 apk 是相同的

## Android level 1

單純的基本逆向題目

Linux 上使用 [ReverseAPK](https://github.com/1N3/ReverseAPK)

```
$ reverse-apk a.apk > out
```

然後看一下 out ，可以看到有
```
inflating: /tmp/p/a.apk-unzipped/assets/tHiS_iS_nOt_tHE_SeCrEt_lEveL_1_fiLE
```
看一下檔案格式，可以知道是 jpg ，打開就是 flag

## Android level 2

