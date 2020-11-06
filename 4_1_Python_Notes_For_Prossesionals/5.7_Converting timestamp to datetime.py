# The datetime module can convert a POSIX timestamp to a ITC datetime object. The Epoch is January 1st, 1970 midnight.

import time
from datetime import datetime
seconds_since_epoch=time.time()
print(seconds_since_epoch)   


utc_date=datetime.utcfromtimestamp(seconds_since_epoch) 
print(utc_date)

# list_methods = dir(time)
# for x in list_methods:
# 	print(x)

list_methods = dir(datetime)
for x in list_methods:
	print(x)






































