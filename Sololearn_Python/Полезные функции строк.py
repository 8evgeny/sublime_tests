'''
Python contains many useful built-in functions and methods to accomplish common tasks. 
join - joins a list of strings with another string as a separator. 
replace - replaces one substring in a string with another.
startswith and endswith - determine if there is a substring at the start and end of a string, respectively. 
To change the case of a string, you can use lower and upper.
The method split is the opposite of join, turning a string with a certain separator into a list.

To find the maximum or minimum of some numbers or a list, you can use max or min.
To find the distance of a number from zero (its absolute value), use abs.
To round a number to a certain number of decimal places, use round.
To find the total of a list, use sum.

'''
print(", ".join(["spam", "eggs", "ham"])) #Объединение списка
#prints "spam, eggs, ham"

print("Hello ME".replace("ME", "world"))
#prints "Hello world"

print("This is a sentence.".startswith("This"))
# prints "True"

print("This is a sentence.".endswith("sentence."))
# prints "True"

print("This is a sentence.".upper())
# prints "THIS IS A SENTENCE."

print("AN ALL CAPS SENTENCE".lower())
#prints "an all caps sentence"

print("spam, eggs, ham".split(", "))   # Разделение списка
#prints "['spam', 'eggs', 'ham']"
print('\n')

print(min(1, 2, 3, 4, 0, 2, 1))
print(max([1, 4, 9, 2, 5, 6, 8]))
print(abs(-99))
print(abs(42))
print(sum([1, 2, 3, 4, 5]))


a=min([sum([11, 22]), max(abs(-30), 2)])
print(a)