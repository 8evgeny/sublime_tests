#ifndef HANDLE_MESSAGE_HPP
#define HANDLE_MESSAGE_HPP

#include "memory"
#include <iostream>
#include "thread"
#include <QByteArray>
#include <QString>

//#define getInstance() inst

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


    void receiveIncomingMessage(std::string & ba);
    void parseReceivedMessade();
    void printHex(unsigned char byte);

private:
    // Private constructor to prevent external instantiation
    handleMessage();

    // Private static instance variable
    static handleMessage* instance_ptr;
    std::string _incomingMessage;
    char CMD = 0xFF;
    char STATUS = 0xFF;

}; // END class handleMessage

#endif // HANDLE_MESSAGE_HPP


