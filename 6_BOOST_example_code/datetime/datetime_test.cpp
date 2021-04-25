
#include <iostream>
#include "boost/date_time/gregorian/gregorian.hpp"

int main()
{

    using namespace boost::gregorian;

    date today = day_clock::local_day();
    partial_date new_years_day(1,Jan);
    //Subtract two dates to get a duration
    days days_since_year_start = today - new_years_day.get_date(today.year());
    std::cout << "Days since Jan 1: " << days_since_year_start.days()
              << std::endl;

    days days_until_year_start = new_years_day.get_date(today.year()+1) - today;
    std::cout << "Days until next Jan 1: " << days_until_year_start.days()
              << std::endl;
    return 0;
};
