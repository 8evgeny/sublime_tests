# Dates don't exist in isolation. It is common that you will need to find the amount of time between dates or
# determine what the date will be tomorrow. This can be accomplished using timedelta objects
import datetime
today = datetime.date.today()
print('Today:', today)
yesterday = today - datetime.timedelta(days=1)
print('Yesterday:', yesterday)
tomorrow = today + datetime.timedelta(days=1)
print('Tomorrow:', tomorrow)
print('Time between tomorrow and yesterday:', tomorrow - yesterday)








































