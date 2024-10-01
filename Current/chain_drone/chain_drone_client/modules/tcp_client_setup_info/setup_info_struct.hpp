#ifndef FENIX2_SETUP_INFO_STRUCT_HPP
#define FENIX2_SETUP_INFO_STRUCT_HPP

#pragma pack(push, 1)
struct Fenix2SetupInfo
{
	int tracker_type = -1; // 0 - CPU tracShats; 1 - GPU tracShats; 2 - ETLD; 3 - ECO
    int a = 11;
    int b = 12;
    int c = 13;
}; // END Fenix2SetupInfo
#pragma pack(pop)

#endif // FENIX2_SETUP_INFO_HPP
