# TUCTF 2017 - Notes


## The Never Ending Crypto

```python
#!/usr/bin/env python
from pwn import *

r = remote('neverending.tuctf.com', 12345)

for i in range(1,51):
	print r.recvuntil('Round %d. Give me some text:' % i)
	r.sendline('aabbcc')
	print r.recvuntil('encrypted is ')
	data = r.recv(1)
	print "data:",data
	count = ord(data) - ord('a')
	print "count:",count
	print r.recvuntil('What is ')
	c = r.recv(15)
	print "c:",c
	print r.recvrepeat(0.1)
	m = ''
	for i in c:
		tmp = ord(i) - count
		if tmp >= 127:
			tmp -= 95
		elif tmp < 32:
			tmp += 95
		m += chr(tmp)
	print "m:",m
	r.sendline(m)

	## first round end



r.interactive()
"""
nc neverending.tuctf.com 12345
"""


```
