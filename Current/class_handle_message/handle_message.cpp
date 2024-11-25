#include "handle_message.hpp"
#include <iostream>
#include <QDebug>

using namespace std;


// Initialize the static instance variable to nullptr
handleMessage * handleMessage::instance_ptr = nullptr;

handleMessage::handleMessage()
{
    cout << "handleMessage instance created." << endl;
} // END handleMessage()

handleMessage::~handleMessage()
{
    cout << "handleMessage instance destroyed." << endl;
    instance_ptr = nullptr;
} // END ~handleMessage()

void handleMessage::printHex(unsigned char byte)
{
    char hex[] = "0123456789ABCDEF";
    printf("%c%c", hex[byte>>4], hex[byte&0xF]);
} // END printHex

void handleMessage::receiveIncomingMessage(string & ba)
{
    _incomingMessage = ba;
    int size = _incomingMessage.size();
    printf("incomingMessage=");
    for(int i=0; i<size; i++)
    {
        printHex(_incomingMessage[i]);
    }
    printf("\n");
} // END receiv eIncomingMessage

void handleMessage::parseReceivedMessade()
{
    CMD = _incomingMessage.at(0);
    STATUS = _incomingMessage.at(1);

    printf("CMD=%02hhX\n",CMD);
    printf("STATUS=%02hhX\n",STATUS);




} // END parseReceivedMessade

