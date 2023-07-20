#include "Poco/Timestamp.h"
#include <ctime>
#include "iostream"
using Poco::Timestamp;
int main(int argc, char** argv)
{
    Timestamp now;                                  // the current date and time
    std::time_t t1 = now.epochTime();               // convert to time_t ...
    Timestamp ts1(Timestamp::fromEpochTime(t1));    // ... and back again
    for (int i = 0; i < 100000; ++i) ;              // wait a bit
    Timestamp::TimeDiff diff = now.elapsed();       // how long did it take?
    Timestamp start(now);                           // save start time
    now.update();                                   // update with current time
    diff = now - start;                             // again, how long?
    std::cout<< "diff: " << diff <<std::endl;
return 0;
}
