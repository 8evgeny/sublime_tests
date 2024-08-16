#ifndef CMD400_STRUCT_HPP
#define CMD400_STRUCT_HPP

#pragma pack(push,1)
struct Cmd400_init
{
    int x = -1;
    int y = -1;
    int w = -1;
    int h = -1;
}; // END Cmd400_init

struct Cmd400_deinit
{
  bool need_deinit = 0;
}; // END Cmd400_deinit
#pragma pack(pop)

#endif //CMD400_STRUCT_HPP
