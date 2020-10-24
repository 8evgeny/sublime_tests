a, b, c = 5, 6, 7

if a > b:
	print("Yeah, A > B")
elif b > c:
	print("B > C")
	print("Blah-blah-blah...")
else:
	print("A <= B")
	if b < c:
		print("B < C")
		print("Something else...")
