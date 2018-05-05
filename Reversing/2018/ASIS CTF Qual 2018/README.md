# ASIS CTF Quals 2018 - Notes

## WarmUp

這題抓下來就是一個 c source code ，編譯後，執行他會發現跑很久，觀察 source code

會發現 l() 和 g() 都是沒作用的函數，主要應該是 l() 在拖時間，把她拿掉，就可以立即 show flag 了