#include <RS232_parser.hpp>

void RS232_parser::find_cmd()
{
    if(find_cmd_STOP())_CMD = CMD::STOP;
    if(find_cmd_LEFT())_CMD = CMD::LEFT;


}//END find_cmd()

bool RS232_parser::find_cmd_STOP()
{
    if (
            (_cmdBuf[0] == 0xEB) &&
            (_cmdBuf[1] == 0x90) &&
            (_cmdBuf[2] == 0x24) &&
            (_cmdBuf[3] == 0x00) &&
            (_cmdBuf[4] == 0x00) &&
            (_cmdBuf[5] == 0x00) &&
            (_cmdBuf[6] == 0x00) &&
            (_cmdBuf[7] == 0x00) &&
            (_cmdBuf[8] == 0x00) &&
            (_cmdBuf[9] == 0x00) &&
            (_cmdBuf[10] == 0x00) &&
            (_cmdBuf[11] == 0x00) &&
            (_cmdBuf[12] == 0x00) &&
            (_cmdBuf[13] == 0x00) &&
            (_cmdBuf[14] == 0x00) &&
            (_cmdBuf[15] == 0x9F) &&
            (_cmdBuf[16] == 0x00) &&
            (_cmdBuf[17] == 0x00) &&
            (_cmdBuf[18] == 0x00) &&
            (_cmdBuf[19] == 0x00) &&
            (_cmdBuf[20] == 0x00) &&
            (_cmdBuf[21] == 0x00) &&
            (_cmdBuf[22] == 0x00) &&
            (_cmdBuf[23] == 0x00) &&
            (_cmdBuf[24] == 0x00) &&
            (_cmdBuf[25] == 0x00) &&
            (_cmdBuf[26] == 0x00) &&
            (_cmdBuf[27] == 0x00) &&
            (_cmdBuf[28] == 0x00) &&
            (_cmdBuf[29] == 0x00) &&
            (_cmdBuf[30] == 0x00) &&
            (_cmdBuf[31] == 0x00)
        )
    {
        return true;
    }
    return false;
}//END find_cmd_STOP()

bool RS232_parser::find_cmd_LEFT()
{
    if (
            (_cmdBuf[0] == 0xEB) &&
            (_cmdBuf[1] == 0x90) &&
            (_cmdBuf[2] == 0x24) &&
            (_cmdBuf[3] == 0x9C) &&
            (_cmdBuf[4] == 0xFF) &&
            (_cmdBuf[5] == 0x00) &&
            (_cmdBuf[6] == 0x00) &&
            (_cmdBuf[7] == 0x00) &&
            (_cmdBuf[8] == 0x00) &&
            (_cmdBuf[9] == 0x00) &&
            (_cmdBuf[10] == 0x00) &&
            (_cmdBuf[11] == 0x00) &&
            (_cmdBuf[12] == 0x00) &&
            (_cmdBuf[13] == 0x00) &&
            (_cmdBuf[14] == 0x00) &&
            (_cmdBuf[15] == 0x3A) &&
            (_cmdBuf[16] == 0x00) &&
            (_cmdBuf[17] == 0x00) &&
            (_cmdBuf[18] == 0x00) &&
            (_cmdBuf[19] == 0x00) &&
            (_cmdBuf[20] == 0x00) &&
            (_cmdBuf[21] == 0x00) &&
            (_cmdBuf[22] == 0x00) &&
            (_cmdBuf[23] == 0x00) &&
            (_cmdBuf[24] == 0x00) &&
            (_cmdBuf[25] == 0x00) &&
            (_cmdBuf[26] == 0x00) &&
            (_cmdBuf[27] == 0x00) &&
            (_cmdBuf[28] == 0x00) &&
            (_cmdBuf[29] == 0x00) &&
            (_cmdBuf[30] == 0x00) &&
            (_cmdBuf[31] == 0x00)
        )
    {
        return true;
    }
    return false;
}//END find_cmd_LEFT()
