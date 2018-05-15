# DEF CON CTF Qualifier 2018 - Notes

## throwback

這題題目是 `Anyo!e!howouldsacrificepo!icyforexecu!!onspeedthink!securityisacomm!ditytop!urintoasy!tem!`

把上面缺的字組起來是 `Anyone who would sacrifice policy for execution speed thinks security is a commodity to pour in to a system!`

缺少的是 `nwltisoos` ，但不是 flag

換一個想法是，如果把 `!` 當成是分隔，每一個的數量是

```
['Anyo',
 'e',
 'howouldsacrificepo',
 'icyforexecu',
 '',
 'onspeedthink',
 'securityisacomm',
 'ditytop',
 'urintoasy',
 'tem',
 '']

# [4, 1, 18, 11, 0, 12, 15, 7, 9, 3] 
``` 

把 0 當成是空白， 1 = a . 2 = b 這樣排，可以得到 flag: `dark logic`



