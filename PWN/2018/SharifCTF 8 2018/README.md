# SharifCTF 8 2018 - Notes

## OldSchool-NewAge

這題很明顯有 buffer overflow ，且保護只開 DEP 

所以就是單純 Overflow 後做 ROP ，先算出 libc 之後 system('sh')

[solve.py](./solve.py)

## suctfdb
> Description
>
> Have you ever played with this *special* seq holder in Python?

