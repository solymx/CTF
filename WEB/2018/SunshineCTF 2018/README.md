# SunshineCTF 2018 - Notes

## Evaluation
> Description:
>
> here's a PHP challenge.
>http://evaluation.web1.sunshinectf.org

這題是 php 代碼審計，直接給我們 src code
```php
<?php 

include "flag.php";
error_reporting(0);
show_source(__FILE__);
$a = @$_REQUEST['hello'];
eval("var_dump($a);");

?>
```

蠻猛的地方在... ，網路上可以找到一模一樣的題目和別人寫好的 write up...

直接參考[這篇](https://blog.csdn.net/wy_97/article/details/77452939)即可，完全一樣

