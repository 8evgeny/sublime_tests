#include "Poco/DateTime.h"
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"

using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;

int main(int argc, char** argv)
{
    Poco::DateTime dt(2006, 10, 22, 15, 22, 34);
    std::string s(DateTimeFormatter::format(dt, "%e %b %Y %H:%M"));
     // "22 Oct 2006 15:22"
    Poco::Timestamp now;
    s = DateTimeFormatter::format(now, DateTimeFormat::SORTABLE_FORMAT);
     // "2006-10-30 09:27:44"
    Poco::Timespan span(5, 11, 33, 0, 0);
    s = DateTimeFormatter::format(span, "%d days, %H hours, %M minutes");
     // "5 days, 11 hours, 33 minutes"
    return 0;
}
