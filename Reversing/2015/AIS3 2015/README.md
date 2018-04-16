# AIS3 2015 - Notes

## ais3_crackme

[源自](https://github.com/angr/angr-doc/blob/master/examples/ais3_crackme/solve.py)

以他的 code 做研究，並記錄在自己這邊

執行的樣子:
```
root@lubun:/tmp/p# ./ais3_crackme asd
I'm sorry, that's the wrong secret key!
```

用 ida pro 看一下可以知道也是有一堆數學運算... ，輸入是以 argv[1]

用上面的 code 跑

```python
#!/usr/bin/env python 
import angr 
import claripy

target = 0x400602

p = angr.Project('./ais3_crackme')
argv1 = claripy.BVS('argv1',8*100)
## bit vector , size = 8 bit * 100 

initial_state = p.factory.entry_state(args=["./ais3_crackme",argv1])
## tell entry point , and define argument

sm = p.factory.simulation_manager(initial_state)

sm.explore(find=target)
found = sm.found[0]
solution = found.solver.eval(argv1, cast_to=str)

print solution
```