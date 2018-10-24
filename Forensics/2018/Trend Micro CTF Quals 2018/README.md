# Trend Micro CTF Quals 2018 - Notes


## Forensics-Crypto 1 100
> Description
>
> Here is the full flag, unfortunately it burnt a bit. I know you can handle it with all the things you know.

很明顯是一個要還原 qr code 的題目


使用這個網站來做: [merricx's qrazybox](https://merricx.github.io/qrazybox/)

首先確定 qr code 的 size ，可以看題目的圖片，簡單看一下兩個框框的距離就可以知道是 version 2

之後照著圖片點完後，按 tools -> Reed-Solomon Decoder 可以看到 flag

## DeepDive

題目給了一個 pcap 檔案，直接丟 network minor 讓他幫我們抓出檔案，會發現 

files 有 18 的， image 有 11 個，可是算了一下 files 裡面的圖片檔有 12 個，比對一下會發現

`mausoleum.jpg` 這個不是圖片檔案，是 `pyinstaller exe`

可以使用 [python-exe-unpacker](https://github.com/countercept/python-exe-unpacker)

解出來的資料節中有一個 `mausoleum` ，直接 strings 看答案

