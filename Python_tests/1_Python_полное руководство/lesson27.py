# def set_register(s):
#     if ' ' in s:
#         return s.upper()
#     else:
#         return s.lower()
#
# print(set_register('Hello world'))
# print(set_register('Hello,world'))


# def get_sum(a=0, b=0, c=0, d=1):
#     return a + b + c + d
#
#
# print(get_sum(1, 2, d=5))


# def get_sum(*args):
#     return sum(args)
#
#
# print(get_sum(1, 5, 10))


# def func(**kwargs):
#     print(kwargs)
#
# func(a=1, b=5, c=20)


def f(a, x, *args, **kwargs):
    print(a)
    print(x)
    print(args)
    print(kwargs)


f(1, 2, 3, 4, b='test', c='hi')
f(1, 2)


