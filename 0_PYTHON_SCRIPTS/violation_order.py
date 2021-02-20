path_to_write = "/home/jhon/Desktop/"
# print ("Введите код нарушения (0 - проезды):")
# code_input = input()
code_input = 0
# print ("Введите адрес хоста")
# host = input()
host = "localhost"
import psycopg2
try:
    connection = psycopg2.connect(
      database="sadko",
      user="postgres",
      password="",
      host=host,
      port="5432"
    )
    print("Подключение к базе успешно\n")
    cur = connection.cursor()
    count = "SELECT count(*) from violation_order where violation_code  = " + str(code_input)
    cur.execute(count)
    row = cur.fetchall()
    print("Записей в базе данных с кодом ",code_input," - ", row[0])

    reqest = '''
    SELECT
    uid,fixation_timestamp
    FROM violation_order
    where violation_code  = 
    '''\
    + str(code_input) + \
    '''
    ORDER BY fixation_timestamp 
    '''
    cur.execute(reqest)
    rows = cur.fetchall()
    # filename=
    file = open(path_to_write+"newfile.txt", "w")

    file.write("\n")
    for row in rows:
        file.write(str(row[0])+'\t\t\t\t\t'+str(row[1])+'\n')
    print("Результаты запроса сохранены в файл: ",path_to_write+"newfile.txt")
except psycopg2.Error as e:
        print("Ошибка запроса:\n", e.args[0])
else:
    connection.commit()
    connection.close()


