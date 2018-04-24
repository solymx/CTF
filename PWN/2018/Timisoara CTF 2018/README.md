# Timisoara CTF 2018

## Attendance

這題先看保護只有 NX ，然後丟到 IDA PRO 可以知道一開始先輸入 31337 後進到函數

可以觸發 buffer overflow ，然後可以直接在城市裏面找到 sh\x00 和 system_plt

所以直接 overflow 後跳 system('sh\x00') 即可

## HeapSchool
