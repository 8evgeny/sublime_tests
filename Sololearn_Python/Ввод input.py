x = int(input("Please enter an integer: ")) # преобразование в целое
if x < 0:
    x = 0
    print('Negative changed to zero')
elif x == 0:
    print('Zero')
elif x == 1:
    print('Single')
else:
    print('More')

print('\n')

name=input("whot i your name? ")
print('Hello', name)
