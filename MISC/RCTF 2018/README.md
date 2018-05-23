# RCTF 2018 - Notes

## Git

首先到 `cd git/.git/logs` ，然後看 HEAD

```
# cat HEAD
0000000000000000000000000000000000000000 22d3349a5c6fe45758daba276108137382a01caa zsx <zsx@zsxsoft.com> 1526187274 +0800        commit (initial): Initial Commit
22d3349a5c6fe45758daba276108137382a01caa 22d3349a5c6fe45758daba276108137382a01caa zsx <zsx@zsxsoft.com> 1526187289 +0800        checkout: moving from master to rctf
22d3349a5c6fe45758daba276108137382a01caa f4d0f6ddf6660f5c9273c84f3de64840a407bef1 zsx <zsx@zsxsoft.com> 1526187319 +0800        commit: Flag
f4d0f6ddf6660f5c9273c84f3de64840a407bef1 f671986f9aaa4fc49d8f3eba916d7947dc9f7e46 zsx <zsx@zsxsoft.com> 1526187331 +0800        commit: Revert
f671986f9aaa4fc49d8f3eba916d7947dc9f7e46 22d3349a5c6fe45758daba276108137382a01caa zsx <zsx@zsxsoft.com> 1526187346 +0800        checkout: moving from rctf to master
22d3349a5c6fe45758daba276108137382a01caa f671986f9aaa4fc49d8f3eba916d7947dc9f7e46 zsx <zsx@zsxsoft.com> 1526187455 +0800        checkout: moving from master to develop
f671986f9aaa4fc49d8f3eba916d7947dc9f7e46 22d3349a5c6fe45758daba276108137382a01caa zsx <zsx@zsxsoft.com> 1526187488 +0800        checkout: moving from develop to master
22d3349a5c6fe45758daba276108137382a01caa f671986f9aaa4fc49d8f3eba916d7947dc9f7e46 zsx <zsx@zsxsoft.com> 1526187817 +0800        checkout: moving from master to develop
f671986f9aaa4fc49d8f3eba916d7947dc9f7e46 22d3349a5c6fe45758daba276108137382a01caa zsx <zsx@zsxsoft.com> 1526187876 +0800        rebase -i (start): checkout 22d3349
22d3349a5c6fe45758daba276108137382a01caa 22d3349a5c6fe45758daba276108137382a01caa zsx <zsx@zsxsoft.com> 1526187876 +0800        rebase -i (finish): returning to refs/heads/develop
22d3349a5c6fe45758daba276108137382a01caa 22d3349a5c6fe45758daba276108137382a01caa zsx <zsx@zsxsoft.com> 1526187889 +0800        checkout: moving from develop to master

```

可以看到 f4d0f6ddf6660f5c9273c84f3de64840a407bef1 這邊有 FLAG

所以
```
git checkout f4d0f6ddf6660f5c9273c84f3de64840a407bef1
```

就可以看到當前目錄下有 flag.txt
```