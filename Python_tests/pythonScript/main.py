# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.

import psycopg2

con = psycopg2.connect(
  database="sadko",
  user="postgres",
  password="",
  host="127.0.0.1",
  port="5432"
)

print("Database opened successfully")
cur = con.cursor()
cur.execute("SELECT * FROM violation_order LIMIT 2")

rows = cur.fetchall()
for row in rows:
    print("uid =", row[0])
    print("NAME =", row[1])
    print("AGE =", row[2])
    print("COURSE =", row[3])
    print("DEPARTMENT =", row[4], "\n")

print("Operation done successfully")
con.close()


# import psycopg2
# # conn = psycopg2.connect(dbname='sadko', user='postgres',password='', host='localhost')
# conn = psycopg2.connect(dbname='sadko', user='postgres')
# cursor = conn.cursor()
# cursor.execute('SELECT * FROM violation_order LIMIT 10')
# records = cursor.fetchall()
# for row in cursor:
#     print(row)
# cursor.fetchall()
# cursor.close()
# conn.close()

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
