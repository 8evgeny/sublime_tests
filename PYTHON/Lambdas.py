#named function
def polynomial(x):
    return x**2 + 5*x + 4
print(polynomial(3))

#lambda
print((lambda x: x**2 + 5*x + 4) (3))


double = lambda x: x * 2
print(double(7))