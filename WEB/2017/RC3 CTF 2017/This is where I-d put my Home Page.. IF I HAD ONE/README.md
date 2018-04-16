# RC3 CTF 2017 - Notes

## This is where I'd put my Home Page.. IF I HAD ONE

>problem:

>This page won't seem to load.. what is happening???????? - Joker
>13.59.6.98:80

>Note: Flag is not in RC3-2017{} format



打開該網頁會看到網址一直跳

改用 curl 看一下 

```
root@lubun:~# curl 13.59.6.98:80
<meta http-equiv="refresh" content="0; url=C.html" /> <p hidden>R</p>
```

可以看到他會不斷跳轉，阿後面有一個 hidden ，把她取出來連起來就是 flag

簡單寫個 python 跑一下

```python
import urllib2
hidden = 'hidden='
url = 'http://13.59.6.98/'
response = urllib2.urlopen(url)
html = response.read()  
print "html: ",html
start = html.find('url=') + 4
end = html.find('html')
next = html[start:end] + 'html'
print url + next
hidden_num = html.find('</p>\n')
hidden += html[hidden_num-1]
print hidden 

while(True):
	response = urllib2.urlopen(url + next)
	html = response.read()  
	print "html: ",html
	start = html.find('url=') + 4
	end = html.find('html')
	next = html[start:end] + 'html'
	print url + next
	hidden_num = html.find('</p>\n')
	hidden += html[hidden_num-1]
	print hidden 
```

![image](https://github.com/solymx/CTF/blob/master/WEB/RC3%20CTF%202017/This%20is%20where%20I-d%20put%20my%20Home%20Page..%20IF%20I%20HAD%20ONE/src/1.png)


把存的 hidden 值拿來看一下

RC3W3MUS7G0D33P3RR3D1R3C777RC3W3MUS7G0D33P3RR3D1R3C777RC

後面開始重複了，所以 flag 是: RC3W3MUS7G0D33P3RR3D1R3C777