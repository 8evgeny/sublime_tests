try:
   num1 = 7
   num2 = 0
   print (num1 / num2)
   print("Done calculation")
except ZeroDivisionError:
   print("An error occurred")
   print("due to zero division")

try:
  variable = 0
  print (10 / variable)
except ZeroDivisionError:
  print("Error")
print("Finished")

try:
   word = "spam"
   print(word / 0)
except:   # Перехватывает все ошибки
   print("An error occurred")


try:
   print("Hello")
   print(1 / 0)
except ZeroDivisionError:
   print("Divided by zero")
finally:  # Код выполняется всегда либо после блока try либо после блока except 
   print("This code will run no matter what")

try:
  print(1)
  assert 2 + 2 == 5
except AssertionError:
  print(3)
except:
  print(4)