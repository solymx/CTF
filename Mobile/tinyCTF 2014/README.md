# tinyCTF 2014 - Notes


## Ooooooh! What does this button do

先用 [dex2jar](https://github.com/pxb1988/dex2jar) 轉 classes.dex 為 .jar
```
$ ./d2j-dex2jar.sh /tmp/p/classes.dex
```

.jar 實際上也是 zip ，直接解開，在 ctf/crackme/ 可以看到 FlagActivity.class

可以用 [jad](http://www.cnblogs.com/EasonJim/p/7868030.html) 把 .class 轉 java code

這樣打開轉換一下，就可以看到 flag 了