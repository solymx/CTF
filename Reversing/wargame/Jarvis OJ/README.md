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

## Classical CrackMe2

首先丟 detect it easy 間單看一下，一個 .net 程式

之後用 dnSpy 解

[參考](https://hk.saowen.com/a/1a229716815dbef999bca7de2632016ac3dbe73d87d51316234ae8e6e6a969e0)

一開始點 run 然後設定要 break 在 entry point

然後跳到另一個畫面後，點一下 new 後面那串字，會跳到主程式那
```
Application.Run(new Wm@@9OrPgw\u0020d/p?i,N>l*h@Y!());
```

一直往下看會看到這邊
```
public static string \u202B\u202E\u200F\u200B\u202D\u202D\u200B\u206B\u200C\u202E\u206A\u206C\u206C\u200F\u200B\u200B\u206C\u200C\u202E\u202B\u206F\u202C\u202A\u206C\u202B\u200C\u200E\u202D\u206F\u206E\u200B\u202B\u202C\u202B\u206A\u206D\u200D\u206E\u200D\u206E\u202E(string A_0)
    {
        byte[] bytes = Encoding.UTF8.GetBytes(<Module>.\u206A\u206D\u202B\u200D\u206D\u202D\u202E\u200C\u206A\u206C\u206E\u202C\u202A\u200E\u206B\u202A\u200F\u202B\u200E\u200E\u206B\u200E\u206A\u206F\u206D\u200F\u200B\u200E\u202A\u202D\u206C\u200D\u206B\u200B\u200B\u206F\u200E\u202B\u200C\u206F\u202E<string>(2131648913u));
        byte[] bytes2 = Encoding.UTF8.GetBytes(A_0);
        ICryptoTransform cryptoTransform = new RijndaelManaged
        {
            Key = bytes,
            Mode = CipherMode.ECB,
            Padding = PaddingMode.PKCS7
        }.CreateEncryptor();
        byte[] array = cryptoTransform.TransformFinalBlock(bytes2, 0, bytes2.Length);
        return Convert.ToBase64String(array, 0, array.Length);
    }
```

從這邊可以看到他用 AES ， MODE 是 ECB ，bytes 這個變數存 key

所以在 `byte[] bytes2` 這行按右鍵下斷點，然後按 continue 可以看到 key 的值

之後往下看一下程式碼

```
private void \u202C\u202B\u206C\u202D\u200C\u206A\u206E\u206D\u202D\u202C\u206B\u206B\u202A\u202A\u206F\u206C\u206E\u202A\u206E\u200D\u206A\u200E\u206E\u206D\u200D\u202E\u206E\u200C\u200E\u200F\u202E\u202A\u206E\u200B\u202B\u206A\u202B\u206B\u200D\u206E\u202E(object A_1, EventArgs A_2)
    {
        string text = this.\u200E\u202E\u206C\u202E\u200D\u202B\u206A\u200E\u206A\u202B\u202B\u202D\u202C\u200F\u206C\u200C\u200D\u202E\u206B\u206C\u202E\u200C\u206D\u206F\u206A\u200B\u202B\u206D\u200C\u206C\u206C\u202A\u200E\u206C\u206C\u206F\u200E\u202E\u206E\u206C\u202E.Text;
        string text2 = Wm@@9OrPgw\u0020d/p?i,N>l*h@Y!.\u202B\u202E\u200F\u200B\u202D\u202D\u200B\u206B\u200C\u202E\u206A\u206C\u206C\u200F\u200B\u200B\u206C\u200C\u202E\u202B\u206F\u202C\u202A\u206C\u202B\u200C\u200E\u202D\u206F\u206E\u200B\u202B\u202C\u202B\u206A\u206D\u200D\u206E\u200D\u206E\u202E(text);
        if (text != "" && text2 == <Module>.\u206C\u202E\u200B\u200F\u206E\u200E\u206C\u200D\u206F\u206F\u206B\u202B\u202D\u202C\u206A\u206F\u206C\u200C\u200E\u202A\u200D\u200E\u206A\u206D\u202E\u206A\u206D\u206D\u200D\u206E\u200E\u206C\u206E\u200C\u200B\u202B\u206D\u206A\u206F\u200F\u202E<string>(2114908449u))
        {
            MessageBox.Show(<Module>.\u200C\u200B\u202A\u200F\u200B\u206E\u206F\u206A\u202B\u206B\u202E\u206E\u200E\u206F\u200F\u200C\u202B\u200D\u202D\u206E\u206C\u202E\u202A\u202D\u202B\u206F\u206C\u206B\u206E\u206D\u206C\u200C\u200C\u206A\u202A\u206F\u206D\u206A\u206D\u206C\u202E<string>(655092558u), <Module>.\u200C\u200B\u202A\u200F\u200B\u206E\u206F\u206A\u202B\u206B\u202E\u206E\u200E\u206F\u200F\u200C\u202B\u200D\u202D\u206E\u206C\u202E\u202A\u202D\u202B\u206F\u206C\u206B\u206E\u206D\u206C\u200C\u200C\u206A\u202A\u206F\u206D\u206A\u206D\u206C\u202E<string>(4269915770u), MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        }
        else
``` 

這邊可以看到 text2 如果比對正確，就可以 get flag ，那先用左鍵點一下 text2 後面那一串字

會跳到另一個函數，在那個函數的最後面 `return result` 那邊下斷點，在繼續 continue

可以看到 flag 加密後的樣子，這樣就可以解了 

```python
#!/usr/bin/env python
from Crypto.Cipher import AES
import libnum
key = 0x7063746632303136706374663230313670637466323031367063746632303136
key = libnum.n2s(key)

func = AES.new(key, AES.MODE_ECB)

c = b64d("x/nzolo0TTIyrEISd4AP1spCzlhSWJXeNbY81SjPgmk=")

print func.decrypt(c) # flag
```

## 61dctf_androideasy

很簡單的入門 android 題目

直接拿 classes.dex 轉 jar 用 jd-gui 看

可以知道單純 xor
```python
a = [113, 123, 118, 112, 108, 94, 99, 72, 38, 68, 72, 87, 89, 72, 36, 118, 100, 78, 72, 87, 121, 83, 101, 39, 62, 94, 62, 38, 107, 115, 106]
flag = ''
for i in a:
    flag += chr(i^0x17)

print flag
```
 
## [61dctf]stheasy

很基本的題目，直接丟 ida pro 可以看到他是要長度 = 29 ，然後

依照他規則寫 code 解即可

## DD - Android Easy

一樣拿 classes.dex 轉 jar 看 code ，照著他流程寫就好@@
```python
p = [ -40, -62, 107, 66, -126, 103, -56, 77, 122, -107, -24, -127, 72, -63, -98, 64, -24, -5, -49, -26, 79, -70, -26, -81, 120, 25, 111, -100, -23, -9, 122, -35, 66, -50, -116, 3, -72, 102, -45, -85, 0, 126, -34, 62, 83, -34, 48, -111, 61, -9, -51, 114, 20, 81, -126, -18, 27, -115, -76, -116, -48, -118, -10, -102, -106, 113, -104, 98, -109, 74, 48, 47, -100, -88, 121, 22, -63, -32, -20, -41, -27, -20, -118, 100, -76, 70, -49, -39, -27, -106, -13, -108, 115, -87, -1, -22, -53, 21, -100, 124, -95, -40, 62, -69, 29, 56, -53, 85, -48, 25, 37, -78, 11, -110, -24, -120, -82, 6, -94, -101 ]
q = [-57, -90, 53, -71, -117, 98, 62, 98, 101, -96, 36, 110, 77, -83, -121, 2, -48, 94, -106, -56, -49, -80, -1, 83, 75, 66, -44, 74, 2, -36, -42, -103, 6, -115, -40, 69, -107, 85, -78, -49, 54, 78, -26, 15, 98, -70, 8, -90, 94, -61, -84, 64, 112, 51, -29, -34, 126, -21, -126, -71, -31, -24, -60, -2, -81, 66, -84, 85, -91, 10, 84, 70, -8, -63, 26, 126, -76, -104, -123, -71, -126, -62, -23, 11, -39, 70, 14, 59, -101, -39, -124, 91, -109, 102, -49, 21, 105, 0, 37, -128, -57, 117, 110, -115, -86, 56, 25, -46, -55, 7, -125, 109, 76, 104, -15, 82, -53, 18, -28, -24 ]

a = []
for i in range(len(p)):
    a.append(p[i] ^ q[i])

k = a[0]
i = 0;
while 1:
    if a[i + k] != 0:
        i += 1
    else:
        break
# i = 54
f = ''
for i in range(54):
    f += chr(a[k + i])
print f
```


## FindPass

完全一步一步照[這篇](https://www.jianshu.com/p/73eb1e15b0f5)走

本來想改用夜神，但好像有 bug = =


## 爬楼梯

先把 apk 安裝下來，可以知道要爬樓梯到他要求的高度才給 flag

這種看起來跟破遊戲蠻像的，直接丟 android killer 看一下 java code 有一行

```java
if (this.to_reach_int <= this.has_gone_int) {
      ((Button)findViewById(2131492950)).setClickable(true);
```
那我們直接在 android killer 裡面搜索 `setClickable`

會搜尋到兩個，那比對一下 java code ，去改 smali 的第二個結果應該是我們要的

也就是把 v5 從 0x0 改為 0x1 (181 行)

不過不知道為啥用 android killer 簽名會失敗= =

改用 apktool box 就成功@@

之後安裝後，就可以馬上看到 flag 了


哦哦後面檢查一下發現，好像是 res/ 下有一個 png 在打包時會出錯@@

所以像用 apktool box 選擇不要處理 res/ 就正常



