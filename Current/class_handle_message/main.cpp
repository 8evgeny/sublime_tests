#include "handle_message.hpp"
#include <iostream>

using namespace std;

uint8_t test_message[]
{
    0x00,                   //CMD
    0x01,                   //STATUS
    0x02,                   //dev stc
    0x00,                   //fun src
    0x03,                   //dev dst
    0x00,                   //fun dst
    0x00, 0x06,             //word count
    0x89,0xBC,0xEF,0x12,    //DATA
    0x90,0xBD,0x00,0x13,
    0x91,0xBE,0x00,0x14,
    0x90,0xBD,0x00,0x13,
    0x91,0xBE,0x00,0x14,
    0xFF,0xCC,0xDD,0xAA
}; // END test_message[]

int main(int argc, char *argv[])
{
    // Access the Singleton instance
    handleMessage * hmPtr = handleMessage::getInstance();

    hmPtr->receiveIncomingMessage(test_message);


    delete hmPtr;
    return 0;
}

