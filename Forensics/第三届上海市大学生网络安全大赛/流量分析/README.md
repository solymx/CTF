用 wireshark 打開後先看使用那些 protocol ，可以看到有 ftp / http / https 和其他幾個

在 過濾那打  ftp || ftp-data 之後從頭看到尾

可以看到有兩個 flag.zip 和一個 key.log  (可以在第 8110 個封包看到所有)

我先用 foremost pcap 直接得到兩個 zip ，打開發現有加密，有可能是[偽加密](http://blog.xmsec.cc/blog/2016/06/27/ZIP%E4%BC%AA%E5%8A%A0%E5%AF%86/)

用 hexedit 改 zip 偽加密後，有一個可以打開看到

```
flag is not here!!!
maybe you should focus on the encrypted packets......
```

所以應該是要去解 https

先把 key.log 拿出來 (在 tcp.stream eq 58) ，在 import 到 wireshark 裡面

![image](https://github.com/solymx/CTF/blob/master/Forensics/%E7%AC%AC%E4%B8%89%E5%B1%8A%E4%B8%8A%E6%B5%B7%E5%B8%82%E5%A4%A7%E5%AD%A6%E7%94%9F%E7%BD%91%E7%BB%9C%E5%AE%89%E5%85%A8%E5%A4%A7%E8%B5%9B/%E6%B5%81%E9%87%8F%E5%88%86%E6%9E%90/src/1.png)

![image](https://github.com/solymx/CTF/blob/master/Forensics/%E7%AC%AC%E4%B8%89%E5%B1%8A%E4%B8%8A%E6%B5%B7%E5%B8%82%E5%A4%A7%E5%AD%A6%E7%94%9F%E7%BD%91%E7%BB%9C%E5%AE%89%E5%85%A8%E5%A4%A7%E8%B5%9B/%E6%B5%81%E9%87%8F%E5%88%86%E6%9E%90/src/2.png)

把 封包編號 8005 的 zip 拿出來看裡面是一個音訊檔，用 audacity 切到頻譜圖分析可以看到 key

```Key：AaaAaaaAAaaaAAaaaaaaAAAAAaaaaaaa!```

那這個 key 可以解最一開始拿到的 zip ，就可以得到 flag


