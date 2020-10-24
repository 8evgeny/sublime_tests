l = [1, 2, 3, "hello"]
l = l + [4, 5, "world"]
print(l)
print (len(l), l[0], l[3])
l[1:3] = []
print(l)
l[1:3] = ["begin", "end"]
print(l)
l[2:2] = [3, 4]
print(l)
print(l[1:5])
print(l[:2])
print(l[2:])
print(l[-2])
print(l[-2:])
print(l[:-2])