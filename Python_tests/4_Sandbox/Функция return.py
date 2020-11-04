def print_nums(x):
  for i in range(x):
    print(i, end=',')
    # return
print_nums(10)
print('\n')


def print_nums(x):
  for i in range(x):
    print(i,end=',')
    return
print_nums(10)
print('\n')

def func(x):
  res = 0
  for i in range(x):
     res += i  # res просуммирует все индексы 
  return res   # без этого оператора результат функции будет None
print(func(9))