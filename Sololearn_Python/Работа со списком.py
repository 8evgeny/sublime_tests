words = ['cat', 'window', 'defenestrate', 'абракадабра']
for w in words[:]:  # Loop over a slice copy of the entire list.
    if len(w) > 6:
        words.insert(0, w) # 0 это позиция вставки
print(words)

for w in words[:]:
    if len(w) < 7:
        words.append(w)
        print(words)

print('\n')
 # Measure some strings:
words = ['cat', 'window', 'defenestrate', 'абракадабра']
for w in words:
    print(w, len(w),end=' , ')
