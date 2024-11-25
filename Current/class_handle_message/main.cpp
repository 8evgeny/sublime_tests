#include "handle_message.hpp"
#include <iostream>

using namespace std;

uint8_t test_message_1[] {
    0x9A,                   //CMD
    0x34,                   //STATUS
    0x67,                   //dev stc
    0x9a,                   //fun src
    0xCD,                   //dev dst
    0xF0,                   //fun dst
    0x23, 0x56,             //word count
    0x89,0xBC,0xEF,0x12};   //data

string ba_1((const char *)test_message_1);

int main(int argc, char *argv[])
{
    // Access the Singleton instance
    handleMessage * hmPtr = handleMessage::getInstance();

    hmPtr->receiveIncomingMessage(ba_1);
    hmPtr->parseReceivedMessade();

    delete hmPtr;
    return 0;
}

