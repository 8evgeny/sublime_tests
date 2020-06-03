a_dict = {1:"one", 2:"two", 3:"three"}
keys = a_dict.keys()
keys = sorted(keys)  #Сортировка
for key in keys:
    print(key, end=',')

print('\n')

a = ['Mary', 'had', 'a', 'little', 'lamb']
for i in range(len(a)):
    print(i, a[i])
