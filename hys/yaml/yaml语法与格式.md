### 基本语法

- 以 `k: v` 的形式来表示键值对的关系，**冒号后面必须有一个空格**
- `#` 表示注释
- 对大小写敏感
- 通过缩进来表示层级关系，**缩排中空格的数目不重要，只要相同阶层的元素左侧对齐就可以了**
- 缩进只能使用空格，不能使用 `tab` 缩进键
- 字符串可以不用双引号



### 格式

通过 `yaml.load()` 解析

#### 对象和键值对

通过 `k: v` 的方式表示对象或者键值对，冒号后必须要加一个空格：

~~~yaml
Name: Astron
Sex: female
School: TJU
~~~

通过缩进来表示对象的多个属性：

~~~yaml
People: 
    Name: Astron
    Sex: female
    School: TJU
~~~

也可以写成

~~~yaml
people: {name: Astron, sex: female}
~~~



#### 数组

数组（或者列表）中的**元素采用 `-` 表示**，以 `-` 开头的行表示构成一个数组

~~~yaml
- A
- B
- C
~~~

~~~yaml
people: 
    - yyy
    - zzz
    - www
~~~

行内表示：

~~~yaml
people: [yyy, zzz, www]
~~~

对象数组:

~~~yaml
people: 
    - 
      name: yyy
      age: 18
    - 
      name: zzz
      age: 19
~~~

使用流式表示:

~~~yaml
people: [{name: yyy, age: 18},{name: zzz, age: 19}]
people: [
    {name: yyy, age: 18},
    {name: zzz, age: 19}
]
~~~



#### 标量

标量是最基本的不可再分的值，包括：

- 整数
- 浮点数
- 字符串
- 布尔值
- Null
- 时间
- 日期

~~~yaml
int:
	- 123
    - 0b1010_0111_0100_1010_1110    #二进制表示

float:
	- 3.14
	- 3.25e+5 # 科学计数法
   
string: "123"
string: '\n'

boolean: true
boolean:
	- true # 大小写都可以
    - false

none: Null
none: null

date: 2020-01-01 # 格式为 yyyy-MM-dd

datetime: 2020-01-10T15:02:08+08:00 # 日期和时间使用T连接，+表示时区
~~~



#### 引用

`&` 用于建立锚点，`*` 用于引用锚点，`<<` 表示合并到当前数据

~~~yaml
defaults: &defaults
   adapter: ppp
   host: qqq

development: 
   database: mq
   <<: *defaults
~~~

等于

~~~yaml
defaults:
   adapter: ppp
   host: qqq

development: 
   database: mq
   adapter: ppp
   host: qqq
~~~



#### 文档块

yaml文档可以通过 `---` 来划分文档，并且可以选择 使用 `...` 来结束文档块。可以使用 `yaml.load_all()` 得到一个迭代器来解析全部的文档。

~~~yaml
---
development: 
   database: mq
...

---
production: 
   database: mq
...
~~~

~~~python
import yaml

with open('test.yml', 'r', encoding='u8') as f:
    data = list(yaml.load_all(f, Loader=yaml.FullLoader))
~~~

