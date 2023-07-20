#include "Poco/DateTime.h"
#include "iostream"

using Poco::DateTime;
int main(int argc, char** argv)
{
    DateTime now;                                   // the current date and time in UTC
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
    double jd = now.julianDay();

    printf("year:%d month:%d day:%d day of week:%d day of year:%d\r\n",year,month,day,dow,doy);
    printf("hour:%d hourAMPM:%d minute:%d second:%d millisecond:%d microsecond:%d\r\n",hour,hour12,min,sec,ms,us);
    printf("julianDay:%f\r\n",jd);

    Poco::Timestamp ts = now.timestamp();
    DateTime xmas(2023, 12, 25);                    // 2023-12-25 00:00:00
    Poco::Timespan timeToXmas = xmas - now;
    printf("timeToXmas: %d\r\n",timeToXmas.days());
    DateTime dt(1973, 9, 12, 2, 30, 45);            // 1973-09-12 02:30:45
    dt.assign(2006, 10, 13, 13, 45, 12, 345);       // 2006-10-13 12:45:12.345
    bool isAM = dt.isAM();                          // false
    bool isPM = dt.isPM();                          // true
    bool isLeap = DateTime::isLeapYear(2006);       // false
    int days = DateTime::daysOfMonth(2006, 2);      // 28
    bool isValid = DateTime::isValid(2006, 02, 29); // false
    dt.assign(2006, DateTime::OCTOBER, 22);         // 2006-10-22 00:00:00
    if (dt.dayOfWeek() == DateTime::SUNDAY)
    {
    // ...
    }
    return 0;
}
