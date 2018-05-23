#!/usr/bin/env python
from pwn import *
from Crypto.Cipher import AES

PORT = 42000
HOST = 'ECDH.2018.teamrois.cn'
r = remote(HOST, PORT)

# secp128r1
p = 0x0fffffffdffffffffffffffffffffffff
a = 0x0fffffffdfffffffffffffffffffffffc
b = 0x0e87579c11079f43dd824993c2cee5ed3
g = 0x4161ff7528b899b2d0c28607ca52c5b86cf5ac8395bafeb13c02da292dded7a83
compress_g = '03161ff7528b899b2d0c28607ca52c5b86'

def get_bob_pubkey():
	r.sendlineafter(': ', str(2))
	r.sendlineafter(': ', str(2))
	r.recvuntil('pub: ')
	key = r.recvuntil('\n')[:-1]
	return key

def set_alice_pubkey():
	r.sendlineafter(': ', str(2))
	r.sendlineafter(': ', str(4))
	r.sendlineafter(': ', compress_g)

def ask_bob_flag():
	r.sendlineafter(': ', str(2))
	r.sendlineafter(': ', str(1))

def get_enc_flag():
	r.sendlineafter(': ', str(1))
	r.sendlineafter(': ', str(1))
	r.recvuntil('something.Bob said: ')
	enc = r.recvuntil('\n')[:-1]
	return enc

key = get_bob_pubkey()[2:].decode('hex')
set_alice_pubkey()
ask_bob_flag()
enc = get_enc_flag().decode('hex')
r.close()

a = AES.new(key, AES.MODE_ECB)
print a.decrypt(enc)


