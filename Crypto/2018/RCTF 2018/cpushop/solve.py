#!/usr/bin/env python
from pwn import *
from hashpumpy import *

HOST = 'cpushop.2018.teamrois.cn'
PORT = 43000
r = remote(HOST, PORT)
r.sendlineafter(': ', str(2))
r.sendlineafter(': ', str(9))

r.recvuntil('Your order:\n')
order = r.recvline().strip().split("&sign=")
for i in range(8, 33):
	aft = hashpump(order[1], order[0], order[0] + "&price=9", i)
	payload = aft[1] + "&sign=" + aft[0]
	r.sendlineafter(': ', str(3))
	r.recvrepeat(0.1)
	r.sendline(payload)
	ans = r.recvline()
	if "Invalid" not in ans:
		print ans
		break
r.interactive()