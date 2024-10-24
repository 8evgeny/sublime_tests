  /* This example demonstrates the use of the time zone database and
   * local time to calculate the number of seconds since the UTC
   * time_t epoch 1970-01-01 00:00:00.  Note that the selected timezone
   * could be any timezone supported in the time zone database file which
   * can be modified and updated as needed by the user.
   *
   * To solve this problem the following steps are required:
   * 1) Get a timezone from the tz database for the local time
   * 2) Construct a local time using the timezone
   * 3) Construct a posix_time::ptime for the time_t epoch time
   * 4) Convert the local_time to utc and subtract the epoch time
   *
   */

#include "boost/date_time/local_time/local_time.hpp"
#include <iostream>

int main()
{
    using namespace boost::gregorian;
    using namespace boost::local_time;
    using namespace boost::posix_time;

    tz_database tz_db;
    try {
        tz_db.load_from_file("../data/date_time_zonespec.csv");
    }catch(data_not_accessible dna) {
        std::cerr << "Error with time zone data file: " << dna.what() << std::endl;
        exit(EXIT_FAILURE);
    }catch(bad_field_count bfc) {
        std::cerr << "Error with time zone data file: " << bfc.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    time_zone_ptr nyc_tz = tz_db.time_zone_from_region("America/New_York");
    date in_date(2004,10,04);
    time_duration td(12,14,32);
    // construct with local time value
    // create not-a-date-time if invalid (eg: in dst transition)
    local_date_time nyc_time(in_date,
                             td,
                             nyc_tz,
                             local_date_time::NOT_DATE_TIME_ON_ERROR);

    std::cout << nyc_time << std::endl;

    ptime time_t_epoch(date(1970,1,1));
    std::cout << time_t_epoch << std::endl;

    // first convert nyc_time to utc via the utc_time()
    // call and subtract the ptime.
    time_duration diff = nyc_time.utc_time() - time_t_epoch;

    //Expected 1096906472
    std::cout << "Seconds diff: " << diff.total_seconds() << std::endl;

}
