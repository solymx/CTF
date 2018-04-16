# 3DSCTF 2017 - Notes

## Wargames

[參考](http://pow270.com/2017-12-18/wargames-3dsctf)

先用 file 看檔案格式，可以知道是 Netpbm image

然後用 hexedit 看 header ，可以看到開頭是 P4

Netpbm 格式有三種:
1. .pbm (P4)
2. .pgm (P5)
3. .ppm (P6)

把它改成其他種用 GIMP 打開看看，就可以看到 Flag	