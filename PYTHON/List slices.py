'''
List slices provide a more advanced way of retrieving values from a list. 
Basic list slicing involves indexing a list with two colon-separated integers. 
This returns a new list containing all the values in the old list between the indices.
List slices can also have a third number, representing the step, 
to include only alternate values in the slice.
'''

squares = [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
print(squares[2:6])
print(squares[3:8])
print(squares[0:1])
print('\n')

squares = [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
print(squares[:7])
print(squares[7:])
print('\n')

squares = [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
print(squares[::2])
print(squares[2:8:3])#[2:8:3] will include elements starting from the 2nd index up to the 8th with a step of 3.

print('\n')
squares = [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
print(squares[1:-1])

sqs = [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
print(sqs[7:5:-1])