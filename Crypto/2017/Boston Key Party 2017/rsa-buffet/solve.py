#!/usr/bin/env python
from Crypto.PublicKey import RSA
import glob

def decrypt(private_key, ciphertext):
	if len(ciphertext) < 512 + 16:
		return None
	msg_header = ciphertext[:512]
	msg_iv = ciphertext[512:512+16]
	msg_body = ciphertext[512+16:]
	try:
		symmetric_key = PKCS1_OAEP.new(private_key).decrypt(msg_header)
	except ValueError:
		return None
	if len(symmetric_key) != 32:
		return None
	return AES.new(symmetric_key,
		mode=AES.MODE_CFB,
		IV=msg_iv).decrypt(msg_body)

cts = glob.glob('ciphertext-?.bin')
keys = glob.glob('d?')
secrets = []
for k in keys:
	for c in cts:
		private_key = RSA.importKey(open(k).read())
		ciphertext = open(c,'rb').read()
		plaintext  = decrypt(private_key,ciphertext)

		if plaintext is not None:
			if 'Congrat' in plaintext:
				secrets = secrets + plaintext.splitlines()[1:]

for x in [x for x in secrets if '1-' == x[:2]]:
	for y in [y for y in secrets if '3-' == y[:2]]:
		for z in [z for z in secrets if '4-' == z[:2]]:
			flag = rs.recover_secret([x,y,z])
			if 'FLAG' in flag:
				print flag


