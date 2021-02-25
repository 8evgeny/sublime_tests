#v1 kris_violations_to_send: 24 - число постановлений в формате крис, лежащих в папке /home/codd/Sync/violation (ожидающих отправки),
#v2 kris_violations_sent: 2141 - число постановлений в формате крис, лежащих в папке /home/codd/Sync/.stversions/violation (отправленных),
#v3 kris_passages_to_send: 437 - число информаций о проезде в формате крис, лежащих в ftp-папке /alager/sadko/build/data/kris/passage (ожидающих отправки).
#v4 kris_passages_bck: 56827 - число информаций о проезде в формате крис, лежащих в backup-папке /alager/sadko/build/data/kris/------------ (данная папка чистится нашим скриптом).
# все папки опрашивать рекурсивно - с подкаталогами
# Постановления и проезды (забирать sql-запросом)
#v5 db_violations_total- число сгенерированных постановлений по базе – всего,
#v6 db_passages_total- число проездов по базе – всего.

import os
v1 = "kris_violations_to_send"
v2 = "kris_violations_sent"
v3 = "kris_passages_to_send"
v4 = "kris_passages_bck"
v5 = "db_violations_total"
v6 = "db_passages_total"

# zabbix_path = "/home/eparubets/tmp/zabbix_shooter/"
zabbix_path = "/home/tmp/zabbix_shooter/"

# path_1 = '/home/eparubets/codd/Sync/v1'
path_1 = '/home/codd/Sync/violation'
# path_2 = '/home/eparubets/codd/Sync/v2'
path_2 = '/home/codd/Sync/.stversions/violation'
# path_3 = '/home/eparubets/codd/Sync/v3'
path_3 = '/alager/sadko/build/data/kris/passage'
# path_4 = '/home/eparubets/codd/Sync/v4'
path_4 = '/alager/sadko/build/data/kris/'

from datetime import datetime,timedelta
time = datetime.now()
host = "localhost"

def scanDir(patch,variable):
    variable_path = zabbix_path + variable
    value = 0
    for dirs,folder,files in os.walk(patch):
        for file in files:
            # print(file)
            value  +=1
    file = open(variable_path, "w")
    file.write(str(value))
    file.close()
    print(variable," = ", value)

scanDir(path_1,v1)
scanDir(path_2,v2)
scanDir(path_3,v3)
scanDir(path_4,v4)

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
    # print("\nподключение к БД - OK.")

    count_violations = \
    "SELECT count(*) FROM violation_order "\
    "WHERE violation_code  > 0 "
    cur.execute(count_violations)
    row = cur.fetchall()
    print("нарушений в базе -", str(row[0])[1:-2])
    file = open(zabbix_path + v5, "w")
    file.write(str(row[0])[1:-2])
    file.close()
    count_passeges = \
    "SELECT count(*) FROM violation_order "\
    "WHERE violation_code  = 0 "
    cur.execute(count_passeges)
    row = cur.fetchall()
    print("проездов в базе -", str(row[0])[1:-2])
    file = open(zabbix_path + v6, "w")
    file.write(str(row[0])[1:-2])
    file.close()
except psycopg2.Error as e:
        print("Ошибка запроса:\n", e.args[0])
else:
    connection.close()
