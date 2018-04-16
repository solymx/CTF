# PWN problem list

## Completed Challenges
Record

* **Wargame - pwnable.tw**
	- start (leak esp and jmp to shellcode)
	- orw (write x86 assembly code (open , read , write))
	- Silver Bullet (off by one overflow & know strncat will add \x00 in the end)
	- dubblesort (scanf("%u") can use "+" to bypass canary)


* **pwnhub.tw**
	- bofeasy (basic buffer overflow (overwrite ret and jmp to function))       
	- gdb (learn how to use gdb (change eip to other function))           
	- ret2sc (return to shellcode)        
	- orw64 (write x64 assembly code (open , read , write))         
	- pwntool (Binary Search)       
	- r3t2lib (return to library)       
	- simplerop (rop (statically linked))     
	- ret2plt (rop)       


* **Wargame - pwnable.kr**
	- ***[Toddler's Bottle]***
		- bof (basic buffer overflow)
		- passcode (GOT Hijack)
		- random (linux c rand())
		- mistake (xor)
		- shellshock (CVE-2014-6271)
		- blackjack (just see code)
		- cmd1
		- cmd2
			
* **Wargame - Jarvis OJ**
	- Smashes (ELF remapping and SSP leak)
	- Tell me Something (buffer overflow & jmp to func)		
	- [XMAN]level0 (buffer overflow & jmp to func)
	- [XMAN]level1 (ret2sc)
	- [XMAN]level2 (basic rop)
	- [XMAN]level2(x64) (basic rop)
	- [XMAN]level3 (ret2libc)
	- [XMAN]level3(x64) (ret2libc, use write to leak base address)

* **picoCTF 2017**
	- Shellz (just send shellcode - execve("/bin/sh,0,0") )
	- Shells (send shellcode - jmp to func)
	- Guess The Number (Integer overflow)
	- Ive Got A Secret (Basic Format String Attack (guess number))

* **X-CTF Quals 2016**
	- b0verfl0w (stack privot)

* **TJCTF 2016**
	- Oneshot (one gadget rce)
		
* **BackdoorCTF 2017**
	- baby-0x41414141 (fmt vuln)	
	- JUST-DO-IT (ret2libc)
	- Fun Signals (SROP)

* **HITB CTF 2017**
	- 1000levels (use vsyscall for ret & one gadget rce)

* **2016 AIS3 Final**
	- Remote1 (use fmt to leak canary and rop)
	- Remote2 (stack privot)

* **XDCTF 2015**
	- pwn200 (ret2_dl_runtime_resolve)

* **HBCTF 2017**
	- pwn100-whatiscanary (use '\x00' to bypass strlen & SSP leak)
	- pwn200–infoless.infoless (ret2_dl_runtime_resolve)

* **TUCTF 2017**
	- Vuln Chat (buffer overflow to overwrite scanf's format)
	- Vuln Chat2.0 (overflow EIP last one byte)

* **SECCON CTF Quals 2017**

* **SECCON CTF Quals 2017**
	- Baby Stack (go, stack overflow)
	- election

* **Wargame - hackme.inndy.tw**
	- homework (index out of bound, ret)
	- ROP (basic rop, static)
	- ROP2 (basic rop, dynamic)
	- toooomuch	(Binary Search)
	- toooomuch-2 (jmp esp)
	- echo (fmt vuln)
	- smashthestack (canary leak)

* **volga quals 2014**
	- 100 (利用時間差去爆破密碼)
	- 300 (python jail escape, use file object to read flag.txt)

* **ROP Emporium**
	- ret2win (jmp to func)
	- split (basic rop)
	- callme (basic rop)
	- write4 
	- badchars (需要對 shellcode 做encode/decode, 用 xor)
	- fluff (對 gadget 需要特別找一下)
	- pivot (stack pivot)

* **tinyCTF 2014**
	- Not exactly Alcatraz (simple python sandbox)

* **AceBear Security Contest 2018**
	- easy heap (integer overflow)

* **MMA CTF 2nd 2016**
	- greeting (fmt vuln, .fini_array)

