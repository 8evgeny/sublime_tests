'''
This is an example project, showing a program that analyzes a sample file
to find what percentage of the text each character occupies.
This section shows how a file could be open and read.
'''
filename = input("Enter a filename: ")
# вводить new.txt
with open(filename) as f:
   text = f.read()
print(text)


def count_char(text, char): # количество символов в строке
  count = 0
  for c in text:
    if c == char:
      count += 1
  return count

filename = input("Enter a filename: ")
with open(filename) as f:
  text = f.read()

print(count_char(text, "!"))
