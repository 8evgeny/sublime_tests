a, b = 0, 1
while a < 1000:
	print(' ',a, end=',')
	a, b = b, a+b

print('\n')

for number in range(5):
    print(number)

print('\n')

for number in range(60):
    if number % 2 == 0:
        print(number, end=',')
