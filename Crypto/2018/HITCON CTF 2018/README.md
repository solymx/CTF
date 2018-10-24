# HITCON CTF 2018 - Notes


## Lost Modulus
> Description:
>
> I lost my modulus. Can you find it for me?
> 
> nc 13.112.92.9 21701




## Lost Key
> Description:
>
> I lost my public key. Can you find it for me?
> 
> nc 18.179.251.168 21700


首先看程式碼，可以知道他一開始會先在 flag 前加 68 個垃圾才加密

之後把 flag 用 rsa 加密後的結果給我們，然後給我們 150 次來下指令:

1. 輸入十六進制的數字，會幫我們轉回文字，然後加密印給我們
2. 輸入十六進制的數字，會幫我們轉回文字，然後解密，但只會回傳給我們兩個字

其實光從這個行為大概就可以猜到要考`LSB Oracle` 

然後這題沒給我們 n 和 e @@














