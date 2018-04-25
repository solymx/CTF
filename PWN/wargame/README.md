# PWN problem list - Wargame

## Completed Challenges
Record


* **pwnable.tw**
	- start (leak esp and jmp to shellcode)
	- orw (write x86 assembly code (open , read , write))
	- Silver Bullet (off by one overflow & know strncat will add \x00 in the end)
	- dubblesort (scanf("%u") can use "+" to bypass canary)
	- hacknote (Use After Free,UAF)


* **pwnhub.tw**
	- bofeasy (basic buffer overflow (overwrite ret and jmp to function))       
	- gdb (learn how to use gdb (change eip to other function))           
	- ret2sc (return to shellcode)        
	- orw64 (write x64 assembly code (open , read , write))         
	- pwntool (Binary Search)
	- r3t2lib (return to library)
	- simplerop (rop (statically linked))
	- ret2plt (rop)


* **pwnable.kr**
	- ***[Toddler's Bottle]***
		- bof (basic buffer overflow)
		- passcode (GOT Hijack)
		- random (linux c rand())
		- mistake (xor)
		- shellshock (CVE-2014-6271)
		- blackjack (just see code)
		- cmd1
		- cmd2

* **Jarvis OJ**
	- Smashes (ELF remapping and SSP leak)
	- Tell me Something (buffer overflow & jmp to func)
	- [XMAN]level0 (buffer overflow & jmp to func)
	- [XMAN]level1 (ret2sc)
	- [XMAN]level2 (basic rop)
	- [XMAN]level2(x64) (basic rop)
	- [XMAN]level3 (ret2libc)
	- [XMAN]level3(x64) (ret2libc, use write to leak base address)
	- [XMAN]level4 (stack migration, DynELF, no libc)
	- [XMAN]level5 (use mmap/mprotect to exec shellcode in NX)

* **hackme.inndy.tw**
	- homework (index out of bound, ret)
	- ROP (basic rop, static)
	- ROP2 (basic rop, dynamic)
	- toooomuch	(Binary Search)
	- toooomuch-2 (jmp esp)
	- echo (fmt vuln)
	- smashthestack (canary leak)

* **ROP Emporium**
	- ret2win (jmp to func)
	- split (basic rop)
	- callme (basic rop)
	- write4
	- badchars (需要對 shellcode 做encode/decode, 用 xor)
	- fluff (對 gadget 需要特別找一下)
	- pivot (stack pivot)
