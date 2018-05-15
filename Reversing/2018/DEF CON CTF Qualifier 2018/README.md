# DEFCON CTF Qualifier 2018 - Notes

## ELF Crumble

[參考](https://www.serraabak.com/notes/DefconCTFQuals-RE-ELF-Crumble)，寫得蠻好的

直接執行會記憶體錯誤
```
root@solymx:/tmp/p/pieces# ./broken
Segmentation fault (core dumped)
```

用 `objdump -d -M intel ./broken` 可以看到 main() 裡面只有 `pop eax`

其他還有四個函數: f1(), f2(), f3(), recover_flag() 都是 `pop eax`

f1() range: 0x5ad ~ 0x6e8 (315)
f2() range: 0x6e9 ~ 0x72d (68)
f3() range: 0x72e ~ 0x7a1 (115)
recover_flag() range: 0x7a2 ~ 0x7db (57)
main() range: 0x7dc ~ 0x8d3 (247)
所以總共有 807 個 

而題目給的 fragment ，總共也是 807 個，所以應該是填空遊戲
```
root@solymx:/tmp/p/pieces# wc fragment_*
  0   2  79 fragment_1.dat
  0   1  48 fragment_2.dat
  0   7 175 fragment_3.dat
  0   1  42 fragment_4.dat
  0   2 128 fragment_5.dat
  0   1  22 fragment_6.dat
  4   5 283 fragment_7.dat
  0   1  30 fragment_8.dat
  4  20 807 total
```

想要看 fragment 可以用 `$ objdump -D -M intel -m i386 -b binary fragment_8.dat`

或是 pwntools
```
from pwn import *
frag = open("frag1", "rb").read()
print disasm(frag)
```

那我們知道一個函數的開頭會是
```
push ebp
mov ebp, esp
sub esp, xxx
```
結尾會是
```
leave
ret
```

所以像是 fragment_1.dat 的 0x3 ~ 0x47 剛好就是一個函數，且長度是 68，所以可以知道就是 f2()

然後全部裡面只有 fragment_8.dat 的開頭是 `push ebp; mov ebp, esp` 所以可以知道他是第一個

這題可以這樣一個個解出來，或者直接爆破


```
#!/usr/bin/env python
import binascii
import itertools
import os

a = binascii.hexlify(open("a","rb").read())
f = [open("fragment_%d.dat" % i, "rb").read() for i in range(1,9)]

start_pop_eax = "5858"
end_pop_eax = "8b04"
start_idx = a.index(start_pop_eax)
end_idx = a.index(end_pop_eax)
begin = a[0:start_idx]
end = a[end_idx:]

for sub in itertools.permutations(f):
	total = binascii.unhexlify(begin) + ''.join(sub) + binascii.unhexlify(end) 
	with open("final", "wb") as out:
		out.write(total)
	os.system("chmod +x ./final")
	os.system("./final >> output")
	os.system("rm ./final") 	
```


