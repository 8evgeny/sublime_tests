# kris_violations_to_send: 24 - число постановлений в формате крис, лежащих в папке /home/codd/Sync/violation (ожидающих отправки),
# kris_violations_sent: 2141 - число постановлений в формате крис, лежащих в папке /home/codd/Sync/.stversions/violation (отправленных),
# kris_passages_to_send: 437 - число информаций о проезде в формате крис, лежащих в ftp-папке /alager/sadko/build/data/kris/passage (ожидающих отправки).
# kris_passages_bck: 56827 - число информаций о проезде в формате крис, лежащих в backup-папке /alager/sadko/build/data/kris/------------ (данная папка чистится нашим скриптом).
#
# все папки опрашивать рекурсивно - с подкаталогами
#
# Постановления и проезды (забирать sql-запросом)
# db_violations_total- число сгенерированных постановлений по базе – всего,
# db_passages_total- число проездов по базе – всего.

kris_violations_to_send_path =  "/tmp/zabbix_shooter/kris_violations_to_send"
kris_violations_sent_path = "/tmp/zabbix_shooter/kris_violations_sent"
kris_passages_to_send_path = "/tmp/zabbix_shooter/kris_passages_to_send"
kris_passages_bck_path = "/tmp/zabbix_shooter/kris_passages_bck"

path_to_write = "lists_violations/"
from datetime import datetime,timedelta
time = datetime.now()
print ("\n\nВведите адрес хоста")
host = input()
# host = "localhost"
# host = "10.8.1.93"


