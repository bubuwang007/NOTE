import os

# 1
print('os.environ: ', os.environ)
print('os.environ["OS"]: ', os.environ['OS'])

os.environ['OS'] = '5'
print('os.environ["OS"]: ', os.environ['OS'])

os.putenv('OS', '6')
print('os.environ["OS"]: ', os.environ['OS'])

os.unsetenv('OS')
print('os.environ["OS"]: ', 'OS' in os.environ)


print('os.get_exec_path(): ', os.get_exec_path())

print('os.getegid(): ', os.getlogin())

# os.getppid()
print('os.getppid(): ', os.getppid())