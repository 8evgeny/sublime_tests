#ifndef HANDLE_MESSAGE_HPP
#define HANDLE_MESSAGE_HPP

#include "memory"
#include <iostream>

#define requestWrite        0x00
#define answerWrite         0x80
#define requestRead         0x01
#define answerRead          0x81

#define requestNoAnswer     0x00
#define requestWithAnswer   0x80

#define DEVICE_ADRESS       0x33



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

    void receiveMessage(uint8_t * ba);
    void receiveHeading(uint8_t * ba);
    void receiveCount(uint8_t * ba);
    void receiveData(uint8_t * ba);
    void parseCmdType();
    void parseStatusType();
    void parseAdress(uint8_t addr);
    void parseFun(uint8_t addr);
    void sendErrorMessage();
    void forwardMessage();
    void runFoo(uint8_t foo);
    void printHex(unsigned char byte);

private:
    // Private constructor to prevent external instantiation
    handleMessage();

    // Private static instance variable
    static handleMessage* instance_ptr;
    static constexpr uint8_t dev_adress = 0x01;  //Собственный алрес устройства
    uint8_t         CMD = 0xFF;
    uint8_t         STATUS = 0xFF;
    uint8_t         SRC_DEV = 0xFF;
    uint8_t         SRC_FUN = 0xFF;
    uint8_t         DST_DEV = 0xFF;
    uint8_t         DST_FUN = 0xFF;
    short           wCOUNT = 0;
    uint8_t         DATA [4 * (256 * 256 + 256)];
    uint            numberAllMessage = 0;
    short           incorrectMessageNumber = 0;
    bool            errorCurrentMessage = false;

    uint8_t         cmdType = 0xFF;     //Таблица 2
    uint8_t         stateType = 0xFF;   //Таблица 3

}; // END class handleMessage

#endif // HANDLE_MESSAGE_HPP


