# ISITDTU CTF 2018 Quals - Notes

## IZ
> Description:
> 
> It's just PHP !!!
> 
> http://35.185.178.212/

urldecode 是比如 %41 = A 這種，就是 ASCII 以十六進制表示

parse_url 是比如 `parse_url("http://xx.com/?name=test", PHP_URL_QUERY);`

會得到 `name=test`

preg_match 的 /i 是表示忽略大小寫


直接:
```
http://35.185.178.212/?%23&_=a
```

就可以 get flag
