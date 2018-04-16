# asis ctf finals 2014 - Notes

## Capsule

解壓縮出來後用 file 看知道是 pcap-ng ，但用 wireshark 打開來說是有損壞

可以用 pcapfix 修復，之後直接 strings

one solution: ```strings fixed.pcap```

two solution: ```strings -n 100 fixed.pcap```

## TicTac

用 Wireshark 打開後，可以看到基本都是 ICMP 

然後我們觀察 data 和其 frame.length 

下 filter: ```icmp && frame.len == 64```

看他的 data 以第一個舉例

用 ```$ echo '37303639363336623230366436353361323034313533' | xxd -r -p | xxd -r -p ```

可以看到: pick me: AS

(如果只用一個 xxd -r -p 看到的是: 7069636b206d653a204153)


觀察一下可以知道前面都是一樣的 7069636b206d653a(pick me:)

把每個轉出來就可以得到 flag



