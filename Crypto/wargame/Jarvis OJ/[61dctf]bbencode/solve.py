import libnum

def bbencode(n):
    a = 0
    for i in bin(n)[2:]:
        a = a << 1
        if (int(i)):
            a = a ^ n
        if a >> 256:
            a = a ^ 0x10000000000000000000000000000000000000000000000000000000000000223L
    return a

enc = 61406787709715709430385495960238216763226399960658358000016620560764164045692
for _ in range(1000000):
	enc = bbencode(enc)
	tmp = libnum.n2s(enc)
	if 'flag' in tmp:
		print tmp
		raw_input()