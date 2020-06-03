file = open("newfile.txt", "w")
file.write("This has been written to a file") #To write to files you use the write method, which writes a string to the file.
file.write("\n")
for i in range(21):
	print(i)
	file.write(str(i+1))  # Число в строку
	file.write("  SPAM!" "\n")

file.close()

file = open("newfile.txt", "r")
print(file.read())
file.close()

a = len(open("newfile.txt").readlines())
print (a)

# The "w" mode will create a file, if it does not already exist.
file = open("new.txt", "w")
file.write("Python  COOL!!!!!!  RAHU!!!!")
file.close()

file = open("new.txt", "r")
print(" file 'new' created!!!!!")
print(file.read())
file.close()


file = open("G:\\1\\Python\\files_fo_primery\\new1.txt", "w")
file.write("Python  COOL!!!!!!  RAHU!!!!")
file.close()

file = open("G:\\1\\Python\\files_fo_primery\\new1.txt", "r")
print(" file 'new' created!!!!!")
print(file.read())
file.close()

