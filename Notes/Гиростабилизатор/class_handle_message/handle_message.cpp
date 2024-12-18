#include "handle_message.hpp"
#include <iostream>
#include <functional>

using namespace std;

void f01(); //Функция, вызываемая при получении 0x01
void f02(); //Функция, вызываемая при получении 0x02
void f03(); //Функция, вызываемая при получении 0x03
void f04(); //Функция, вызываемая при получении 0x04
void f05(); //Функция, вызываемая при получении 0x05
void f06(); //Функция, вызываемая при получении 0x06
void f07(); //Функция, вызываемая при получении 0x07
void f08(); //Функция, вызываемая при получении 0x08
void ffe(); //Функция, вызываемая при получении 0xFE


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

void handleMessage::receiveHeading(uint8_t * ba)
{
    CMD = ba[0];
    printf("CMD=%02hhX\n",CMD);
    parseCmdType();

    STATUS = ba[1];
    printf("STATUS=%02hhX\n",STATUS);
    parseStatusType();

    SRC_DEV = ba[2];
    printf("SRC_DEV=%02hhX\n",SRC_DEV);
    parseAdress(SRC_DEV);

    SRC_FUN = ba[3];
    printf("SRC_FUN=%02hhX\n",SRC_FUN);
    parseFun(SRC_FUN);

    DST_DEV = ba[4];
    printf("DST_DEV=%02hhX\n",DST_DEV);
    parseAdress(DST_DEV);

    DST_FUN = ba[5];
    printf("DST_FUN=%02hhX\n",DST_FUN);
    parseFun(DST_FUN);

} // END receiveHeading

void handleMessage::receiveCount(uint8_t * ba)
{
    if(!errorCurrentMessage)
    {
        char wc0=ba[6];
        char wc1=ba[7];
        printf("wc0=%02hhx\nwc1=%02hhx\n", wc0, wc1);
        wCOUNT = wc0 * 256 + wc1;
    } // END if(!errorCurrentMessage)
} // END receiveCount

void handleMessage::receiveData(uint8_t * ba)
{
    if(!errorCurrentMessage)
    {
        if(wCOUNT > 0)
        {
            cout<<"DATA=";
            for(int i = 0; i < wCOUNT * 4; i += 4)
            {
                for(int k = 0; k < 4; ++k)
                {
                    DATA[i + k] = ba[i + k + 8];
                    printHex(DATA[i + k]);
                } // END for(int k = 0; k < 4; ++k)
                cout <<"\n     ";
            } // END for(int i = 0; i < wCOUNT * 4; i += 4)
        } // END if(wCOUNT > 0)
    } // END if(!errorCurrentMessage)
} // END receiveData

void handleMessage::receiveMessage(uint8_t * ba)
{
    cout<<"receive new message "<< ++numberAllMessage <<endl;
    receiveHeading(ba);
    receiveCount(ba);
    receiveData(ba);

    //Тут проверка что команда приходит данному устройству
    if(!errorCurrentMessage)
    {
        if(dev_adress == DST_DEV)
        {
            //Тут запуск нужной функции из таблицы функций
            runFoo(DST_FUN);
        }
        else //пересылаем сообщение далее
        {
            forwardMessage();
        }
    } // END if(!errorCurrentMessage)

    if(errorCurrentMessage)
    {
        ++incorrectMessageNumber;
        errorCurrentMessage = false;
        sendErrorMessage();
        cout<<"incorrectMessageNumber="<<incorrectMessageNumber<<endl;
    } // END if(errorCurrentMessage)


} // END receiveMessage

void handleMessage::parseCmdType()
{
    if(!((CMD == requestWrite) || (CMD == answerWrite) || (CMD == requestRead) || (CMD == answerRead)))
    {
        errorCurrentMessage = true;
        cout << "===== incorrect CMD ======"<<endl;
    }
} //END parseCmdType

void handleMessage::parseStatusType()
{
    if(!((STATUS == requestNoAnswer) || (STATUS == requestWithAnswer)))
    {
        errorCurrentMessage = true;
        cout << "===== incorrect STATUS ======"<<endl;
    }
} //END parseStatusType

void handleMessage::parseAdress(uint8_t addr)
{
    if((addr == 0x00) || (addr == 0xFF))
    {
        errorCurrentMessage = true;
        cout << "===== incorrect ADRESS ======"<<endl;
    }
} //END parseAdress

void handleMessage::parseFun(uint8_t foo)
{
    if((foo == 0x00) || (foo == 0xFF))
    {
        errorCurrentMessage = true;
        cout << "===== incorrect FUNCTION ======"<<endl;
    }
} //END parseAdress

void handleMessage::runFoo(uint8_t foo)
{
    function<void(void)> run;
    switch (foo)
    {
        case 0x01: run = f01;   break;
        case 0x02: run = f02;   break;
        case 0x03: run = f03;   break;
        case 0x04: run = f04;   break;
        case 0x05: run = f05;   break;
        case 0x06: run = f06;   break;
        case 0x07: run = f07;   break;
        case 0x08: run = f08;   break;
        case 0xFE: run = ffe;   break;
        default:                break;
    }
    run(); //Вызов нужной функции
} // END runFoo

void f01() {cout<<"\r===== invoke f01 =====\n"<<endl;}
void f02() {cout<<"\r===== invoke f02 =====\n"<<endl;}
void f03() {cout<<"\r===== invoke f03 =====\n"<<endl;}
void f04() {cout<<"\r===== invoke f04 =====\n"<<endl;}
void f05() {cout<<"\r===== invoke f05 =====\n"<<endl;}
void f06() {cout<<"\r===== invoke f06 =====\n"<<endl;}
void f07() {cout<<"\r===== invoke f07 =====\n"<<endl;}
void f08() {cout<<"\r===== invoke f08 =====\n"<<endl;}
void ffe() {cout<<"\r===== invoke ffe =====\n"<<endl;}

void handleMessage::sendErrorMessage()
{


} // END sendErrorMessage

void handleMessage::forwardMessage()
{


} // END forwardMessage

