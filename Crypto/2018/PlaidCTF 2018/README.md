# PlaidCTF 2018 - Notes

## Macsh
> Description:
> 
> Forget ssh, this is a much more secure shell. 
> Server running at macsh.chal.pwning.xxx:64791


一開始輸入
```
    mac, cmdline = input().split('<|>')
    cmd, *args = cmdline.split()
```

所以需要輸入如 `mac<|>cmdline`

然後如果希望程式執行指令，須滿足

```
if cmd == "tag" or bytes.hex(fmac(k0, k1, encode(cmdline))) == mac:
    eval(cmd)(*args)
```

也就是要滿足:
1. cmd == "tag"
2. fmac(k0, k1, encode(cmdline)) 要是正確的 mac

可以看一下 mac 的產生方式
```
def fmac(k0, k1, m):
    C = AES.new(k1, AES.MODE_ECB)
    bs = [C.encrypt(xor(b, f(k0, i))) for i,b in enumerate(to_blocks(m))]
    return reduce(xor, bs, b"\x00" * N)

def f(k0, i):
    return to_block(rot(to_int(k0), i % (8 * N)))
```

重點可以看到它是 ECB Mode ，也就是每個 block 都是獨立的，可以想到的攻擊是 `cut and paste`

不過這題不是，但他這邊用的是 xor 且每個 block 獨立，他的 `f(k0, i)` ，是把每個 block 做 xor

所以我們可以做 `a xor a xor b = b` 這種把東西消掉的方式來解 

然後另一個點是在 f(k0, i) ，他把 i = index 作為key 去加密，他的 range = 8 * N = 128

也就是給他到 129 == 1  (一個 block = 16 , 所以總共要給 16 * 8 = 2048)


[參考](https://ctftime.org/task/6064)

