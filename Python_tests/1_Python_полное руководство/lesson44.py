# https://ru.wikipedia.org/wiki/%D0%A0%D0%B5%D0%B3%D1%83%D0%BB%D1%8F%D1%80%D0%BD%D1%8B%D0%B5_%D0%B2%D1%8B%D1%80%D0%B0%D0%B6%D0%B5%D0%BD%D0%B8%D1%8F

# https://docs.python.org/3/library/re.html

import re

# s = 'Это просто строка текста. А это ещё одна строка текста.'
# pattern = 'строка'

# if re.search(pattern, s):
#     print('Matched')
# else:
#     print('No match')
#
# match = re.search(pattern, s)
# print(match.start())
# print(match.end())


# print(re.match(pattern, s))

# print(re.findall(pattern, s))

# print(re.split(r'\.', s, 1))


s = '''Это просто строка текста.
А это ещё одна строка текста.
А это строка с цифрами: 1, 2, 3, 4, 5, 6, 7, 8, 9, ٣, 0, 10
А это строка с разными символами: "!", "@", "-", "&", "?", "_"
a\\b\tc
test string'''

# pattern = r'\w+'
# pattern = r'[а-яё]+'
# pattern = r'[0-9]+'
# pattern = r'\d+'
# pattern = r'[\da-]+'
# pattern = r'a\\b\tc'
# pattern = r'\w+$'

# print(re.findall(pattern, s, flags=re.IGNORECASE))

# mail@mail.com
# kudlay@bank
# mail@google.com.ua


def validate_email(email):
    return re.match(r'^.+@(\w+\.){0,2}[a-z]{2,6}$', email, re.IGNORECASE)


print(validate_email('mail@mail.com'))
print(validate_email('ivanov@bank'))
print(validate_email('mail@google.com.ua'))
print(validate_email('mail@google.com.infotest'))




