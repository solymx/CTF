# picoCTF 2018 - Notes

## special-pw
> Description:
>
> Can you figure out the right argument to this program to login? We couldn't manage to get a copy of the binary but we did manage to dump some machine code and memory from the running process.

## keygen-me-1
> Description:
>
> Can you generate a valid product key for the validation program in /problems/keygen-me-1_1_8eb35cc7858ff1d2f55d30e5428f30a7


直接丟 ida pro 可以看到一開始 `check_valid_key` 這個函數要求你的輸入需要是數字或英文大寫

並且要求長度必須是 16

之後進來看 `validate_key`， 大概就是算個值，然後要和 input 的最後一個字數值一樣

其實這邊直接用 gdb 改一下比較快

直接用
```
set args AAAAAAAAAAAAAAAA
```
看差多少，改成
```
set args AAAAAAAAAAAAAAAO
```

這樣就是答案


## keygen-me-2

一樣先丟 ida pro ，`check_valid_key` 這個和前一個一樣，之後來看 `validate_key`

裡面要過 12 關...

第一關 第一和第二個字相加再 mod 36 要等於 14 ，比如 '4A'
第二關 第三和第四個字相加再 mod 36 要等於 24 ，比如 'AE'
第三關 第三和第一個字相減再 mod 36 要等於 6  ，比如 '4A'
第四關 第二個加上第四個加上第六個 mod 36 要等於 4 
第五關 第三個加上第五個加上第七個 mod 36 要等於 13 
第六關 第四個加上第五個加上第六個 mod 36 要等於 22
第七關 第七個加上第九個加上第十一個 mod 36 要等於 31 
第八關 第二個加上第五個加上第八個 mod 36 要等於 7
第九關 第十個加上第十三個加上第十六個 mod 36 要等於 20
第十關 第十四個加上第十五個加上第十六個 mod 36 要等於 12

# 4AAE
