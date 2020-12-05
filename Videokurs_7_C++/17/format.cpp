// Format

#include <boost/format.hpp>
#include <iostream>

int main()
{
    std::cout << boost::format{"%1% [%2%] %3%"} % "2018-01-12" % "info" % 
            (boost::format{"%1% was open"} % "test.txt") << std::endl;
}
