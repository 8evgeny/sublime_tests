import random
# Использование модуля random
for i in range(20):
   value = random.randint(1, 1000)
   print(value, )
print('\n')
for i in range(5):
   value = random.uniform(1, 8)
   print(value, end=',')
print('\n')

# Импорт из модуля math одной переменной pi и дальнейшее её использование !!!!
# Можно импортировать несколько переменных (через запятую) или все, мспользуя *
from math import pi
print(pi)  
print('\n')

#  Импортированной переменной присваиваем свое имя
from math import sqrt as square_root
print(square_root(100))

# There are three main types of modules in Python, those you write yourself, 
# those you install from external sources, and those that are preinstalled with Python. 
# The last type is called the standard library, and contains many useful modules. 
# Some of the standard library's useful modules include 
# string, re, datetime, math, random, os, multiprocessing, subprocess, socket, 
# email, json, doctest, unittest, pdb, argparse and sys.

# Tasks that can be done by the standard library include string parsing, data serialization, 
# testing, debugging and manipulating dates, emails, command line arguments, and much more!

# Many third-party Python modules are stored on the Python Package Index (PyPI). 
# The best way to install these is using a program called pip. This comes installed by default with modern distributions of Python. 
# If you don't have it, it is easy to install online. Once you have it, installing libraries from PyPI is easy. 
# Look up the name of the library you want to install, go to the command line 
# (for Windows it will be the Command Prompt), and enter pip install library_name. 
# Once you've done this, import the library and use it in your code.