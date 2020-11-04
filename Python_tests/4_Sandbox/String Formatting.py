'''
So far, to combine strings and non-strings, you've converted the non-strings to 
strings and added them. String formatting provides a more powerful way to embed 
non-strings within strings. String formatting uses a string's format method to 
substitute a number of arguments in the string.
Each argument of the format function is placed in the string at the corresponding 
position, which is determined using the curly braces { }.
'''

# string formatting
nums = [4, 5, 6]
msg = "Numbers: {0} {1} {2}". format(nums[0], nums[1], nums[2])
print(msg)

print("{0}{1}{0}".format("abra", "cad"))

str="{c}, {b}, {a}".format(a=5, b=9, c=7)
print(str)