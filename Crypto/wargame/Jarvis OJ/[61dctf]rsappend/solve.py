#!/usr/bin/env python
import libnum
res = open("result").readlines()
n = int(res[0].strip())
del res[0]


def common_modulus_attack(c1, c2, e1, e2, n):
	s1, s2, _ = libnum.xgcd(e1, e2)
	if s1 < 0:
		s1 = s1 * -1
		c1 = libnum.invmod(c1, n)
	if s2 < 0:
		s2 = s2 * -1
		c2 = libnum.invmod(c2, n)
	m = (pow(c1, s1, n) * pow(c2, s2, n)) % n
	return m

for i in range(len(res)):
	for j in range(len(res)):
		if i == j:
			continue
		if libnum.gcd(int(res[i][:res[i].index("###")]), int(res[j][:res[j].index("###")])) == 1:
			e1 = int(res[i][:res[i].index("###")])
			e2 = int(res[j][:res[j].index("###")])
			c1 = int(res[i][res[i].index("###")+3:].strip())
			c2 = int(res[j][res[j].index("###")+3:].strip())
			print libnum.n2s(common_modulus_attack(c1,c2,e1,e2,n))
			raw_input("#")