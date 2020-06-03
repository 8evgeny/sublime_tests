# When a file is opened in write mode, the file's existing content is deleted.
file = open("newfile.txt", "r")
print("Reading initial contents")
print(file.read())
print("Finished")
file.close()

file = open("newfile.txt", "w")
file.write("Some new text")
file.close()

file = open("newfile.txt", "r")
print("Reading new contents")
print(file.read())
print("Finished")
file.close()


# The write method returns the number of bytes written to a file, if successful.(file.write(msg) == len(msg))
msg = "Hello world! SPAM!!!!!!!!!!!!!!!!!"
file = open("newfile.txt", "w")
amount_written = file.write(msg)  #этой переменной присваивается колл записанного
print(amount_written)
file.close()
