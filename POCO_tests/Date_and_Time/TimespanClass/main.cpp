#include "Poco/DateTime.h"
#include "Poco/Timespan.h"

using Poco::DateTime;
using Poco::Timespan;

int main(int argc, char** argv)
{
    Timespan ts1(1, 11, 45, 22, 123433);                    // 1d 11h 45m 22.123433s
    Timespan ts2(33*Timespan::SECONDS);                     // 33s
    Timespan ts3(2*Timespan::DAYS + 33*Timespan::HOURS);    // 3d 33h
    int days = ts1.days();                                  // 1
    int hours = ts1.hours();                                // 11
    int totalHours = ts1.totalHours();                      // 35
    int minutes = ts1.minutes();                            // 45
    int totalMins = ts1.totalMinutes();                     // 2145
    int seconds = ts1.seconds();                            // 22
    int totalSecs = ts1.totalSeconds();                     // 128722

    // what is my age?
    DateTime birthdate(1973, 9, 12, 2, 30);                 // 1973-09-12 02:30:00
    DateTime now;
    Timespan age = now - birthdate;
    int Days = age.days();                                  // in days
    int Hours = age.totalHours();                           // in hours
    int Secs = age.totalSeconds();                          // in seconds
    // when was I 10000 days old?
    Timespan span(10000*Timespan::DAYS);
    DateTime dt = birthdate + span;






    return 0;
}
