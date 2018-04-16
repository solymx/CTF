# CSAW CTF 2014

## Obscurity

直接 pdftotext 後，就可以看到 flag

## why not sftp?

直接用 foremost ，可以看到裡面有個 zip ，放有 flag.png 

但不知道為什麼 foremost 出來的 zip 是壞掉的

用 network minor 沒把 zip dump 出來 

所以只好用 wireshark 做搜尋

ctrl + f -> 調整 type: hex value ，搜尋上打 "50 4b 03 04" (zip 的 header)

然後找到該封包後 -> follow tcp stream 把它存出來 (格式調成 raw)

這樣打開 zip 看 flag.png 就可以得到答案
 


