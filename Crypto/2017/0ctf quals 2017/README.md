# 0ctf Quals 2017 - Notes

## Integrity
[參考](https://github.com/ctfs/write-ups-2017/tree/master/0ctf-quals-2017/crypto/integrity-75)

這題是登入 admin 就可以得到 flag

加密返回是 `iv || enc` ， enc = `md5(pad(user)) | pad(user)`

在 cbc mode 中，第一個 block 解密是 `iv xor aes.decrypt(ciphertext[0])`
![image](./img/cbc_de.png)

換句話說，如果有 iv 和 ciphertext[0] ，就可以解密

而如果我們在 register 送的是 `aes.decrypt(ciphertext[0])` ，就可以順利解密

而這題的第一個 block 是 md5(pad(user))

如果我們先註冊並送出 `md5(pad(admin)).digest() || admin`

則會得到 `iv || real_md5 || admin_md5 || admin`

之後我們用 login ，並給 `real_md5 || admin_md5 || admin`

則 read_md5 當 iv 去解 admin_md5 ，admin_md5 再去解 admin

## onetimepad

