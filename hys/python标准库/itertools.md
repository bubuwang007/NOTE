# [`itertools`](https://www.bookstack.cn/read/python-3.10.0-zh/d230b7788e5c2742.md#module-itertools) — 为高效循环而创建迭代器的函数

本模块实现一系列 [iterator](https://www.bookstack.cn/read/python-3.10.0-zh/bd6b000ceb39b61e.md#term-iterator) ，这些迭代器受到APL，Haskell和SML的启发。为了适用于Python，它们都被重新写过。

本模块标准化了一个快速、高效利用内存的核心工具集，这些工具本身或组合都很有用。它们一起形成了“迭代器代数”，这使得在纯Python中有可能创建简洁又高效的专用工具。



## 无穷迭代器

|                            迭代器                            |     实参      |                结果                 |                 示例                 |
| :----------------------------------------------------------: | :-----------: | :---------------------------------: | :----------------------------------: |
| [`count()`](https://www.bookstack.cn/read/python-3.10.0-zh/d230b7788e5c2742.md#itertools.count) | start, [step] | start, start+step, start+2*step, …  |   `count(10) —> 10 11 12 13 14 …`    |
| [`cycle()`](https://www.bookstack.cn/read/python-3.10.0-zh/d230b7788e5c2742.md#itertools.cycle) |       p       |     p0, p1, … plast, p0, p1, …      | `cycle(‘ABCD’) —> A B C D A B C D …` |
| [`repeat()`](https://www.bookstack.cn/read/python-3.10.0-zh/d230b7788e5c2742.md#itertools.repeat) |   elem [,n]   | elem, elem, elem, … 重复无限次或n次 |     `repeat(10, 3) —> 10 10 10`      |

~~~python
import itertools as it

for i in it.count(-1):
    print(i)
    if i > 10:
        break

for i, j in zip(it.cycle([1,2,3,4]), it.count()):
    print(i, j)
    if j > 10:
        break

# 浅拷贝
li = list(it.repeat([0, 0], 10))
print(li)
~~~



## 根据最短输入序列长度停止的迭代器

|                            迭代器                            |            实参             |                      结果                      |                           示例                            |
| :----------------------------------------------------------: | :-------------------------: | :--------------------------------------------: | :-------------------------------------------------------: |
| [`accumulate()`](https://www.bookstack.cn/read/python-3.10.0-zh/d230b7788e5c2742.md#itertools.accumulate) |          p [,func]          |             p0, p0+p1, p0+p1+p2, …             |         `accumulate([1,2,3,4,5]) —> 1 3 6 10 15`          |
| [`chain()`](https://www.bookstack.cn/read/python-3.10.0-zh/d230b7788e5c2742.md#itertools.chain) |           p, q, …           |           p0, p1, … plast, q0, q1, …           |           `chain(‘ABC’, ‘DEF’) —> A B C D E F`            |
| [`chain.from_iterable()`](https://www.bookstack.cn/read/python-3.10.0-zh/d230b7788e5c2742.md#itertools.chain.from_iterable) |    iterable — 可迭代对象    |           p0, p1, … plast, q0, q1, …           |   `chain.from_iterable([‘ABC’, ‘DEF’]) —> A B C D E F`    |
| [`compress()`](https://www.bookstack.cn/read/python-3.10.0-zh/d230b7788e5c2742.md#itertools.compress) |       data, selectors       |       (d[0] if s[0]), (d[1] if s[1]), …        |      `compress(‘ABCDEF’, [1,0,1,0,1,1]) —> A C E F`       |
| [`dropwhile()`](https://www.bookstack.cn/read/python-3.10.0-zh/d230b7788e5c2742.md#itertools.dropwhile) |          pred, seq          | seq[n], seq[n+1], … 从pred首次真值测试失败开始 |     `dropwhile(lambda x: x<5, [1,4,6,4,1]) —> 6 4 1`      |
| [`filterfalse()`](https://www.bookstack.cn/read/python-3.10.0-zh/d230b7788e5c2742.md#itertools.filterfalse) |          pred, seq          |   seq中pred(x)为假值的元素，x是seq中的元素。   |   `filterfalse(lambda x: x%2, range(10)) —> 0 2 4 6 8`    |
| [`groupby()`](https://www.bookstack.cn/read/python-3.10.0-zh/d230b7788e5c2742.md#itertools.groupby) |       iterable[, key]       |            根据key(v)值分组的迭代器            |                                                           |
| [`islice()`](https://www.bookstack.cn/read/python-3.10.0-zh/d230b7788e5c2742.md#itertools.islice) | seq, [start,] stop [, step] |          seq[start:stop:step]中的元素          |         `islice(‘ABCDEFG’, 2, None) —> C D E F G`         |
| [`pairwise()`](https://www.bookstack.cn/read/python-3.10.0-zh/d230b7788e5c2742.md#itertools.pairwise) |    iterable — 可迭代对象    |           (p[0], p[1]), (p[1], p[2])           |        `pairwise(‘ABCDEFG’) —> AB BC CD DE EF FG`         |
| [`starmap()`](https://www.bookstack.cn/read/python-3.10.0-zh/d230b7788e5c2742.md#itertools.starmap) |          func, seq          |        func(*seq[0]), func(*seq[1]), …         |    `starmap(pow, [(2,5), (3,2), (10,3)]) —> 32 9 1000`    |
| [`takewhile()`](https://www.bookstack.cn/read/python-3.10.0-zh/d230b7788e5c2742.md#itertools.takewhile) |          pred, seq          |    seq[0], seq[1], …, 直到pred真值测试失败     |      `takewhile(lambda x: x<5, [1,4,6,4,1]) —> 1 4`       |
| [`tee()`](https://www.bookstack.cn/read/python-3.10.0-zh/d230b7788e5c2742.md#itertools.tee) |            it, n            |  it1, it2, … itn 将一个迭代器拆分为n个迭代器   |                                                           |
| [`zip_longest()`](https://www.bookstack.cn/read/python-3.10.0-zh/d230b7788e5c2742.md#itertools.zip_longest) |           p, q, …           |         (p[0], q[0]), (p[1], q[1]), …          | `zip_longest(‘ABCD’, ‘xy’, fillvalue=’-‘) —> Ax By C- D-` |

~~~python
import itertools as it

for i in it.accumulate([1, 2, 3, 4, 5]):
    print(i)

for i in it.chain([1, 2, 3, 4, 5], [7, 8, 9, 10]):
    print(i) 

for i in it.chain.from_iterable([[1, 2, 3, 4, 5], [7, 8, 9, 10]]):
    print(i)
    
for i in it.compress([1, 2, 3, 4, 5], [True, False, True, False, True]):
    print(i)
    
for i in it.dropwhile(lambda x: x < 5, [1, 4, 3, 2, 6, 4, 1, 2, 6]):
    print(i)

# 筛选假值
for i in it.filterfalse(lambda x: x < 5, [1, 4, 3, 2, 6, 4, 1, 2, 6]):
    print(i)
    
for i,j in it.groupby("aaaabbbbccccaaaa"):
    print(i, list(j))

li = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
for i in it.islice(li, 2, 7):
    print(i)
    
li = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
for i in it.takewhile(lambda x: x < 5, li):
    print(i)

def add(x, y):
    return x + y
paras = [(1, 2), (3, 4), (5, 6)]
res = it.starmap(add, paras)
print(list(res))

li = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
for i in it.takewhile(lambda x: x < 5, li):
    print(i)
~~~

