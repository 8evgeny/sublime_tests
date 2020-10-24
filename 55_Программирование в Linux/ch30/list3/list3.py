lst1 = ["a", "b", "c"]
lst2 = [1, 2, 3]
lst = ["hello", lst1, lst2, "goodbye"]
print(lst)
print(len(lst), len(lst[1]), len(lst[2]))
print(lst[1][0], lst[2][0])
lst[1][2] = "C"
print(lst)
lst[2][0], lst[2][1] = "one", "two"
print(lst)
