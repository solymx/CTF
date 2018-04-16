# VolgaCTF 2018 Quals - Notes


## Old Goverment Site
打開登入頁面
![image](./img/WvvtAhf.png)

點旁邊的 about , contact 看網址
```
http://old-government-site.quals.2018.volgactf.ru:8080/page?id=36
```

把其改成
```
http://old-government-site.quals.2018.volgactf.ru:8080/page?id[]=36
```

會報錯，[error_html](./Old_Goverment_Site/err.html)

可以從中知道是使用 ruby