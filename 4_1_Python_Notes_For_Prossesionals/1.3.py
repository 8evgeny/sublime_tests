def my_function(): # This is a function definition. Note the colon (:)
	a = 2          # This line  belongs to the function because it's indented
	return a       # This line  also belongs to the same function 
print(my_function()) # This line is OUTSIDE the function block


# Converting between datatypes

a = '123'
b = int(a)

a = '123.456'
b = float(a)
# c = int(a) # ValueError: invalid literal for int() with base 10: '123.456'
d = int(b) # 123

a = 'hello'
print (list(a)) # ['h', 'e', 'l', 'l', 'o']
print (set(a)) # {'o', 'e', 'l', 'h'}
print (tuple(a)) # ('h', 'e', 'l', 'l', 'o')

def f(m):
	m.append(3)  # adds a number to the list. This is a mutation.
x = [1, 2]
f(x)
print(x == [1, 2])  # False now, since an item was added to the list









