# Jarvis OJ - Notes

> 目錄:
> * [简单ECC概念](#简单ECC概念)



简单ECC概念
---
> Description:
>
> 已知椭圆曲线加密Ep(a,b)参数为
> 
> p = 15424654874903
> 
> a = 16546484
> 
> b = 4548674875
> 
> G(6478678675,5636379357093)
> 
> 私钥为
> 
> k = 546768
> 
> 求公钥K(x,y)
> 
> 提示：K=kG
> 
> 提交格式XUSTCTF{x+y}(注意，大括号里面是x和y加起来求和，不是用加号连接)
> 注：题目来源XUSTCTF2016


這題是單純算公鑰，看給的參數是質數體，直接帶公式即可

```python
#!/usr/bin/env python
import libnum

G = (6478678675,5636379357093)
P = (0,0)
a = 16546484
p = 15424654874903
k = 546768

def p_add(G,P):
	if G == (0, 0):
		return P
	if P == (0, 0):
		return G
	x1, y1 = G
	x2, y2 = P
	if G == P:
		t = (3*x1*x1+a) * libnum.invmod(2*y1, p)
	else:
		t =  (y2 - y1) * libnum.invmod((x2 - x1), p)
	x = (t*t - x1 - x2) % p
	y = (t*(x1 - x) - y1) % p
	return (x, y)

for _ in range(k):
	P = p_add(G, P)

print "XUSTCTF{%s}" % (str(P[1] + P[0]))
```

## Medium RSA

n 可以直接分解

## hard RSA

看到 e = 2 就會想到 rabin 密碼

[參考](http://www.cnblogs.com/iptables/p/5598049.html)

## very hard RSA

看到 N 相同，e 互質就知道是考共模攻擊

 
