#include "handle_message.hpp"
#include <iostream>

using namespace std;

uint8_t test_message[] {
    0x9A,                   //CMD
    0x34,                   //STATUS
    0x67,                   //dev stc
    0x9a,                   //fun src
    0xCD,                   //dev dst
    0xF0,                   //fun dst
    0x00, 0x02,             //word count
    0x89,0xBC,0xEF,0x12,
    0xFF,0xCC,0xDD,0xAA,};   //data

int main(int argc, char *argv[])
{
    // Access the Singleton instance
    handleMessage * hmPtr = handleMessage::getInstance();

    hmPtr->receiveIncomingMessage(test_message);


    delete hmPtr;
    return 0;
}

