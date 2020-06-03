a=list(range(5))
print(a)  #вывод массива
a=list(range(5,10))
print(a)  #вывод массива
a=list(range(0, 20, 3))
print(a)  #вывод массива
a=list(range(-10, -100, -30))
print(a)  #вывод массива
print('\n')

for i in reversed(range(15)):  #обратная функция к range
    print(i,end=',')
print('\n')

#Доступ к объектам range по индексу
print(range(3)[1])
# Результат: 1
print(range(3)[2])
# Результат: 2  
print(range(3,20,3)[2])  