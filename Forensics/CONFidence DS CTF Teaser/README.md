# CONFidence DS CTF Teaser - Notes

## Stegano50 

先用 pdfinfo 看其資訊
```
root@lubun:/tmp/p# pdfinfo stegano50.pdf
Title:          polar bear during a snow storm
Subject:        <| tr AB .- |>
Keywords:       Could this be the flag? : Tm9wZSAsIG5vdCBoZXJlIDspCg==
Author:         KeiDii
Creator:        LaTeX /o/
Producer:       find mr.morse text
CreationDate:   Thu Mar 13 22:33:50 2014
ModDate:        Thu Mar 13 22:33:50 2014
Tagged:         no
UserProperties: no
Suspects:       no
Form:           none
JavaScript:     no
Pages:          1
Encrypted:      no
Page size:      595.276 x 841.89 pts (A4)
Page rot:       0
File size:      38742 bytes
Optimized:      no
PDF version:    1.5
```

有一個 base64 ，把她 decode 看一下

```
root@lubun:/tmp/p# echo 'Tm9wZSAsIG5vdCBoZXJlIDspCg==' | base64 -d
Nope , not here ;)
```

不過可以看到在 Subject 那邊，他寫把 AB 轉 .-

.- << 看起來是摩斯電碼

所以可以找一下 pdf 裡面有沒有格式是 ABAA 這種

先用 pdftotext 轉一下，但沒有啥特別的

改用 pdftohtml ，轉出來有一個 stegano50s.html ，裡面有

```html 
<body>
<a name=1></a>AAABB<br/>
BBA<br/>
AAAAB<br/>
AAAAA<br/>
AAA<br/>
AA<br/>
AAABB<br/>
BB<br/>
AAABB<br/>
ABAA<br/>
BAAA<br/>
ABBBB<br/>
AAAAA<br/>
ABBBB<br/>
AAAB<br/>
BA<br/>
ABBBB<br/>
BBBAAA<br/>
BBA<br/>
AB<br/>
ABAA<br/>
AABA<br/>
BBAABB<br/>
AAA<br/>
BA<br/>
BBB<br/>
AA<br/>
B<br/>
AB<br/>
ABAA<br/>
AAB<br/>
B<br/>
AB<br/>
ABA<br/>
BBA<br/>
A<br/>
B<br/>
BBB<br/>
BABA<br/>
```

把上面的整理一下，再轉成 .-  之後解 morse code 即可