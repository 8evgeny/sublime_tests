path_to_write = "/home/jhon/Desktop/"
print ("Введите код нарушения :")
# code_violation = input()
code_violation = 0
print ("Введите адрес хоста")
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

    cur.execute(reqest_passages)
    rows = cur.fetchall()
    file = open(path_to_write+"passages.csv", "w")
    for row in rows:
        file.write(str(row[1])[0:10]+";  "+str(row[1])[11:19]+';'+'  '+str(row[0])[0:36]+';'+'\n')
    file.close()

    cur.execute(reqest_violation)
    rows = cur.fetchall()
    file = open(path_to_write+"violations.csv", "w")
    for row in rows:
        file.write(str(row[1])[0:10]+";  "+str(row[1])[11:19]+';'+'  '+str(row[0])[0:36]+';'+'\n')
    file.close()
    print("Результаты запроса по проездам сохранены в файл: ",path_to_write+"passages.csv")
    print("Результаты запроса по нарушениям сохранены в файл: ", path_to_write + "violations.csv")
except psycopg2.Error as e:
        print("Ошибка запроса:\n", e.args[0])
else:
    connection.commit()
    connection.close()