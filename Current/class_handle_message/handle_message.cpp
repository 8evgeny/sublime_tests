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
    string ba_string((const char *)ba);
    ba_string.substr(6);
    _incomingMessagePartOne = ba_string;
    cout<<"incomingMessage=";
    for(int i = 0; i < 6; i++)
    {
        printHex(_incomingMessagePartOne[i]);
    }
    cout<<endl;
} // END receiveIncomingMessagePartOne

void handleMessage::receiveIncomingMessageCount(uint8_t * ba)
{
    char wc0=ba[6];
    char wc1=ba[7];
    printf("wc0=%02hhx\nwc1=%02hhx\n", wc0, wc1);
    wCOUNT = wc0 * 256 + wc1;
//    cout<<"wCOUNT="<<wCOUNT<<endl;
} // END receiveIncomingMessageCount

void handleMessage::receiveIncomingMessageData(uint8_t * ba)
{
    string ba_data((const char *)(ba + 8));
    DATA = ba_data;
    cout<<"DATA=";
    for(int i = 0; i < wCOUNT * 4; i++)
    {
        printHex(DATA[i]);
    }
    cout<<endl;
} // END receiveIncomingMessageData

void handleMessage::parseHeading()
{
    CMD = _incomingMessagePartOne.at(0);
    STATUS = _incomingMessagePartOne.at(1);
    SRC_DEV = _incomingMessagePartOne.at(2);
    SRC_FUN = _incomingMessagePartOne.at(3);
    DST_DEV = _incomingMessagePartOne.at(4);
    DST_FUN = _incomingMessagePartOne.at(5);

    printf("CMD=%02hhX\n",CMD);
    printf("STATUS=%02hhX\n",STATUS);
    printf("SRC_DEV=%02hhX\n",SRC_DEV);
    printf("SRC_FUN=%02hhX\n",SRC_FUN);
    printf("DST_DEV=%02hhX\n",DST_DEV);
    printf("DST_FUN=%02hhX\n",DST_FUN);

} // END parseReceivedMessagePartOne

void handleMessage::receiveIncomingMessage(uint8_t * ba)
{
    receiveIncomingMessageHeading(ba);
    parseHeading();
    receiveIncomingMessageCount(ba);
    receiveIncomingMessageData(ba);
} // END receiveIncomingMessage
