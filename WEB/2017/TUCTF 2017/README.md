# TUCTF 2017 - Notes

## Git Gud

[參考](https://github.com/HackThisCode/CTF-Writeups/tree/master/2016/InternetWache-CTF/web80)

dump 下來後

可以在 http://gitgud.tuctf.com/.git/logs/refs/heads/master

看到
```2c6190537a2655121ccb9647765fa99687afec25 4fa0acbccd0885dace2f111f2bd7a120abc0fb4e Jimmy <jimmy@jimmyrocks.site> 1511297220 +0000	commit: Added flag```


所以 git checkout 4fa0acbccd0885dace2f111f2bd7a120abc0fb4e

就可以看到 flag

cat flag 即可

## Cookie Harrelson

[取自](http://k3ramas.blogspot.tw/2017/11/tuctf-2017-web-challenges.html)

打開頁面只有一張圖片

![image](https://github.com/solymx/CTF/blob/master/WEB/TUCTF%202017/images/cookieharrelson_hompage.png)

題目說明 cookies ，然後用 chrome 的 editThisCookie 沒看到啥有趣的

看 Request/Response header

![image](https://github.com/solymx/CTF/blob/master/WEB/TUCTF%202017/images/cookieharrelson_startcookie.png)

可以看到 Set-cookie 那邊有一個 base64 encode 的訊息，decode 出來是 cat index.txt #

所以用 burpsuite 改封包把 base64 encode 那邊的訊息換成

cat index.txt # cat flag 的 base64 encode 就可以看到 flag


## iFrame and Shame

[取自](http://k3ramas.blogspot.tw/2017/11/tuctf-2017-web-challenges.html)

題目描述

![image](https://github.com/solymx/CTF/blob/master/WEB/TUCTF%202017/images/iframe_challenge.png)

使用:
```"; echo $(ls) #```

可以得到

![image](https://github.com/solymx/CTF/blob/master/WEB/TUCTF%202017/images/iframebroke!.png)

要看 flag ，所以修改成: ```"; echo $(cat flag) #```

![image](https://github.com/solymx/CTF/blob/master/WEB/TUCTF%202017/images/iframe_flagget.png)


