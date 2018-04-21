# AIS3 Final 2016

## Remote 1

這題漏洞有兩個，一個是在 echo() 裡面有 printf(buf, "quit"); => fmt vuln

另一個是 echo() 裡面的 rlen = read(0, buf, 80uLL); => buffer overflow

然後看保護有開 stack guard ，然後程式中有 system_plt 和 sh 可以直接用

所以步驟就是先透過fmt vuln 來獲取 canary ，之後 overflow 蓋好後跳 system('sh')

