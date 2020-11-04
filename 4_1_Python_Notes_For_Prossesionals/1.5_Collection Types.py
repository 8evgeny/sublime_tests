# Examples of immutable Data Types:
# int, long, float, complex
# str
# bytes
# tuple
# frozenset

# Examples of mutable Data Types:
# bytearray
# list
# set
# dict

#list
int_list = [1, 2, 3]
string_list = ['abc', 'defghi']
empty_list = []  # A list can be empty
mixed_list = [1, 'abc', True, 2.34, None]

names = ['Alice', 'Bob', 'Craig', 'Diana', 'Eric']
print(names[0]) # Alice
print(names[2]) # Craig
print(names[-1]) # Eric
print(names[-4]) # Bob

names[0] = 'Ann'
print(names)
# Outputs ['Ann', 'Bob', 'Craig', 'Diana', 'Eric']

names = ['Alice', 'Bob', 'Craig', 'Diana', 'Eric']
names.append("Sia")
print(names)
# Outputs ['Alice', 'Bob', 'Craig', 'Diana', 'Eric', 'Sia']

names.insert(1, "Nikki")
print(names)
# Outputs ['Alice', 'Nikki', 'Bob', 'Craig', 'Diana', 'Eric', 'Sia']

names.remove("Bob")
print(names) # Outputs ['Alice', 'Nikki', 'Craig', 'Diana', 'Eric', 'Sia']

print(names.index("Alice")) # 0

print(len(names)) #6

a = [1, 1, 1, 2, 3, 4]
print(a)
print(a.count(1)) #3
a.reverse()
print(a) 
# or
a[::-1] # ?
print(a) 

print(names.pop()) # Outputs 'Sia'
print(names)

# You can iterate over the list elements like below:
for element in names:
	print (element)

# Tuples   A tuple is similar to a list except that it is fixed-length and immutable

ip_address = ('10.20.30.40', 8080)
one_member_tuple = ('Only member',)
# or
one_member_tuple = 'Only member', # No brackets
one_member_tuple = tuple(['Only member'])

# Dictionaries   is a collection of key-value pairs

state_capitals = {
'Arkansas': 'Little Rock',
'Colorado': 'Denver',
'California': 'Sacramento',
'Georgia': 'Atlanta'
}

ca_capital = state_capitals['California']
print (ca_capital)

# You can also get all of the keys in a dictionary and then iterate over them:
for k in state_capitals.keys():
	print('{} is the capital of {}'.format(state_capitals[k], k))

# set     collection of elements with no repeats and without insertion order but sorted order.

first_names = {'Adam', 'Beth', 'Charlie'}
# Or you can build a set using an existing list:
my_list = [1,2,3,3]
print(my_list)
my_set = set(my_list)
print(my_set)

# defaultdict

state_capitals = {
'Arkansas': 'Little Rock',
'Colorado': 'Denver',
'California': 'Sacramento',
'Georgia': 'Atlanta'
}

ca_capital = state_capitals['California']
print (ca_capital)

from collections import defaultdict
state_capitals = defaultdict(lambda: 'Boston')

ca_capital = state_capitals['Alabama']
print (ca_capital)




















