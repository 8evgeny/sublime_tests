from classes import Person, Employee

person = Person('Katy', 30)
person.age = 35
person.print_info()
print(person)


employee = Employee('Nick', 30, 'Google')
employee.print_info()
employee.more_info()
print(employee)
