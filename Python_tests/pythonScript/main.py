path_to_write = "/home/jhon/Desktop/results/"

from datetime import datetime
time = datetime.now()
code_violation = 0
print ("\n\nВведите адрес хоста")
host = input()
# host = "localhost"

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
    print("Подключение к комплексу "+str(host)+" - OK.\n")
    codes = "SELECT DISTINCT violation_code from violation_order"
    cur.execute(codes)
    codes_in_DB = cur.fetchall()
    for code in codes_in_DB:
        count_violations = "SELECT count(*) from violation_order where violation_code  = " + str(code)[1:-2]
        cur.execute(count_violations)
        row = cur.fetchall()
        print("В базе данных нарушений с кодом",str(code)[1:-2]," -", str(row[0])[1:-2])

        reqest_violation = '''
        SELECT
        uid,fixation_timestamp
        FROM violation_order
        where violation_code  = 
        '''\
        + str(code)[1:-2] + \
        '''
        ORDER BY fixation_timestamp 
        '''
        name = path_to_write + str(host) + "_" + str(time.year) + "." + str(time.month) + "." + \
            str(time.day) + "_" + str(time.hour) + "." + str(time.minute) + "." + \
            str(time.second) + "_" + "violations_code" + str(code)[1:-2]+".csv"
        cur.execute(reqest_violation)
        rows = cur.fetchall()
        file = open(name, "w")
        for row in rows:
            file.write(str(row[1])[0:10]+";  "+str(row[1])[11:19]+';'+'  '+str(row[0])[0:36]+';'+'\n')
        file.close()
        print("Результаты сохранены в файл: ", name)
except psycopg2.Error as e:
        print("Ошибка запроса:\n", e.args[0])
else:
    connection.commit()
    connection.close()