#include "Poco/LocalDateTime.h"
using Poco::LocalDateTime;
int main(int argc, char** argv)
{
    LocalDateTime now; // the current date and local time
    int year = now.year();
    int month = now.month();
    int day = now.day();
    int dow = now.dayOfWeek();
    int doy = now.dayOfYear();
    int hour = now.hour();
    int hour12 = now.hourAMPM();
    int min = now.minute();
    int sec = now.second();
    int ms = now.millisecond();
    int us = now.microsecond();
    int tzd = now.tzd();
    double jd = now.julianDay();
    Poco::Timestamp ts = now.timestamp();
    LocalDateTime dt1(1973, 9, 12, 2, 30, 45); // 1973-09-12 02:30:45
    dt1.assign(2006, 10, 13, 13, 45, 12, 345); // 2006-10-13 12:45:12.345
    LocalDateTime dt2(3600, 1973, 9, 12, 2, 30, 45, 0, 0); // UTC +1 hour
    dt2.assign(3600, 2006, 10, 13, 13, 45, 12, 345, 0);
    Poco::Timestamp nowTS;
    LocalDateTime dt3(3600, nowTS); // construct from Timestamp
    return 0;
}
