# Pico CTF 2014 - Notes

## Droid App

用 jadx 反編譯後在 main 那邊可以看到 flag

## Redacted

用 pdftohtml 可以看到有一個 png 可以看到被蓋掉的地方

## SSH Backdoor

使用的 [tool](http://www.scootersoftware.com/) ，下載題目的和[正常的](http://ftp.openbsd.org/pub/OpenBSD/OpenSSH/portable/openssh-6.7p1.tar.gz)

比對可以看到

```c
static int frobcmp(const char *chk, const char *str) {
    int rc = 0;
    size_t len = strlen(str);
    char *s = xstrdup(str);
    memfrob(s, len);

    if (strcmp(chk, s) == 0) {
        rc = 1;
    }

    free(s);
    return rc;
}

int check_password(const char *password) {
    return frobcmp("CGCDSE_XGKIBCDOY^OKFCDMSE_XLFKMY", password);
}
```

解出來後可以知道要連去哪，並看 flag