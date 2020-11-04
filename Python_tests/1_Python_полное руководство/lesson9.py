s = r'C:\d\new.txt'
print(s)

s = 'Py' 'thon'
print(s)

s1 = 'Hello, '
s2 = 'world!'
s3 = s1 + s2
print(s3)

name = 'John'
age = 20

print('My name is ' + name + " I'm " + str(age))

print('hi ' * 5)

s = 'Hello world!'
print(s[0])
print(s[-12])
# s[0] = 'D'

'''
+---+---+---+---+---+---+---+---+---+---+---+---+
| H | e | l | l | o |   | w | o | r | l | d | ! |
+---+---+---+---+---+---+---+---+---+---+---+---+
0   1   2   3   4   5   6   7   8   9  10  11  12
-12 -11 -10 -9  -8  -7  -6  -5  -4  -3  -2 -1
'''
#[X:Y:Z]

s = 'Hello world!'

print(s[0:12]) #Hello world!
print(s[-1]) #!
print(s[0:5]) #Hello
print(s[:5]) #Hello
print(s[6:]) #world!
print(s[::2]) #Hlowrd
print(s[::-1]) #!dlrow olleH
print(s[:5] + s[6:]) #Helloworld!