# meepwn ctf 2018 - Notes

## Bazik 
> Description:
>
> A basic challenge will shine you...
> 
> nc 206.189.92.209 31333
> 
> nc 178.128.17.82 31333

首先連上去的樣子
```
root@solymx:~# nc 206.189.92.209 31333

Choose one:
1. Test the OTP
2. Get the public key
3. Get flag
1
otp should be: 522751278
encrypted dat: 06d74959aafe6e2570a23ac9f2db9376601792c240557f92583607d877e81a2b75ef8c81a4b336b84be68b9c2a0e0fa15cda7b581265a5250735fea79145c704880faa0cbe451b791abaf09c8bcc52aa588aab96855959d2bf02b7a243fc787131f969023915480c1ca942703c93da8dd45c2eeb44b8a44e63f3ef59d6509f27
decrypted dat: Your OTP for transaction #731337 in ABCXYZ Bank is 522751278.
decrypted otp: ['522751278']

Choose one:
1. Test the OTP
2. Get the public key
3. Get flag
2
-----BEGIN PUBLIC KEY-----
MIGdMA0GCSqGSIb3DQEBAQUAA4GLADCBhwKBgQC8Wfm1upxTkdV91b+nFL3w8iqc
qbmy+5Z3KbKPwPFb0+bs3Le9/utSkOQCyzQK7u+U/+FBwJGeK53PFV9zfFq4N+k6
tq3WwOTvTb0958Vc760IuuRCaUfUoMs5rll980K1YJ2uekAYdBU0NCUWkGYHD7wQ
M2Rwv4PItIjASNFlEQIBAw==
-----END PUBLIC KEY-----

Choose one:
1. Test the OTP
2. Get the public key
3. Get flag
3
encrypted dat: 6c8963a038c11b71ab1281f0bf02dfb33691caa9dc7a90300be878dd770e34d50b069b1088f3a3d71a361750d8f2ea2c5dc527dbddbc14cee5aba6c2227437b743c2196dfed4a31a91442bc643006d34302d06eb6836b7dc608c618a07913ae2bc44f37e3161260bc3b91a93ca484329a78ded441f5aff64b3564334205556ba
send me otp to get flag >>> ^C
```

在連上去看一下不同處
```
root@solymx:~# nc 206.189.92.209 31333

Choose one:
1. Test the OTP
2. Get the public key
3. Get flag
1
otp should be: 537838758
encrypted dat: 7469a81a5103bfa6375ebf691086d49f38bc70899acae9421926f2c182584d31a8c3acca5b2c68a78929f6718e432178e89315f6b32150b0e995f61e172f228f044935c24229f0ee974aa8d7c0f9c0ed5f07bd2f5beca0d756f437d492bf1893d39f31c86ebb76f2293092c9d0f4cc3f0b04d552aab11f069dca9eb03a58ee97
decrypted dat: Your OTP for transaction #731337 in ABCXYZ Bank is 537838758.
decrypted otp: ['537838758']

Choose one:
1. Test the OTP
2. Get the public key
3. Get flag
2
-----BEGIN PUBLIC KEY-----
MIGdMA0GCSqGSIb3DQEBAQUAA4GLADCBhwKBgQDEYYJhIeFmjfpT3gRF+OW8SvyX
BS9+iP1iEGoe/PFeX10JW4PcjOgXn6ku8uoK3H4N52JG+23Rb0EZVO0JGvAnNCsj
DWZ+usCEKTq2yf9VP7+ptku6TFr756StXd6xGPsCrv6S1v6aq9gszlIyG7HOBVwX
fhTdzWr1Jd0cjgz2jwIBAw==
-----END PUBLIC KEY-----

Choose one:
1. Test the OTP
2. Get the public key
3. Get flag
3
encrypted dat: 6f9531d06a1ad92ce776f5e9a80312b564e72682cbcd7025ad02724d49faf457fe5b1dbd0cad5f3b852bb2203099c4b36c02fc2d4aa6b94a7deb56880ea193775a9c319b575a9f9a07898bbb610809c4e95d0614473799ce0ac06ac8a5335b8fbeaa614ab8f34d92d4d512c421665518020bd844fdd455205d2b37fe63cf1141
send me otp to get flag >>> ^C

```

我們可以得到一個 rsa 公鑰，n size = 2014 , e = 3

而 Test the OTP 的 transaction #731337 in ABCXYZ Bank is 537838758

`537838758` 這個數值每次都會變，

然後最後要給個他要求的 otp 來 get flag


這邊可以發現其實要加密的 dat 都差不多，格式是
```
Your OTP for transaction #731337 in ABCXYZ Bank is 537838758.
```

537838758 每次不同而已

所以這題考的是 Stereotyped Messages Attack

可以[參考](https://github.com/mimoo/RSA-and-LLL-attacks)

也就是知道明文的高位元，可以還原出來整個明文的攻擊

所以需要使用 sage，每次連線只有 n 和 c 要改
```

e = 3
N = 135437459110716304538006156687298284070488506859949999283309586807611108705732076005935138650224504522957712346884962100004011168387736418008468741636540603993547197582288733324170281531145633058750726835930208387585358445030898533341905272355456567762723344068542021256820307134477127118613173245037419238891

c = 45647022535538658728224711328975909788224597772394986851089909749553823196992241783869850838501517774468200926152528104178955964780883980068981216212905092549003048586679359654538118207679517416094385662872504646081377800733953482656121364536945884450918846092252220296746192471995679226400210207843425179136

P.<x> = PolynomialRing(Zmod(N), implementation='NTL')
pol = (m + x)^e - c
roots = pol.small_roots(epsilon=1/30)
print("Potential solutions:")
for root in roots:
   print(root, long_to_bytes(m+root))
```

算出來結果
```
root@solymx:~# nc 206.189.92.209 31333

Choose one:
1. Test the OTP
2. Get the public key
3. Get flag
2
-----BEGIN PUBLIC KEY-----
MIGdMA0GCSqGSIb3DQEBAQUAA4GLADCBhwKBgQDA3o1RKoJI8uaShvCh6lqY6h70
ujF/ONqsWC7JNiztD82afJbT5rHlXC/OhFovo9yige4vkFw7ggEWDwcwUXwp0EWt
r4W/Nl1ab2vczLdrQq/0bSjBZTvckJBNkvtEXMda7busCHEa83A2NtBf8HaA4EVN
0PuyXJBAINcQqa0V6wIBAw==
-----END PUBLIC KEY-----

Choose one:
1. Test the OTP
2. Get the public key
3. Get flag
3
encrypted dat: 4100e68ae3ff9332246989ee751ade80c24060c4ee29547a76857f81cc060cdf91a5299fe9feee657a78c19415a2401114cff99135a74e0f5612044d50b5c174a73ac928462d0ebd010f8940898e0d3d61aae46e6ecb89599d2f4b74943d8d9f83401d263a9c86874d3ca354eadde5e7016d285f89468cdd3b88a16b10dbd600
send me otp to get flag >>> 974244003
MeePwnCTF{blackbox-rsa-is-0xd34d}
```