import re

re_sub = re.compile(r'\[(.*?)\]\(.*?\)')
string = 'environ 的字节版本：一个 mapping 对象，其中键值都是 bytes 对象，代表进程环境。 environ 和 environb 是同步的（修改 environb 会更新 environ，反之亦然）。'
print(re_sub.sub(r'\1', string))