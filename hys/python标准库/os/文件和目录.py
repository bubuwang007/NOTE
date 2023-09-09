import os

# 1
if os.access('os.md', os.F_OK):
    print('os.md 存在')
else:
    print('os.md 不存在')

if os.access('1.txt', os.W_OK):
    print('1.txt 可写')
else:
    print('1.txt 不可写')

print(os.supports_effective_ids)