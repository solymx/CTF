# picoCTF 2018 - Notes

## SpyFi

這邊直接來看程式碼，可以看到他考的是 AES-ECB ，所以可以立馬想到是 `cut-and-paste attack`

這邊要先幫他分組，首先我要先知道 flag 長度是多少 

這邊會發現說，當我輸入的字長度是 1 ~ 9 時，密文長度都是 320 ，可是當輸入的字長度是 10 ，則密文長度變為 352

所以可以知道 flag 總長度是 38，這邊先分好組:
```
0 :  'Agent,\nGreetings'
1 :  '. My situation r'
2 :  'eport is as foll'
3 :  'ows:\naaaaaaaaa\nM'
4 :  'y agent identify'
5 :  'ing code is: FLA'
6 :  'G{38_chars_in_i1'
7 :  '2345678931123456'
8 :  '7t}.\nDown with t'
9 :  'he Soviets,\n006\n'
```

將輸入改為: `"a"*11 + "A"*16` ，其中 `A` 用來撞 FLAG，而 `a` 只是垃圾，在分組看一下:
```
0 :  'Agent,\nGreetings'
1 :  '. My situation r'
2 :  'eport is as foll'
3 :  'ows:\naaaaaaaaaaa'
4 :  'AAAAAAAAAAAAAAAA'
5 :  '\nMy agent identi'
6 :  'fying code is: F'
7 :  'LAG{38_chars_in_'
8 :  'i123456789311234'
9 :  '567t}.\nDown with'
10 :  ' the Soviets,\n00'
11 :  '6\n00000000000000'
```

其實因為知道 flag 開頭是 picoCTF ，可以先測試一下

輸入 `"a"*11 + "fying code is: p"`:
```
0  :  ce046744a8001b55f5031288fc983115
1  :  ff5affb36c681216a9c51e8f21a58aed
2  :  691761c8573db4e7ea6b58605dd68fbd
3  :  67c97d1296274f932b30d88bfdcb769f
4  :  382f6cf8958cf724be0bf19b83c44ee1
5  :  aeaca2bcf64ed4288cfd207f5e6d5bb4
6  :  382f6cf8958cf724be0bf19b83c44ee1
7  :  b94302ebb74b3f7e9c78f8cece361cbe
8  :  4b5efa244fdcb91b59df3b07b89192bb
9  :  ce2e2abb47f4d0d8de6460e42a73f9e7
10  :  ae95e42f07779a466b0bbefcef0334ce
11  :  4437689d6901875ea13a57727ddf42e4

```

可以看到 4 和 6 一樣，反正以此類推大概這樣


## Magic padding Oracle
> Description:
>
> Can you help us retreive the flag from this crypto service? Connect with nc 2018shell1.picoctf.com 45008. We were able to recover some Source Code.


可以先簡單看一下程式碼，一開始會給一個 enc(cookie) ，之後問我們 cookie ，這邊直接把它給我們丟回去看:
```
# nc 2018shell1.picoctf.com 45008

Welcome to Secure Encryption Service version 1.34

Here is a sample cookie: 5468697320697320616e20495634353642fef6c675ee50fca505d4023e8c21bd0b409a1f864eec9dad32e86199b518330ab686ba7afaf345e4b2bdca541146511d82c37e7f991be60eda932d1fd407c65ab1726c337c128163c4c3449ce2398d

What is your cookie?
5468697320697320616e20495634353642fef6c675ee50fca505d4023e8c21bd0b409a1f864eec9dad32e86199b518330ab686ba7afaf345e4b2bdca541146511d82c37e7f991be60eda932d1fd407c65ab1726c337c128163c4c3449ce2398d
username: guest
Admin? false
Cookie is expired

```

這邊大概可以知道的是，我們要構造一個有正確 pkcs7 padding 的 json 格式的資料，其內有:
1. username: admin
2. is_admin: true
3. expires:  未來的日期








