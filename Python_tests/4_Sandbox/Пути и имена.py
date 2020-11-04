# import sys
# print(sys.version_info)
# print(sys.version)

import cmath
x=cmath.sqrt(-1)
print(x)

import os
print(os.getcwd)
print(os.listdir(os.curdir))   # Содержимое текущего каталога Константа os.curdir возвращает строку, которая используется вашей системой для
#обозначения текущего каталога
os.chdir("/home/jhon/PycharmProjects/")       #Функция смены каталога
print(os.listdir(os.curdir))


import os
print(os.path.join('bin', 'utils', 'disktools')) #Иначе говоря, os.path.join позволяет формировать пути из последовательности каталогов или файлов, не беспокоясь о соглашениях текущей операционной системы.

import os
print(os.path.split(os.path.join('some', 'directory', 'path')))


with os.scandir(".") as my_dir:
	for entry in my_dir:
		print(entry.name, entry.is_file())