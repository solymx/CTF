# 34C3 CTF 2017 - Notes

## chaingang 
> Description:
> send 1505 szabo 457282 babbage 649604 wei 0x949a6ac29b9347b3eb9a420272a9dd7890b787a3

可以參考[以太币(Ether)的单位](https://zhuanlan.zhihu.com/p/28994731)

根據題目敘述， wei, szabo, babbage 都是以太幣的單位

所以後面那個可以假設是地址，去 [etherscan](https://etherscan.io/address/0x949a6ac29b9347b3eb9a420272a9dd7890b787a3)

看 block 是 4809285 [這個](https://etherscan.io/tx/0x70e9f6de87a7db0fe5eb5c93c8b51413c017cdb51d4a8d82f91a0aaca6eb8939)

點旁邊的 Tool&Utilities => Parity Trace 

```
 {
    "action": {
      "callType": "call",
      "from": "0xa77a10bc57819f6334d35d05de07ced2fc14e3e8",
      "gas": "0x43fc8",
      "input": "0x2a0f7696000000000000000000000000000000000000000000000000000000000000c1cb",
      "to": "0x949a6ac29b9347b3eb9a420272a9dd7890b787a3",
      "value": "0x0"
    },
    "blockHash": "0xd631f4f92c10adc3b1e6797fb80b5ea2f86e4a88e00d7e9086fa7d0dd52d94c4",
    "blockNumber": 4809285,
    "result": {
      "gasUsed": "0x326",
      "output": "0x333443335f6772616e646d615f626f756768745f736f6d655f626974636f696e"
    },
    "subtraces": 0,
    "traceAddress": [],
    "transactionHash": "0x70e9f6de87a7db0fe5eb5c93c8b51413c017cdb51d4a8d82f91a0aaca6eb8939",
    "transactionPosition": 2,
    "type": "call"
  }
]
```

把 0x333443335f6772616e646d615f626f756768745f736f6d655f626974636f696e 轉 ascii 
```python
import libnum
print libnum.n2s(0x333443335f6772616e646d615f626f756768745f736f6d655f626974636f696e)

## 34C3_grandma_bought_some_bitcoin
```

