# NoNameConCTF 2018 - Notes

## Convert
純粹看別人的 write up 留個紀錄
[write_up](https://fireshellsecurity.team/nonamectf-convert/)

簡單講:
1. 依題目提示，知道是考 ssrf ，但用 http://127.0.0.1 和 localhost 沒反應，改用 0.0.0.0 有東西
2. 但從中找不到什麼有趣東西，直接用掃描的: ```$ dirb url``` 
3. 從中找到 flag

是說好像大多比賽都不喜歡大家用掃描工具 @@