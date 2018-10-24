# CSAW CTF Qualification Round 2018 - Notes

## babycrypto
> Description:
>
> yeeeeeeeeeeeeeeeeeeeeeeeeeeeeeet
> 
> single yeet yeeted with single yeet == 0
> 
> yeeet
> 
> what is yeet?
> 
> yeet is yeet

猜謎題...

先 base64 decode 後用 '\xff' 做 xor


## flatcrypto
> Description:
>
> no logos or branding for this bug
>
> flag is not in flag format. flag is PROBLEM_KEY

可以看一下程式碼，他使用 CTR Mode ，所以是一種 stream cipher ，先看一下 counter 的方式

看起來無法去撞他，然後可以發現在加密前，他會先用 zlib 做壓縮，所以可以上網 google 一下

可以找到這一題 `PlaidCTF 2013 – Crypto 250 Compression`

程式碼全部都一樣... ，唯一的差別在這一題的加密的資料是 `FLAG + 我們的輸入`

而 `PlaidCTF 2013 – Crypto 250 Compression` 這題則是 `我們的輸入 + FLAG`

反正簡單講就是如果有相同的，會被 zlib 給壓縮掉，所以得到的加密輸出的長度會比較短

所以可以透過判斷加密出來的長度來判斷是不是有撞到 FLAG 

我的整個流程是:

1. 個別輸入每個可視字元，會發現輸入 `o` 得到的長度最短，所以我們知道最後一個 flag 字元是 o
2. 在 o 前面加一個字元這樣爆，會發現 `go` 得到的最短，以此類推
3. 最終得到答案: `crime_doesnt_have_a_logo`
