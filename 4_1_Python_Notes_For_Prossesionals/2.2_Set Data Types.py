# Sets are unordered collections of unique objects, there are two types of set:

# 1. Sets - They are mutable and new elements can be added once sets are defined

basket = {'apple', 'orange', 'apple', 'pear', 'orange', 'banana'}
print(basket)  # duplicates will be removed  # > {'orange', 'banana', 'pear', 'apple'}
a = set('abracadabra')
print(a)  # unique letters in a  # > {'a', 'r', 'b', 'c', 'd'}
a.add('z')
print(a)   # > {'a', 'c', 'r', 'b', 'z', 'd'}

# 2. Frozen Sets - They are immutable and new elements cannot added after its defined.

b = frozenset('asdfagsa')
print(b) # > frozenset({'f', 'g', 'd', 'a', 's'})
cities = frozenset(["Frankfurt", "Basel","Freiburg"])
print(cities)  # > frozenset({'Frankfurt', 'Basel', 'Freiburg'})




























