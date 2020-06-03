def multiply(x, y):
   return x * y
a = 4
b = 7
operation = multiply
print(operation(a, b))

def shout(word):
   return word + "!"
speak = shout
output = speak("shout")
print(output)

def add(x, y):
  return x + y
def do_twice(func, x, y):
  return func(func(x, y), func(x, y))
a = 5
b = 10
print(do_twice(add, a, b))  
#do_twice  принимает функцию add в качестве аргумента и затем вызывает её

  
 
def square(x):
  return x * x
def test(func, x):
  print(func(x))
test(square, 8)