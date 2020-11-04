from datetime import date, datetime, timedelta
import locale

# date
# today = date.today()
# print(today) # 2019-07-10
# print(today.day) # 10
# print(today.month) # 7
# print(today.year) # 2019
# print(today.weekday()) # 2019

# datetime
# now = datetime.now()
# now2 = datetime.today()

# print(now) # 2019-07-10 14:16:51.696373
# print(now.day) # 10
# print(now.month) # 7
# print(now.year) # 2019
# print(now.weekday()) # 2
# print(now.hour) # 14
# print(now.minute) # 16
# print(now.second) # 51

# days = ['пн', 'вт', 'ср', 'чт', 'пт', 'сб', 'вс']
# print(days[now.weekday()]) # ср

locale.setlocale(locale.LC_ALL, 'ru_RU.UTF-8')
# locale.setlocale(locale.LC_ALL, 'ru_RU')

# now = datetime.now()
# print(now)
#
# print(now.strftime('%a'))
# print(now.strftime('%A'))
#
# print(f'Дата: {now.strftime("%A, %d %b %Y")}')
# print(f'Время: {now.strftime("%H:%M:%S")}')
#
# print(now.strftime('%c'))
# print(now.strftime('%x'))
# print(now.strftime('%X'))

now = datetime.today()
print(now.strftime('%c'))
d1 = now + timedelta(days=1, hours=2, minutes=10)
print(d1.strftime('%c'))



# import random
#
# x = random.randint(1, 100)
# user_num = 0
# cnt = 0
#
# while True:
#     user_num = int(input('Я загадал число от 1 до 100 - угадай его: '))
#     cnt += 1
#     if user_num == x:
#         print(f'Ты угадал число за {cnt} попыток')
#         print("""
#                 ------------
#                 |           |
#                 |  0     0  |
#                 |     <     |
#                 |  .     .  |
#                 |   `...`   |
#                 ------------
#                 """)
#         if input('Сыграем еще? "y|n":') == 'y':
#             x = random.randint(1, 100)
#             cnt = 0
#         else:
#             print('Спасибо за игру')
#             break
#     elif user_num > x:
#         print('Мое число меньше')
#     else:
#         print('Мое число больше')
