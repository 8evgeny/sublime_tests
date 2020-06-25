squares = {1: 1, 2: 4, 3: "error", 4: 16,}
print(squares)
squares[8] = 64 # заносим ключ 8 и присваиваем ему значение 64
squares[3] = 9
print(squares)
print('\n')

nums = {
  1: "one",
  2: "two",
  3: "three",
}
print(1 in nums)
print("three" in nums)
print(4 not in nums)
print('\n')

# A useful dictionary method is get. It does the same thing as indexing, 
# but if the key is not found in the dictionary it returns another specified value instead ('None', by default).

pairs = {
1:             "apple",
"orange":      [2, 3, 4], 
True:          False, 
None:          "True",
}

print(pairs.get("orange"))
print(pairs.get(7))
print(pairs.get(12345, "not in dictionary"))
print('\n')


fib = {1: 1, 2: 1, 3: 2, 4: 3}
print(fib.get(4, 0) + fib.get(7, 5))  

