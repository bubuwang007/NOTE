该模块提供了各种与时间相关的函数。相关功能还可以参阅 [`datetime`](https://www.bookstack.cn/read/python-3.10.0-zh/ab023c100d4bd692.md#module-datetime) 和 [`calendar`](https://www.bookstack.cn/read/python-3.10.0-zh/5b3e20962affdf7f.md#module-calendar) 模块。

尽管所有平台皆可使用此模块，但模块内的函数并非所有平台都可用。此模块中定义的大多数函数的实现都是调用其所在平台的C语言库的同名函数。因为这些函数的语义可能因平台而异，所以使用时最好查阅对应平台的相关文档。

下面是一些术语和惯例的解释.

- *epoch* 是时间开始的点，其值取决于平台。对于Unix， epoch 是1970年1月1日00:00:00（UTC）。要找出给定平台上的 epoch ，请查看 `time.gmtime(0)` 。

- 术语 *纪元秒数* 是指自 epoch （纪元）时间点以来经过的总秒数，通常不包括 [闰秒](https://en.wikipedia.org/wiki/Leap_second)。 在所有符合 POSIX 标准的平台上，闰秒都不会记录在总秒数中。

- 此模块中的函数可能无法处理纪元之前或遥远未来的日期和时间。“遥远未来”的定义由对应的C语言库决定；对于32位系统，它通常是指2038年及以后。

- 函数 [`strptime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.strptime) 在接收到 `%y` 格式代码时可以解析使用 2 位数表示的年份。当解析 2 位数年份时，函数会按照 POSIX 和 ISO C 标准进行年份转换：数值 69—99 被映射为 1969—1999；数值 0—68 被映射为 2000—2068。

- UTC是协调世界时（Coordinated Universal Time）的缩写。它以前也被称为格林威治标准时间（GMT）。使用UTC而不是CUT作为缩写是英语与法语（Temps Universel Coordonné）之间妥协的结果，不是什么低级错误。

- DST是夏令时（Daylight Saving Time）的缩写，在一年的某一段时间中将当地时间调整（通常）一小时。 DST的规则非常神奇（由当地法律确定），并且每年的起止时间都不同。C语言库中有一个表格，记录了各地的夏令时规则（实际上，为了灵活性，C语言库通常是从某个系统文件中读取这张表）。从这个角度而言，这张表是夏令时规则的唯一权威真理。

- 由于平台限制，各种实时函数的精度可能低于其值或参数所要求（或给定）的精度。例如，在大多数Unix系统上，时钟频率仅为每秒50或100次。

- 另一方面， [`time()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.time) 和 [`sleep()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.sleep) 的精度优于它们的Unix等价物：时间表示为浮点数，[`time()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.time) 返回最准确的时间 （使用Unix `gettimeofday()` 如果可用），并且 [`sleep()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.sleep) 将接受非零分数的时间（Unix `select()` 用于实现此功能，如果可用）。

- 时间值由 [`gmtime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.gmtime)，[`localtime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.localtime) 和 [`strptime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.strptime) 返回，并被 [`asctime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.asctime)， [`mktime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.mktime) 和 [`strftime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.strftime) 接受，是一个 9 个整数的序列。 [`gmtime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.gmtime)， [`localtime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.localtime) 和 [`strptime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.strptime) 的返回值还提供各个字段的属性名称。

  请参阅 [`struct_time`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.struct_time) 以获取这些对象的描述。

- 使用以下函数在时间表示之间进行转换：

  |                              从                              |                              到                              |                             使用                             |
  | :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
  |                       自纪元以来的秒数                       | UTC 的 [`struct_time`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.struct_time) | [`gmtime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.gmtime) |
  |                       自纪元以来的秒数                       | 本地时间的 [`struct_time`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.struct_time) | [`localtime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.localtime) |
  | UTC 的 [`struct_time`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.struct_time) |                       自纪元以来的秒数                       | [`calendar.timegm()`](https://www.bookstack.cn/read/python-3.10.0-zh/5b3e20962affdf7f.md#calendar.timegm) |
  | 本地时间的 [`struct_time`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.struct_time) |                       自纪元以来的秒数                       | [`mktime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.mktime) |



`time.asctime`([*t*])

转换由 [`gmtime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.gmtime) 或 [`localtime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.localtime) 所返回的表示时间的元组或 [`struct_time`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.struct_time) 为以下形式的字符串: `'Sun Jun 20 23:21:05 1993'`。 日期字段的长度为两个字符，如果日期只有一个数字则会以零填充，例如: `'Wed Jun 9 04:26:40 1993'`。

如果未提供 *t*，则会使用 [`localtime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.localtime) 所返回的当前时间。 [`asctime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.asctime) 不会使用区域设置信息。



`time.ctime`([*secs*])

转换以距离初始纪元的秒数表示的时间为以下形式的字符串: `'Sun Jun 20 23:21:05 1993'` 代表本地时间。 日期字段的长度为两个字符，如果日期只有一个数字则会以零填充，例如: `'Wed Jun 9 04:26:40 1993'`。

如果 *secs* 未提供或为 [`None`](https://www.bookstack.cn/read/python-3.10.0-zh/a385553acf159919.md#None)，则使用 [`time()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.time) 所返回的当前时间。 `ctime(secs)` 等价于 `asctime(localtime(secs))`。 [`ctime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.ctime) 不会使用区域设置信息。



`time.get_clock_info`(*name*)

获取有关指定时钟的信息作为命名空间对象。 支持的时钟名称和读取其值的相应函数是：

- `'monotonic'`: [`time.monotonic()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.monotonic)
- `'perf_counter'`: [`time.perf_counter()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.perf_counter)
- `'process_time'`: [`time.process_time()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.process_time)
- `'thread_time'`: [`time.thread_time()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.thread_time)
- `'time'`: [`time.time()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.time)

结果具有以下属性：

- *adjustable* ： 如果时钟可以自动更改（例如通过NTP守护程序）或由系统管理员手动更改，则为 `True` ，否则为 `False` 。
- *implementation* ： 用于获取时钟值的基础C函数的名称。有关可能的值，请参阅 [Clock ID 常量](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time-clock-id-constants) 。
- *monotonic* ：如果时钟不能倒退，则为 `True` ，否则为 `False` 。
- *resolution* ： 以秒为单位的时钟分辨率（ [`float`](https://www.bookstack.cn/read/python-3.10.0-zh/343ac5efc1fa2896.md#float) ）



`time.gmtime`([*secs*])

将以自 epoch 开始的秒数表示的时间转换为 UTC 的 [`struct_time`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.struct_time) ，其中 dst 标志始终为零。 如果未提供 *secs* 或为 [`None`](https://www.bookstack.cn/read/python-3.10.0-zh/a385553acf159919.md#None) ，则使用 [`time()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.time) 所返回的当前时间。 一秒以内的小数将被忽略。 有关 [`struct_time`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.struct_time) 对象的说明请参见上文。 有关此函数的逆操作请参阅 [`calendar.timegm()`](https://www.bookstack.cn/read/python-3.10.0-zh/5b3e20962affdf7f.md#calendar.timegm)。



`time.localtime`([*secs*])

与 [`gmtime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.gmtime) 相似但转换为当地时间。如果未提供 *secs* 或为 [`None`](https://www.bookstack.cn/read/python-3.10.0-zh/a385553acf159919.md#None) ，则使用由 [`time()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.time) 返回的当前时间。当 DST 适用于给定时间时，dst标志设置为 `1` 。



`time.mktime`(*t*)

这是 [`localtime()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.localtime) 的反函数。它的参数是 [`struct_time`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.struct_time) 或者完整的 9 元组（因为需要 dst 标志；如果它是未知的则使用 `-1` 作为dst标志），它表示 *local* 的时间，而不是 UTC 。它返回一个浮点数，以便与 [`time()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.time) 兼容。如果输入值不能表示为有效时间，则 [`OverflowError`](https://www.bookstack.cn/read/python-3.10.0-zh/177bd954d1cc6696.md#OverflowError) 或 [`ValueError`](https://www.bookstack.cn/read/python-3.10.0-zh/177bd954d1cc6696.md#ValueError) 将被引发（这取决于Python或底层C库是否捕获到无效值）。它可以生成时间的最早日期取决于平台。



`time.monotonic`() → [float](https://www.bookstack.cn/read/python-3.10.0-zh/343ac5efc1fa2896.md#float)

（以小数表示的秒为单位）返回一个单调时钟的值，即不能倒退的时钟。 该时钟不受系统时钟更新的影响。 返回值的参考点未被定义，因此只有两次调用之间的差值才是有效的。

使用 [`monotonic_ns()`](https://www.bookstack.cn/read/python-3.10.0-zh/c770715226a94b49.md#time.monotonic_ns) 以避免 [`float`](https://www.bookstack.cn/read/python-3.10.0-zh/343ac5efc1fa2896.md#float) 类型导致的精度损失。