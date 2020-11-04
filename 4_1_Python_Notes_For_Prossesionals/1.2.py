# Integer
a = 2
print(a)
# Output: 2
# Integer
b = 9223372036854775807
print(b)
# Output: 9223372036854775807
# Floating point
pi = 3.14
print(pi)
# Output: 3.14
# String
c = 'A'
print(c)
# Output: A
# String
name = 'John Doe'
print(name)
# Output: John Doe
# Boolean
q = True
print(q)
# Output: True
# Empty value or null data type
x = None
print(x)
# Output: None

import keyword
print(keyword.kwlist)
a = 2
print(type(a))
# Output: <type 'int'>
b = 9223372036854775807
print(type(b))
# Output: <type 'int'>
pi = 3.14
print(type(pi))
# Output: <type 'float'>
c = 'A'
print(type(c))
# Output: <type 'str'>
name = 'John Doe'
print(type(name))
# Output: <type 'str'>
q = True
print(type(q))
# Output: <type 'bool'>
x = None
print(type(x))

a, b, c = 1, 2, 3
print(a, b, c)
# Output: 1 2 3

a, b, _ = 1, 2, 3
print(a, b)
# Output: 1, 2

a = b = c = 1
print(a, b, c)
# Output: 1 1 1

a = b = c =  1
 # all three names a, b and c refer to same int object with value 1
print(a, b, c)
# Output: 1 1 1
b = 2
 # b now refers to another int object, one with a value of 2
print(a, b, c)
# Output: 1 2 1 # so output is as expected.

x = y = [7, 8, 9] # x and y refer to the same list object just created, [7, 8, 9]
x = [13, 8, 9]    # x now refers to a different list object just created, [13, 8, 9]
print(y)           # y still refers to the list it was first assigned
# Output: [7, 8, 9]

x = y = [7, 8, 9]  # x and y are two different names for the same list object just created, [7, 8, 9]
x[0] = 13  # we are updating the value of the list [7, 8, 9] through one of its names, x in this case
print(y)  # printing the value of the list using its other name
# Output: [13, 8, 9]  

x = [1, 2, [3, 4, 5], 6, 7] # this is nested list
print (x[2])
# Output: [3, 4, 5]
print (x[2][1])
# Output: 4

a = 2
print(a)
# Output: 2
a = "New value"
print(a)
# Output: New value






