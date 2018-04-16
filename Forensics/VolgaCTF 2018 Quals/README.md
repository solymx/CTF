# VolgaCTF 2018 Quals - Notes

## The Colors - Listen!
> Description:
>
> Look at these images. See the music.

不懂 stegsolve 拉出資料的機制 = = ，單純照別人 [write up](https://ctftime.org/writeup/9372) 做

留個紀錄...

## Master
> Description:
>
> We've found one of C&C servers that controlled recent DDoS attack, however we can't get credentials.
> 
> http://master.quals.2018.volgactf.ru:3333
> 
> Also, we've got a communication traffic dump between C&C servers.
> 
> https://quals.2018.volgactf.ru/files/9fbdd4dc5135f43ca537e9be33991ce5/capture.pcap
> 
> Can you get in?

用 wireshark 簡單看一下，一開始有 ssh ，後面是 arp 和 mysql 

先在 filter 那邊下 : mysql ，可以看到每個 response 都是 user.password

可以用 tshark 下指令拉出來找找，不過直接用 find 找 admin 也可以

之後丟到網站上就可以得到 flag

