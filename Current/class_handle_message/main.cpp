#include "handle_message.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    uint8_t test_message_blank[]
    {
        0x00,                   //CMD
        0x00,                   //STATUS
        0x02,                   //dev stc
        0x33,                   //fun src
        0x01,                   //dev dst
        0xfe,                   //fun dst
        0x00, 0x00,             //word count
    }; // END test_message_blank

    uint8_t test_message[]
    {
        0x01,                   //CMD
        0x80,                   //STATUS
        0x02,                   //dev stc
        0x11,                   //fun src
        0x01,                   //dev dst
        0x05,                   //fun dst
        0x00, 0x06,             //word count
        0x89,0xBC,0xEF,0x12,    //DATA
        0x90,0xBD,0x00,0x13,
        0x91,0xBE,0x00,0x14,
        0x90,0xBD,0x00,0x13,
        0x91,0xBE,0x00,0x14,
        0xFF,0xCC,0xDD,0xAA
    }; // END test_message

    uint8_t error_message[]
    {
        0x10,                   //CMD
        0x01,                   //STATUS
        0x00,                   //dev stc
        0x00,                   //fun src
        0x33,                   //dev dst
        0x04,                   //fun dst
        0x00, 0x01,             //word count
        0xFF,0xCC,0xDD,0xAA
    }; // END error_message

    // Access the Singleton instance
    handleMessage * inst = handleMessage::getInstance();
    inst->receiveMessage(test_message_blank);
    inst->receiveMessage(test_message);
    inst->receiveMessage(error_message);

    delete inst;
    return 0;
} // END main

