#include "CoastalRadarMessage.h"
#include "SystemClock.h"

CoastalRadarMessage::CoastalRadarMessage() { }
CoastalRadarMessage::~CoastalRadarMessage() { }

bool CoastalRadarMessage::is_data_valid() const
{
    if (SystemClock::get_time_milliseconds() - data.timestamp < 100)
        return false;
    return true;
}
