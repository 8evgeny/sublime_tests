#ifndef TRACKMETA2AP_HPP
#define TRACKMETA2AP_HPP

#include <cstdint>

#pragma pack(push,1)
struct TrackMeta2AP
{
    float vel_longit_mps = 0 ;
    float vel_transv_mps = 0 ;
	uint8_t valid;
};
#pragma pack(pop)

#endif //TRACKMETA2AP_HPP
