#include "handle_message.hpp"
#include <iostream>

using namespace std;

// Initialize the static instance variable to nullptr
handleMessage * handleMessage::instance_ptr = nullptr;

handleMessage::handleMessage()
{
    cout << "handleMessage instance created." << endl<<endl;
} // END handleMessage()

handleMessage::~handleMessage()
{
    cout << endl<<"handleMessage instance destroyed." << endl;
    instance_ptr = nullptr;
} // END ~handleMessage()

void handleMessage::printHex(unsigned char byte)
{
    char hex[] = "0123456789ABCDEF";
    printf("%c%c", hex[byte>>4], hex[byte&0xF]);
} // END printHex

void handleMessage::receiveIncomingMessageHeading(uint8_t * ba)
{
    CMD = ba[0];
    STATUS = ba[1];
    SRC_DEV = ba[2];
    SRC_FUN = ba[3];
    DST_DEV = ba[4];
    DST_FUN = ba[5];
    printf("CMD=%02hhX\n",CMD);
    printf("STATUS=%02hhX\n",STATUS);
    printf("SRC_DEV=%02hhX\n",SRC_DEV);
    printf("SRC_FUN=%02hhX\n",SRC_FUN);
    printf("DST_DEV=%02hhX\n",DST_DEV);
    printf("DST_FUN=%02hhX\n",DST_FUN);
    cout<<endl;
} // END receiveIncomingMessagePartOne

void handleMessage::receiveIncomingMessageCount(uint8_t * ba)
{
    char wc0=ba[6];
    char wc1=ba[7];
    printf("wc0=%02hhx\nwc1=%02hhx\n", wc0, wc1);
    wCOUNT = wc0 * 256 + wc1;
} // END receiveIncomingMessageCount

void handleMessage::receiveIncomingMessageData(uint8_t * ba)
{
    cout<<"DATA=";
    for(int i = 0; i < wCOUNT * 4; i += 4)
    {
        for(int k = 0; k < 4; ++k)
        {
            DATA[i + k] = ba[i + k + 8];
            printHex(DATA[i + k]);
        }
        cout <<"\n     ";
    }
} // END receiveIncomingMessageData

void handleMessage::receiveIncomingMessage(uint8_t * ba)
{
    receiveIncomingMessageHeading(ba);
    receiveIncomingMessageCount(ba);
    receiveIncomingMessageData(ba);
} // END receiveIncomingMessage
