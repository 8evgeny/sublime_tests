# s = {'apple', 'orange', 'apple', 'pear', 'orange', 'banana'}
# s2 = set('hello')
# s3 = {i for i in range(1, 11)}
# s4 = set()
#
# print(s)
# print(s2)
# print(s3)
# print(s4)

# nums = [1, 2, 3, 3, 1, 2, 4, 5]
# nums2 = set(nums)
# print(nums2)

# a = set('abracadabra')
# b = set('alacazam')
#
# c = a - b # вычитание - убираем из a все буквы, которые есть в b
# d = a | b # объединение - буквы или в a или в b
# e = a & b # пересечение - буквы и в a и в b
# f = a ^ b # множество из элементов - буквы в a или b, но не в обоих
#
# print(a, b, c, d, e, f, sep='\n')

# set.copy() - возвращает копию множества
# set.add(elem) - добавляет элемент в множество
# set.remove(elem) - удаляет элемент из множества. KeyError, если такого элемента не существует
# set.discard(elem) - удаляет элемент, если он находится в множестве
# set.pop() - возвращает и удаляет первый элемент из множества. Так как множества не упорядочены, нельзя точно сказать, какой элемент будет первым.
# set.clear() - очистка множества

# s = {'apple', 'orange', 'apple', 'pear', 'orange', 'banana'}
# s.clear()
# print(s)
# s2 = s.copy()
#
# print(s, id(s))
# print(s2, id(s2))

a = frozenset('hello')
print(a)



