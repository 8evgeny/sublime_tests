# By default all datetime objects are naive. To make them timezone-aware, you must attach a tzinfo object, which
# provides the UTC offset and timezone abbreviation as a function of date and time.

# Fixed Offset Time Zones

# For time zones that are a fixed offset from UTC, in Python 3.2+, the datetime module provides the timezone class, a
# concrete implementation of tzinfo, which takes a timedelta and an (optional) name parameter:

from datetime import datetime, timedelta, timezone
JST = timezone(timedelta(hours=+9))
dt = datetime(2015, 1, 1, 12, 0, 0, tzinfo=JST)
print(dt)   # 2015-01-01 12:00:00+09:00
print(dt.tzname())  # UTC+09:00
dt = datetime(2015, 1, 1, 12, 0, 0, tzinfo=timezone(timedelta(hours=9), 'JST'))
print(dt.tzname())   # 'JST'

# Zones with daylight savings time

from datetime import datetime
from dateutil import tz
local = tz.gettz() # Local time
PT = tz.gettz('US/Pacific') # Pacific time
dt_l = datetime(2015, 1, 1, 12, tzinfo=local) # I am in EST
dt_pst = datetime(2015, 1, 1, 12, tzinfo=PT)
dt_pdt = datetime(2015, 7, 1, 12, tzinfo=PT) # DST is handled automatically
print(dt_l)    # 2015-01-01 12:00:00-05:00
print(dt_pst)  # 2015-01-01 12:00:00-08:00
print(dt_pdt)  # 2015-07-01 12:00:00-07:00

































