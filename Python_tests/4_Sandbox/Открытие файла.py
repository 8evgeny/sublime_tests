file = open("filename.txt", "r")
cont = file.read()
print(cont)
file.close()
print('\n')

file = open("filename.txt", "r")
print(file.read(5),file.read(4),file.read(2),file.read())
file.close()
print('\n')

file = open("filename.txt", "r")
for i in range(27):
  print(file.read(4))  #когда файл заканчивается выводит пустые строки
file.close()
# print('\n')

file = open("filename.txt", "r")
str = file.read()
print (str)
print(len(str))
file.close()


file = open("filename.txt", "r")  # Печатает все строки
print(file.readlines())
file.close()


a = len(open("filename.txt").readlines())  # чмсло строк
print (a)