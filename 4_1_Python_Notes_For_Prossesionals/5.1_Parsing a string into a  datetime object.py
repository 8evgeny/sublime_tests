import datetime
dt = datetime.datetime.strptime("2016-04-15T08:27:18-0500", "%Y-%m-%dT%H:%M:%S%z")
print(dt)

dt = datetime.datetime.now()
print(dt)

dt = datetime.date.today()
print(dt)

dt = datetime.datetime.utcfromtimestamp(1601233456)
print(dt)

dt = datetime.datetime.now().timestamp()
print(dt)


datetime.datetime()
# datetime.datetime(2016, 4, 15, 8, 27, 18, tzinfo=tzoffset(None, -18000)) ???
































