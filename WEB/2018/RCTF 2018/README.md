# RCTF 2018 - Notes

##　r-cursive
> Description:
>
> LUL dat font
> 
> http://r-cursive.ml
>
> hint: If you get stuck after arbitary code execution, try to escape the sandbox. phpinfo may help you figure out how the sandbox works.

一打開網頁顯示
```
<?php
$token = sha1($_SERVER['REMOTE_ADDR']);
$dir = '../sandbox/'.$token.'/';
is_dir($dir) ?: mkdir($dir);
is_file($dir.'index.php') ?: file_put_contents($dir.'index.php', str_replace('#SHA1#', $token, file_get_contents('./template')));
switch($_GET['action'] ?: ''){
    case 'go':
        header('Location: http://'.$token.'.sandbox.r-cursive.ml:1337/');
        break;
    case 'reset':
        system('rm -rf '.$dir);
        break;
    default:
        show_source(__FILE__);
}
?>
<style>code{font-family: Segoe Script, Brush Script MT, cursive; font-size: 1.337em;}</style>
```

如果在網址後面接 `/?action=go`，會顯示
```
<?php
sha1($_SERVER['REMOTE_ADDR']) === '3726cd2810a1680064202c2bb8ebcfe4b47fca58' ?: die();
';' === preg_replace('/[^\W_]+\((?R)?\)/', NULL, $_GET['cmd']) ? eval($_GET['cmd']) : show_source(__FILE__);
```

其餘可以[參考](https://devcraft.io/2018/05/21/r-cursive-rctf-2018.html)


