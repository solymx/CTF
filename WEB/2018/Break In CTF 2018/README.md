# Break In CTF 2018 - Notes

## Connecting Will

給了一段 code
```php
<?php
/** 
 * Find hashes which match 
*/
if (!array_key_exists('val1', $_POST) || !array_key_exists('val2', $_POST)) {
    echo "Please send the inputs correctly\n";
    exit(0);
}

$first = $_POST['val1'];
$second = $_POST['val2'];

if (!(is_numeric($first) || is_numeric($second))) {
    echo "Invalid input\n";
    exit(0);
}

$hash1 = hash('md5', $first, false);
$hash2 = hash('md5', $second, false);

if ($hash1 != $hash2) {
    $hash1 = strtr($hash1, "abcd", "0123");
    $hash2 = strtr($hash2, "abcd", "0123");
    if ($hash1 == $hash2) {
        // Flag will be echoed here.
    } else {
        echo "Hard luck :(\nKeep trying\n";
    }
} else {
    echo "Hard luck :(\nKeep trying\n";
}

?>
```

一開始的 is_numeric() 判斷是數字或數字的字串

這裡要求 var1 是數字而 var2 不是

之後他們判斷 md5 不是用 ===/!== 所以可以找 0e開頭的

這樣會是 0 == 0

那最後他會用 strtr 轉換，所以我們要找其中一個是 ae 另一個是 0e 這樣就可以

可以來這個[網站查](https://md5db.net/explore/ae46)

