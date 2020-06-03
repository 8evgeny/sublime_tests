def decor(func):
  def wrap():
    print("============")
    func()
    print("============")
  return wrap

def print_text():
  print("Hello world!")

decorated = decor(print_text)
decorated()

print_text = decor(print_text)
print_text()

def print_text():
  print("Hello world!")
print_text = decor(print_text)

@decor
def print_text():
  print("Hello world!")