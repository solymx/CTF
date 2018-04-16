# Pragyan CTF 2018 - Notes

## Xmen OR the avengers 
> Description:
>
> the legion of doom is expecting an impending attack from a group of superheroes. they are not sure if it is the Xmen OR the avengers. they have received some information from a spy, a zip file containing the following files:
>
> info_crypt.txt
> info_clear.txt
> superheroes_group_info_crypt.txt
>
> help the legion of doom in decrypting the last file so they can prepare themselves and prevent their impending doom.

> Hint:
> Note: The key for the second decryption is the MD5 hash of the first resulting file.

先把題目給的 xor 出來可以得到提示，之後照著提示走即可


```python
#!/usr/bin/env python
from pwn import *
from Crypto.Cipher import AES
import hashlib
import base64

p = open('info_clear.txt').read()
c = open('info_crypt.txt').read()
ciphertext = open('superheroes_group_info_crypt.txt').read()
ciphertext = base64.b64decode(ciphertext.strip())
k = xor(p,c).strip()
key = hashlib.md5(k).hexdigest()

print AES.new(key, AES.MODE_ECB).decrypt(ciphertext)

```

## Improper encryption - Not done
> Description:
>
> Two brothers, Shivam and Mit were fighting for the only computer they had in their house. Watching this their father got angry and locked the computer with a strong password of length 28 which consists of alphabets. To unite them he gave them a puzzle to solve.
> 
> He used two random strings and added the half-half of password in each string at some random position. He wanted to apply one-time-pad on both strings . So he used a smaller key 'k' of length 14(contains only english alphabets), and used some pseudo random generator, to get a longer key(K) of suitable size. Then he XOR each string with the generated key(K),and get encrypted message M1, and M2. He gave Shivam M1 and Mit M2 and asked them to find the password.
> Also, to help them he also generated a string of suitable size by repeating k several times and then applied one time pad on it by larger key(K) to get M3.
> 
> Shivam and Mit come to you with M1, M2, and M3. Help them find the password.
> 
> M1=2d142303073d05392c3d3e273c2a1a211f082b280d2d0e332025380301352a122a151c3a342e362d2723171904011c0c0c292b3d0122063e2e1e2a08102a2d3d0b2e102123141c280f0c373d2b380d3d0301301f2d281935233239330f3a102b123b0d2a
> M2=29190f1b18390707093a290b2d0b113f37332533333a0c3d1a29160a2f100a1d0034323b1b2e1225252500182531391d13260c21211019242d0a0a123b362d232d3a3a0a083c0e363c183a032b332d252c5637252d047b522a1e462a2a2909081705033d
> M3=15350a23053f04272a2f12113a2137202a3022081616090c32162b0b32333413161725072508391f3c36192e1e1e37030b361a2a26163337130628020b34352d1a2e143d3f0a1b1d13012a19223c2b1f0c172b3406033808061d1a2306133011080e1839

> First 14 letter of password is: sAldnJfpUGlciN


```python
#!/usr/bin/env python
from pwn import *

M1=0x2d142303073d05392c3d3e273c2a1a211f082b280d2d0e332025380301352a122a151c3a342e362d2723171904011c0c0c292b3d0122063e2e1e2a08102a2d3d0b2e102123141c280f0c373d2b380d3d0301301f2d281935233239330f3a102b123b0d2a
M2=0x29190f1b18390707093a290b2d0b113f37332533333a0c3d1a29160a2f100a1d0034323b1b2e1225252500182531391d13260c21211019242d0a0a123b362d232d3a3a0a083c0e363c183a032b332d252c5637252d047b522a1e462a2a2909081705033d
M3=0x15350a23053f04272a2f12113a2137202a3022081616090c32162b0b32333413161725072508391f3c36192e1e1e37030b361a2a26163337130628020b34352d1a2e143d3f0a1b1d13012a19223c2b1f0c172b3406033808061d1a2306133011080e1839

```
