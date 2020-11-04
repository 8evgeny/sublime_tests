# words = ['мадам', 'топот', 'test', 'madam', 'word']

#palindromes = []

# for word in words:
#     if word == word[::-1]:
#         palindromes.append(word)

# palindromes = [word for word in words if word == word[::-1]]
#
# print(palindromes)

# my_str = ['Око за око', 'А роза упала на лапу Азора', 'Около Миши молоко']
# palindromes = []
# for word in my_str:
#     word_r = word.replace(' ', '').lower()
#     if word_r == word_r[::-1]:
#         palindromes.append(word)
#
# print(palindromes)

l = list(range(1, 10))
l2 = list('hello')

print(l, l2)

s = '-'.join(map(str, l))
s2 = ','.join(l2)

print(s)
print(s2)
