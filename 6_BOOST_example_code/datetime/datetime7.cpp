  /* Generate a set of dates using a collection of date generators
   * Output looks like:
   * Enter Year: 2002
   * 2002-Jan-01 [Tue]
   * 2002-Jan-21 [Mon]
   * 2002-Feb-12 [Tue]
   * 2002-Jul-04 [Thu]
   * 2002-Sep-02 [Mon]
   * 2002-Nov-28 [Thu]
   * 2002-Dec-25 [Wed]
   * Number Holidays: 7
   */

#include "boost/date_time/gregorian/gregorian.hpp"
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>
#include <set>

void
print_date(boost::gregorian::date d)
  {
    using namespace boost::gregorian;
#if defined(BOOST_DATE_TIME_NO_LOCALE)
    std::cout << to_simple_string(d) << " [" << d.day_of_week() << "]\n";
#else
    std::cout << d << " [" << d.day_of_week() << "]\n";
#endif
}


int
main() {

    std::cout << "Enter Year: ";
    int year;
    std::cin >> year;

    using namespace boost::gregorian;

    //define a collection of holidays fixed by month and day
    std::vector<year_based_generator*> holidays;
    holidays.push_back(new partial_date(1,Jan)); //Western New Year
    holidays.push_back(new partial_date(4,Jul)); //US Independence Day
    holidays.push_back(new partial_date(25, Dec));//Christmas day


    //define a shorthand for the nth_day_of_the_week_in_month function object
    typedef nth_day_of_the_week_in_month nth_dow;

    //US labor day
    holidays.push_back(new nth_dow(nth_dow::first,  Monday,   Sep));
    //MLK Day
    holidays.push_back(new nth_dow(nth_dow::third,  Monday,   Jan));
    //Pres day
    holidays.push_back(new nth_dow(nth_dow::second, Tuesday,  Feb));
    //Thanksgiving
    holidays.push_back(new nth_dow(nth_dow::fourth, Thursday, Nov));

    typedef std::set<date> date_set;
    date_set all_holidays;

    for(std::vector<year_based_generator*>::iterator it = holidays.begin();
         it != holidays.end(); ++it)
    {
        all_holidays.insert((*it)->get_date(year));
    }

    //print the holidays to the screen
    std::for_each(all_holidays.begin(), all_holidays.end(), print_date);
    std::cout << "Number Holidays: " << all_holidays.size() << std::endl;

    return 0;
}
