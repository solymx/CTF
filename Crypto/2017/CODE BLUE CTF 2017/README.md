# CODE BLUE CTF 2017 - Notes

## Common Modulus 1
> Description:
>
> We made RSA Encryption Scheme/Tester. Can you break it?

使用相同 n 加密同一個 m 且 e 不同又互質，完美符合 common modulus attack


## Common Modulus 2

跟第一題的差別在 e1 和 e2 不是互質，而是 gcd(e1, e2) = 3 

所以算出 m 之後還要開三次方根

## Common Modulus 3
