def numbers(x):
  for i in range(x):
    if i % 2 == 0:
      yield i

print(list(numbers(20)))

def make_word():
  word = ""
  for ch in "spam":
    word +=ch
    yield word

print(list(make_word()))