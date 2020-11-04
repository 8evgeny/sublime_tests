from classes import Person

person1 = Person('John')
person1.print_info()

person2 = Person('Katy')
# print(person2.__age)
# print(person2._Person__age)
# print(person2.get_age())
# person2.set_age(25)
print(person2.age)
person2.age = 35
person2.print_info()
