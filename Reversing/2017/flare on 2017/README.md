# flare on 2017 - Notes

## challenge 1

給了一個 login.html

```html
<!DOCTYPE Html />
<html>
    <head>
        <title>FLARE On 2017</title>
    </head>
    <body>
        <input type="text" name="flag" id="flag" value="Enter the flag" />
        <input type="button" id="prompt" value="Click to check the flag" />
        <script type="text/javascript">
            document.getElementById("prompt").onclick = function () {
                var flag = document.getElementById("flag").value;
                var rotFlag = flag.replace(/[a-zA-Z]/g, function(c){return String.fromCharCode((c <= "Z" ? 90 : 122) >= (c = c.charCodeAt(0) + 13) ? c : c - 26);});
                if ("PyvragFvqrYbtvafNerRnfl@syner-ba.pbz" == rotFlag) {
                    alert("Correct flag!");
                } else {
                    alert("Incorrect flag, rot again");
                }
            }
        </script>
    </body>
</html>
```

看 code 可以知道是 rot13 ，這邊直接用 tr 解

```
$ echo 'PyvragFvqrYbtvafNerRnfl@syner-ba.pbz' | tr a-zA-Z n-za-mN-ZA-M
ClientSideLoginsAreEasy@flare-on.com
```


## challenge 2

先執行看看
```
$ ./IgniteMe.exe
G1v3 m3 t3h fl4g: ww
N0t t00 h0t R we? 7ry 4ga1nz plzzz!
```

所以從這邊可以知道，他會需要一個輸入，並且存到某個地方

之後經過一些驗證判斷，然後給我們一個輸出

那這邊直接丟 ida 看，可以看到這邊
```
signed int sub_401050()
{
  int v0; // ST04_4
  int i; // [esp+4h] [ebp-8h]
  unsigned int j; // [esp+4h] [ebp-8h]
  char v4; // [esp+Bh] [ebp-1h]

  v0 = sub_401020(byte_403078);
  v4 = sub_401000();
  for ( i = v0 - 1; i >= 0; --i )
  {
    byte_403180[i] = v4 ^ byte_403078[i];
    v4 = byte_403078[i];
  }
  for ( j = 0; j < 0x27; ++j )
  {
    if ( byte_403180[j] != (unsigned __int8)byte_403000[j] )
      return 0;
  }
  return 1;

```

也就是他做 xor 4 之後要等於 byte_403000[j]

```
a = [0xD ,0x26 ,0x49 ,0x45 ,0x2A ,0x17 ,0x78 ,0x44 ,0x2B ,0x6C ,0x5D ,0x5E ,0x45 ,0x12 ,0x2F ,0x17 ,0x2B ,0x44 ,0x6F ,0x6E ,0x56 ,0x9 ,0x5F ,0x45 ,0x47 ,0x73 ,0x26 ,0x0A ,0x0D ,0x13 ,0x17 ,0x48 ,0x42 ,0x1 ,0x40 ,0x4D ,0xC , 2 ,0x69]

flag = []
v = 4

for x in reversed(a):
    v = x ^ v
    flag.append(v)

print ''.join(reversed(map(chr, flag)))  

```

## challenge 3

一個 socket 監聽在 127.0.0.1:2222


## challenge 4

## challenge 5


## challenge 6

## challenge 7


## challenge 8

## challenge 9

## challenge 10

## challenge 11

## challenge 12
