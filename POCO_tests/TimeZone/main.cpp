#include "Poco/Timezone.h"
#include "Poco/Timestamp.h"
#include "iostream"

using Poco::Timezone;
using Poco::Timestamp;

int main(int argc, char** argv)
{
    int utcOffset = Timezone::utcOffset();
    int dst = Timezone::dst();
    bool isDst = Timezone::isDst(Timestamp());
    int tzd = Timezone::tzd();
    std::string name = Timezone::name();
    std::string stdName = Timezone::standardName();
    std::string dstName = Timezone::dstName();
    printf("utcOffset:%d\r\n",utcOffset);
    printf("name:%s\r\n",name.c_str());
    printf("stdName:%s\r\n",stdName.c_str());
    printf("dstName:%s\r\n",dstName.c_str());
    return 0;
}
