#include <RS232_parser.hpp>

int RS232_parser::find_cmd()
{
    if(find_cmd_STOP()) return CMD::STOP;
    if(find_cmd_LEFT()) return CMD::LEFT;
    if(find_cmd_RIGHT()) return CMD::RIGHT;
    if(find_cmd_UP()) return CMD::UP;
    if(find_cmd_DOWN()) return CMD::DOWN;
    if(find_cmd_INFRA()) return CMD::INFRA;
    if(find_cmd_TV()) return CMD::TV;
    if(find_cmd_ZOOM_MINUS()) return CMD::ZOOM_MINUS;
    if(find_cmd_ZOOM_PLUS()) return CMD::ZOOM_PLUS;
    if(find_cmd_TO_CENTRE()) return CMD::TO_CENTRE;
    if(find_cmd_TRACKING_START()) return CMD::TRACKING_START;
    if(find_cmd_TRACKING_STOP()) return CMD::TRACKING_STOP;
    return CMD::notCMD;
}//END find_cmd()

bool RS232_parser::find_cmd_STOP()
{
    if ((_cmdBuf[2] == 0x24) &&
        (_cmdBuf[3] == 0x00) && (_cmdBuf[4] == 0x00) && (_cmdBuf[5] == 0x00) && (_cmdBuf[6] == 0x00))
    {
        return true;
    }//END if
    return false;
}//END find_cmd_STOP()

bool RS232_parser::find_cmd_LEFT()
{
    if ((_cmdBuf[2] == 0x24) &&
        (_cmdBuf[3] == 0x9C) && (_cmdBuf[4] == 0xFF))
    {
        return true;
    }//END if
    return false;
}//END find_cmd_LEFT()

bool RS232_parser::find_cmd_RIGHT()
{
    if ((_cmdBuf[2] == 0x24) &&
        (_cmdBuf[3] == 0x64) && (_cmdBuf[4] == 0x00))
    {
        return true;
    }//END if
    return false;
}//END find_cmd_RIGHT()

bool RS232_parser::find_cmd_UP()
{
    if ((_cmdBuf[2] == 0x24) &&
        (_cmdBuf[5] == 0x64) && (_cmdBuf[6] == 0x00))
    {
        return true;
    }//END if
    return false;
}//END find_cmd_UP()

bool RS232_parser::find_cmd_DOWN()
{
    if ((_cmdBuf[2] == 0x24) &&
        (_cmdBuf[5] == 0x9C) && (_cmdBuf[6] == 0xFF))
    {
        return true;
    }//END if
    return false;
}//END find_cmd_DOWN()

bool RS232_parser::find_cmd_INFRA()
{
    if ((_cmdBuf[2] == 0x03) &&
        (_cmdBuf[3] == 0x00) && (_cmdBuf[4] == 0x00) && (_cmdBuf[5] == 0x00) && (_cmdBuf[6] == 0x00))
    {
        return true;
    }//END if
    return false;
}//END find_cmd_INFRA()

bool RS232_parser::find_cmd_TV()
{
    if ((_cmdBuf[2] == 0x01) &&
        (_cmdBuf[3] == 0x00) && (_cmdBuf[4] == 0x00) && (_cmdBuf[5] == 0x00) && (_cmdBuf[6] == 0x00))
    {
        return true;
    }//END if
    return false;
}//END find_cmd_TV()

bool RS232_parser::find_cmd_ZOOM_MINUS()
{
    if ((_cmdBuf[2] == 0x25) &&
        (_cmdBuf[3] == 0x00) && (_cmdBuf[4] == 0x00) && (_cmdBuf[5] == 0x00) && (_cmdBuf[6] == 0x00) && (_cmdBuf[7] == 0x00) && (_cmdBuf[8] == 0xC4))
    {
        return true;
    }//END if
    return false;
}//END find_cmd_ZOOM_MINUS()

bool RS232_parser::find_cmd_ZOOM_PLUS()
{
    if ((_cmdBuf[2] == 0x25) &&
        (_cmdBuf[3] == 0x00) && (_cmdBuf[4] == 0x00) && (_cmdBuf[5] == 0x00) && (_cmdBuf[6] == 0x00) && (_cmdBuf[7] == 0x00) && (_cmdBuf[8] == 0x3C))
    {
        return true;
    }//END if
    return false;
}//END find_cmd_ZOOM_PLUS()

bool RS232_parser::find_cmd_TO_CENTRE()
{
    if ((_cmdBuf[2] == 0x2B) &&
        (_cmdBuf[3] == 0x00) && (_cmdBuf[4] == 0x00) && (_cmdBuf[5] == 0x00) && (_cmdBuf[6] == 0x00))
    {
        return true;
    }//END if
    return false;
}//END find_cmd_TO_CENTRE()

bool RS232_parser::find_cmd_TRACKING_START()
{
    if ((_cmdBuf[2] == 0x0D) &&
        (_cmdBuf[3] == 0x00) && (_cmdBuf[4] == 0x00) && (_cmdBuf[5] == 0x00) && (_cmdBuf[6] == 0x00))
    {
        return true;
    }//END if
    return false;
}//END find_cmd_TRACKING_START()

bool RS232_parser::find_cmd_TRACKING_STOP()
{
    if ((_cmdBuf[2] == 0x0E) &&
        (_cmdBuf[3] == 0x00) && (_cmdBuf[4] == 0x00) && (_cmdBuf[5] == 0x00) && (_cmdBuf[6] == 0x00))
    {
        return true;
    }//END if
    return false;
}//END find_cmd_TRACKING_STOP()
