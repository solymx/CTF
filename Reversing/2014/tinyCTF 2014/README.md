# tinyCTF 2014 - Notes

## Elrond32

非常簡單的 rev ，用 ida pro 看一下，寫個code 反解一下就好

```python
dict = {}
dict['3'] = 'n'
dict['9'] = 'r'
dict['4'] = 'd'
dict['1'] = 'e'
dict['0'] = 'i'
dict['5'] = 'a'
dict['6'] = 'g'
dict['7'] = 's'
a2 = 0
pw = ''
for i in range(33):
	pw +=dict[str(a2)]
	a2 = 7 * (a2 + 1) % 11
	if a2 == 2:
		break
print "password: ",pw
```

