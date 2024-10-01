#ifndef TRACKMETA2AP_POS_HPP
#define TRACKMETA2AP_POS_HPP

#include <cstdint>

#pragma pack(push,1)
struct TrackMeta2AP_pos
{
    float delta_x_rad = 0 ;
    float delta_y_rad = 0 ;
	uint8_t valid;
};
#pragma pack(pop)

#endif //TRACKMETA2AP_HPP
