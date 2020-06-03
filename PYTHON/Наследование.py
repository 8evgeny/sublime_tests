'''
Inheritance provides a way to share functionality between classes. 
Imagine several classes, Cat, Dog, Rabbit and so on. Although they may differ in some ways (only Dog might have the method bark), they are likely to be similar in others (all having the attributes color and name). 
This similarity can be expressed by making them all inherit from a superclass Animal, which contains the shared functionality. 
To inherit a class from another class, put the superclass name in parentheses after the class name.
'''


class Animal: 
  def __init__(self, name, color):
    self.name = name
    self.color = color

class Cat(Animal):  # Класс наследует атрибуты суперкласса
  def purr(self):
    print("Purr...")
        
class Dog(Animal):
  def bark(self):
    print("Woof!")

fido = Dog("Fido", "brown")
print(fido.color)
fido.bark()

class A:
  def method(self):
    print(1)

class B(A):
  def method(self):
    print(2)
B().method()

#Вложенное наследование

class A:
  def method(self):
    print("A method")
    
class B(A):
  def another_method(self):
    print("B method")
    
class C(B):
  def third_method(self):
    print("C method")
c = C()
c.method()
c.another_method()
c.third_method()
print('\n')

class A:
  def a(self):
    print(1)
class B(A):
  def a(self):
    print(2)
class C(B):
  def c(self):
    print(3)
c = C()
c.a()
print('\n')

class A:
  def spam(self):
    print(1)

class B(A):
  def spam(self):
    print(2)
    super().spam()   #!!!! По имени (spam) ищется его метод в суперклассе объекта (А)
            
B().spam()