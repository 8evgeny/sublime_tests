from datetime import datetime
time = datetime.now()
print("Текущее время: ",time)
path_to_write = "/home/jhon/Desktop/"
print ("Введите код нарушения :")
code_violation = input()
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
    cur = connection.cursor()
    print("Подключение к базе успешно\n")

    count_passages = "SELECT count(*) from violation_order where violation_code  = 0"
    cur.execute(count_passages)
    row = cur.fetchall()
    print("В базе данных проездов -", str(row[0])[1:-2])

    count_violations = "SELECT count(*) from violation_order where violation_code  = " + str(code_violation)
    cur.execute(count_violations)
    row = cur.fetchall()
    print("В базе данных нарушений с кодом",code_violation," -", str(row[0])[1:-2])

    reqest_passages = '''
    SELECT
    uid,fixation_timestamp
    FROM violation_order
    where violation_code  = 0
    ORDER BY fixation_timestamp 
    '''
    reqest_violation = '''
    SELECT
    uid,fixation_timestamp
    FROM violation_order
    where violation_code  = 
    '''\
    + str(code_violation) + \
    '''
    ORDER BY fixation_timestamp 
    '''
    name1 = path_to_write + str(time.year) + "_" + str(time.month) + "_" + \
            str(time.day) + "_" + str(time.hour) + str(time.minute) + \
            str(time.second) + "_" + "passages.csv"
    name2 = path_to_write + str(time.year) + "_" + str(time.month) + "_" + \
            str(time.day) + "_" + str(time.hour) + str(time.minute) + \
            str(time.second) + "_" + "violations_code" + str(code_violation)+".csv"
    cur.execute(reqest_passages)
    rows = cur.fetchall()
    file = open(name1, "w")
    for row in rows:
        file.write(str(row[1])[0:10]+";  "+str(row[1])[11:19]+';'+'  '+str(row[0])[0:36]+';'+'\n')
    file.close()

    cur.execute(reqest_violation)
    rows = cur.fetchall()
    file = open(name2, "w")
    for row in rows:
        file.write(str(row[1])[0:10]+";  "+str(row[1])[11:19]+';'+'  '+str(row[0])[0:36]+';'+'\n')
    file.close()
    print("Результаты запроса по проездам сохранены в файл: ", name1)
    print("Результаты запроса по нарушениям сохранены в файл: ", name2)
except psycopg2.Error as e:
        print("Ошибка запроса:\n", e.args[0])
else:
    connection.commit()
    connection.close()


