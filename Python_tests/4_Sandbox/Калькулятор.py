x = float(input('число1 : '))
y = float(input('число2 : '))
oper = input('операция ? ')

rezult = None
if oper == '+':
    rezult = x + y
elif oper == '-':
    rezult = x - y
elif oper == '*':
    rezult = x * y
elif oper == '/':
    rezult = x / y
else:
    print("ошибка")

if rezult is not None:
    print('Результат', int(rezult))  # int - целое число
    print('Результат', rezult)
