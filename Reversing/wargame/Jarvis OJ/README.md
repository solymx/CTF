# Jarvis OJ - Notes


## DD - Hello
> Description:
>
> Flag 是下一关的邮箱地址（以 DD 开头）。

先看格式，用 file
```
1.Hello.12b9bde7c0c8558a9da42aa1798cafc8: Mach-O 64-bit x86_64 executable, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|PIE>
```
 
丟 ida 看看，直接看關鍵函數

```
int sub_100000CE0()
{
  int result; // eax@1
  signed int v1; // [sp+1Ch] [bp-14h]@2
  int v2; // [sp+24h] [bp-Ch]@1

  v2 = ((start - sub_100000C90) >> 2) ^ byte_100001040[0];
  result = sub_100000DE0();
  if ( !(result & 1) )
  {
    v1 = 0;
    while ( v1 < 55 )
    {
      byte_100001040[v1] -= 2;
      byte_100001040[v1] ^= v2;
      ++v1;
      ++v2;
    }
    result = printf("\nFinal output is %s\n", &byte_100001040[1]);
  }
  return result;
}
```

所以直接解 while 裡面的算式就好

先算出v2 的初始值
```
__text:0000000100000C90 sub_100000C90   proc near               ; CODE XREF: start+20p
__text:0000000100000C90                                         ; DATA XREF: sub_100000CE0+Fo ...

可以知道 
sub_100000C90 = 0x100000C90 

__text:0000000100000CB0 start           proc near               ; DATA XREF: sub_100000CE0+8o
__text:0000000100000CB0                                         ; sub_100000CE0+34o

可以知道
start = 0x100000CB0

然後 byte_100001040[0] = 0x41 

可以算 k = 73
```

之後寫一個 python 解
```python
flag = [0x41, 0x10, 0x11, 0x11, 0x1B, 0x0A, 0x64, 0x67, 0x6A, 0x68, 0x62, 0x68, 0x6E, 0x67, 0x68, 0x6B, 0x62, 0x3D, 0x65, 0x6A, 0x6A, 0x3D, 0x68, 4, 5, 8, 3, 2, 2, 0x55, 8, 0x5D, 0x61, 0x55, 0x0A, 0x5F, 0x0D, 0x5D, 0x61, 0x32, 0x17, 0x1D, 0x19, 0x1F, 0x18, 0x20, 4, 2, 0x12, 0x16, 0x1E, 0x54, 0x20, 0x13, 0x14, 0x0, 0x0]

k = 73
i = 0
while(i < 55):
	flag[i] = flag[i] - 2
	flag[i] = flag[i] ^ k
	i = i + 1
	k = k + 1
print ''.join(chr(i) for i in flag)

```


## FindKey

一樣先看檔案格式
```
./a: python 2.7 byte-compiled
```

所以她是 python2.7 的 .pyc

用[線上工具](https://tool.lu/pyc)解

```
#!/usr/bin/env python
# encoding: utf-8
# 访问 http://tool.lu/pyc/ 查看更多信息
import sys
lookup = [
    196,
    153,
    149,
    206,
    17,
    221,
    10,
    217,
    167,
    18,
    36,
    135,
    103,
    61,
    111,
    31,
    92,
    152,
    21,
    228,
    105,
    191,
    173,
    41,
    2,
    245,
    23,
    144,
    1,
    246,
    89,
    178,
    182,
    119,
    38,
    85,
    48,
    226,
    165,
    241,
    166,
    214,
    71,
    90,
    151,
    3,
    109,
    169,
    150,
    224,
    69,
    156,
    158,
    57,
    181,
    29,
    200,
    37,
    51,
    252,
    227,
    93,
    65,
    82,
    66,
    80,
    170,
    77,
    49,
    177,
    81,
    94,
    202,
    107,
    25,
    73,
    148,
    98,
    129,
    231,
    212,
    14,
    84,
    121,
    174,
    171,
    64,
    180,
    233,
    74,
    140,
    242,
    75,
    104,
    253,
    44,
    39,
    87,
    86,
    27,
    68,
    22,
    55,
    76,
    35,
    248,
    96,
    5,
    56,
    20,
    161,
    213,
    238,
    220,
    72,
    100,
    247,
    8,
    63,
    249,
    145,
    243,
    155,
    222,
    122,
    32,
    43,
    186,
    0,
    102,
    216,
    126,
    15,
    42,
    115,
    138,
    240,
    147,
    229,
    204,
    117,
    223,
    141,
    159,
    131,
    232,
    124,
    254,
    60,
    116,
    46,
    113,
    79,
    16,
    128,
    6,
    251,
    40,
    205,
    137,
    199,
    83,
    54,
    188,
    19,
    184,
    201,
    110,
    255,
    26,
    91,
    211,
    132,
    160,
    168,
    154,
    185,
    183,
    244,
    78,
    33,
    123,
    28,
    59,
    12,
    210,
    218,
    47,
    163,
    215,
    209,
    108,
    235,
    237,
    118,
    101,
    24,
    234,
    106,
    143,
    88,
    9,
    136,
    95,
    30,
    193,
    176,
    225,
    198,
    197,
    194,
    239,
    134,
    162,
    192,
    11,
    70,
    58,
    187,
    50,
    67,
    236,
    230,
    13,
    99,
    190,
    208,
    207,
    7,
    53,
    219,
    203,
    62,
    114,
    127,
    125,
    164,
    179,
    175,
    112,
    172,
    250,
    133,
    130,
    52,
    189,
    97,
    146,
    34,
    157,
    120,
    195,
    45,
    4,
    142,
    139]
pwda = [
    188,
    155,
    11,
    58,
    251,
    208,
    204,
    202,
    150,
    120,
    206,
    237,
    114,
    92,
    126,
    6,
    42]
pwdb = [
    53,
    222,
    230,
    35,
    67,
    248,
    226,
    216,
    17,
    209,
    32,
    2,
    181,
    200,
    171,
    60,
    108]
flag = raw_input('Input your Key:').strip()
if len(flag) != 17:
    print 'Wrong Key!!'
    sys.exit(1)
flag = flag[::-1]
for i in range(0, len(flag)):
    if ord(flag[i]) + pwda[i] & 255 != lookup[i + pwdb[i]]:
        print 'Wrong Key!!'
        sys.exit(1)

print 'Congratulations!!'
```

程式真的很簡單，直接寫個 python 解
```python
flag = ''
for i in range(17):
	flag += chr(lookup[i + pwdb[i]] - pwda[i] & 255)
print flag[::-1]
```

## Classical Crackme
> Description:
>
> 经典Crackme题目，FLAG就是注册码。

先看檔案格式，是 .NET 的 ，用 ILSpy 來看，裡面有一個
```
private void ‬​⁪‪⁭⁫‭⁯‭‌‎⁫‮‮‬‫⁪⁭⁮‫⁮‏‭‎‬‏‍‏‫‌‪⁭⁪⁮‭‍‌⁫‪‭‮(object P_0, EventArgs P_1)
{
	string s = this.‎⁯⁪‏⁮‬⁬‌⁪​⁮‭⁫‭‏⁫‫‌⁫‭⁭‫⁫‌⁯⁭⁪‭‏‮​⁭‬‍‍‬‏‮‮⁪‮.Text.ToString();
	byte[] bytes = Encoding.Default.GetBytes(s);
	string a = Convert.ToBase64String(bytes);
	string b = "UENURntFYTV5X0RvX05ldF9DcjRjazNyfQ==";
	if (a == b)
	{
		MessageBox.Show("注册成功！", "提示", MessageBoxButtons.OK);
	}
	else
	{
		MessageBox.Show("注册失败！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Hand);
	}
}

```

所以做 base64 decode 即可

## Smali
> Description:
>
> 都说学好Smali是学习Android逆向的基础，现在刚好有一个smali文件，大家一起分析一下吧~~

先用 smali2java 轉 java code 來看

這裡參考[工具](http://blog.csdn.net/huangxiaoguo1/article/details/52635854)

```java
public class Crackme {
    private String str2 = "cGhyYWNrICBjdGYgMjAxNg==";
    
    public Crackme() {
        GetFlag("sSNnx1UKbYrA1+MOrdtDTA==");
    }
    
    private String GetFlag(String p1) {
        byte[] "content" = Base64.decode(p1.getBytes(), 0x0);
        String "kk" = new String(Base64.decode(str2.getBytes(), 0x0));
        System.out.println(decrypt("content", "kk"));
        return null;
    }
    
    private String decrypt(byte[] p1, String p2) {
        String "m" = 0x0;
        try {
            byte[] "keyStr" = p2.getBytes();
            SecretKeySpec "key" = new SecretKeySpec("keyStr", "AES");
            Cipher "cipher" = Cipher.getInstance("AES/ECB/NoPadding");
            "cipher".init(0x2, "key");
            byte[] "result" = "cipher".doFinal(p1);
            return "m";
        } catch(NoSuchPaddingException "e") {
            "e".printStackTrace();
        }
        return  "m";
    }
}

```

所以可以知道是 AES 加密，用 Python 簡單解一下

```python
#!/usr/bin/env python
from Crypto.Cipher import AES
from base64 import b64decode as b64d

c = b64d('sSNnx1UKbYrA1+MOrdtDTA==')
k = b64d('cGhyYWNrICBjdGYgMjAxNg==')
print AES.new(k, AES.MODE_ECB).decrypt(c)
```

