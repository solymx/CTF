# TUCTF - Notes

## Gr8 Pictures
> ### Description:
> The mysterious hacker 4chan is believed to be passing secret messages hidden in a picture. We know that he connects to gr8pics.tuctf.com:4444 to hide his message in the picture. Your mission, should you choose to accept it, is to find out what message he is trying to hide.

> nc gr8pics.tuctf.com 4444
> If you get connection refused, use nc gr8pics.tuctf.com 41234
> NOTE: the server does not show a prompt, but if the connection is successful, you are at the correct starting point.
> NOTE: without connecting to the server, the flag is theoretically cryptographically impossible to get
> NOTE: If you’re getting a bunch of data that doesn’t seem to stop – it stops after ~3MB of data

題目有給一個 flag.png ，然後連上 server 那邊:
```
echo "flag" | nc gr8pics.tuctf.com 4444
```

可以得到一堆 base64 encode 的東西
```
echo "flag" | nc gr8pics.tuctf.com 4444 | base64 -d > sth
```

可以看到 sth 是一張圖片且跟題目給的 flag.png 很像

所以有可能是其將我們的訊息做 xor 在某些地方，改成
```
python -c 'print "\x00"*100' | nc gr8pics.tuctf.com 4444 | base64 -d > sth.png
```

因為任何東西 xor '\x00' 還是等於自己

故我們把得到的 sth.png 和題目給的 flag.png 做比對，差異就是 key 

再把 key 跟 flag.png 做 xor 就可以得到 flag 


