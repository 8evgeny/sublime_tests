'''
Tuples are very similar to lists, except that they are immutable (they cannot be changed). 
Also, they are created using parentheses, rather than square brackets. 
You can access the values in the tuple with their index, just as you did with lists:
Trying to reassign a value in a tuple causes a TypeError.
Tuples can be created without the parentheses, by just separating the values with commas.
Example:
'''
words = ("spam", "eggs", "sausages",)
print(words[0])
words = "spam", "eggs", "sausages"
print(words[1])



# list
list = ["one", "two"]
 
# dictionary 
dict = {1:"one", 2:"two"}
 
# tuple 
tp = ("one", "two")

my_tuple = "one", "two", "three"
print(my_tuple[0])

tuple = (1, (1, 2, 3))
print(tuple[1])