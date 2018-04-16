### solution 1
```foremost certer.jpg```

### solution 2
```
root@lubun:/tmp/p# binwalk carter.jpg

DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
0             0x0             JPEG image data, JFIF standard 1.01
382           0x17E           Copyright string: "Copyright (c) 1998 Hewlett-Packard Company"
3192          0xC78           TIFF image data, big-endian, offset of first image directory: 8
140147        0x22373         JPEG image data, JFIF standard 1.01
140177        0x22391         TIFF image data, big-endian, offset of first image directory: 8

root@lubun:/tmp/p# dd if=./carter.jpg of=flag.jpg bs=1 skip=140147

```