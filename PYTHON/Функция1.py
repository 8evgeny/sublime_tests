def my_func():
    print("spam")
    print("spam")
    print("spam")
my_func()
print('\n')

def print_with_exclamation(word):
   print(word + "!")
print_with_exclamation("spam")
print_with_exclamation("eggs")
print_with_exclamation("python")
print('\n')

def function(variable): #Переменная определена только внутри функции
    variable += 1
    print(variable)
function(7)
print(variable)   #Здесь переменная не определена и выходит ошибка

