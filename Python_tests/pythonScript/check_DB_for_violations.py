path_to_write = "lists_violations/"
# import calendar
from datetime import datetime , timedelta
time = datetime.now()
# print ("\n\nВведите адрес хоста")
# host = input()
# host = "localhost"
host = "10.8.1.93"
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
    print("Выберите интервал:")
    print("0 - все записи")
    print("1 - за год")
    print("2 - за 3 месяца")
    print("3 - за месяц")
    print("4 - за неделю")
    print("5 - за 3 суток")
    print("6 - за сутки")
    print("7 - за 3 часа")
    print("8 - за 1 час")
    print("9 - за 15 минут\n")

    if interval == 1:
        t0 = time - timedelta(days=365)
    elif  interval == 2:
        t0 = time - timedelta(days=90)
    elif  interval == 3:
        t0 = time - timedelta(days=30)
    elif  interval == 4:
        t0 = time - timedelta(days=7)
    elif  interval == 5:
        t0 = time - timedelta(days=3)
    elif  interval == 6:
        t0 = time - timedelta(days=1)
    elif  interval == 7:
        t0 = time - timedelta(hours=3)
    elif  interval == 8:
        t0 = time - timedelta(hours=1)
    elif  interval == 9:
        t0 = time - timedelta(minutes=15)
    else:
        t0 = time - timedelta(days=10000)
        
    codes = "SELECT DISTINCT violation_code from violation_order ORDER BY violation_code"
    cur.execute(codes)
    codes_in_DB = cur.fetchall()
    for code in codes_in_DB:
        count_violations = "SELECT count(*) from violation_order where violation_code  = " + str(code)[1:-2]
        cur.execute(count_violations)
        row = cur.fetchall()
        if str(code)[1:-2] == '0':
            print("В базе данных проездов -", str(row[0])[1:-2])
        else:
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
        if str(code)[1:-2] == '0':
            name = path_to_write + str(host) + "_" + str(time.year) + "." + str(time.month) + "." + \
            str(time.day) + "_" + str(time.hour) + "." + str(time.minute) + "." + \
            str(time.second) + "_" + "passeges.csv"
        else:
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
