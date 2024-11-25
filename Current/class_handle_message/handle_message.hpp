#ifndef HANDLE_MESSAGE_HPP
#define HANDLE_MESSAGE_HPP

#include "memory"
#include <iostream>

class handleMessage
{
public:
    // Static method to access the handleMessage instance
    static handleMessage * getInstance()
    {
        // If the instance doesn't exist, create it
        if (!instance_ptr)
        {
            instance_ptr = new handleMessage();
        }
        return instance_ptr;
    } // END getInstance()

    // Delete the copy and move constructor and assignment operator
    handleMessage(const handleMessage &) = delete;
    handleMessage& operator=(const handleMessage &) = delete;
    handleMessage(const handleMessage &&) = delete;
    ~handleMessage();

    void receiveIncomingMessage(uint8_t * ba);
    void receiveIncomingMessageHeading(uint8_t * ba);
    void receiveIncomingMessageCount(uint8_t * ba);
    void receiveIncomingMessageData(uint8_t * ba);
    void parseHeading();
    void printHex(unsigned char byte);

private:
    // Private constructor to prevent external instantiation
    handleMessage();

    // Private static instance variable
    static handleMessage* instance_ptr;
    std::string _incomingMessagePartOne;
    char        CMD = 0xFF;
    char        STATUS = 0xFF;
    char        SRC_DEV = 0xFF;
    char        SRC_FUN = 0xFF;
    char        DST_DEV = 0xFF;
    char        DST_FUN = 0xFF;
    short       wCOUNT = 0;
    std::string DATA = "";

}; // END class handleMessage

#endif // HANDLE_MESSAGE_HPP


