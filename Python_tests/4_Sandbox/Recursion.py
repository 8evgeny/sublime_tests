def factorial(x):
  if x == 1:
    return 1
  else: 
    return x * factorial(x-1)
    
print(factorial(50))

# def sum_to(x):
#    return x + sum_to(x-1)
# print (sum_to(5))