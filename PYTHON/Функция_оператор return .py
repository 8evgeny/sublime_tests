def max(x, y):
    if x >=y:
        return x
    else:
        return y
# Функция возвращает разные переменные в зависимости от условия
# return может использоваться только внутри функции
print(max(4, 7))
z = max(8, 5)
print(z)

def shortest_string(x, y):
  if len(x) <= len(y):
    return x
  else:
    return y
a='aaaaaaaa'
b='bbbbbbbbbbb'
print(shortest_string(a, b))

def add_numbers(x, y):
  total = x + y
  return total         #Возврат из функции и следующая строка не печатается
  print("This won't be printed")
print(add_numbers(4, 5))