#pragma once

#include <QSerialPort>
#include <QSerialPortInfo>
#include <iostream>
#include <memory>
#include <thread>

class RS232_parser
{
enum CMD
{
    notCMD = 0,
    STOP = 1,           //EB 90 24 00 00 00 00 00 00 00 00 00 00 00 00 9F 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    LEFT = 2,           //EB 90 24 9C FF 00 00 00 00 00 00 00 00 00 00 3A 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    RIGHT = 3,          //EB 90 24 64 00 00 00 00 00 00 00 00 00 00 00 03 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    UP = 4,             //EB 90 24 00 00 64 00 00 00 00 00 00 00 00 00 03 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    DOWN = 5,           //EB 90 24 00 00 9C FF 00 00 00 00 00 00 00 00 3A 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    INFRA = 6,          //EB 90 03 00 00 00 00 00 00 00 00 00 00 00 00 7E 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    TV = 7,             //EB 90 01 00 00 00 00 00 00 00 00 00 00 00 00 7C 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    ZOOM_MINUS = 8,     //EB 90 25 00 00 00 00 00 C4 00 00 00 00 00 00 64 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    ZOOM_PLUS = 9,      //EB 90 25 00 00 00 00 00 3C 00 00 00 00 00 00 DC 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    TO_CENTRE = 10,     //EB 90 2B 00 00 00 00 00 00 00 00 00 00 00 00 A6 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    TRACKING_START = 11,//EB 90 0D 00 00 00 00 00 00 00 00 00 00 00 00 88 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    TRACKING_STOP = 12  //EB 90 0E 00 00 00 00 00 00 00 00 00 00 00 00 89 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
};
public:
    RS232_parser();
    ~RS232_parser();
    QSerialPort serial;
    const QString &getPortName() const;
    const int getSpeed() const;
    void parsing();
    int find_cmd();
    bool find_cmd_STOP();
    bool find_cmd_LEFT();
    bool find_cmd_RIGHT();
    bool find_cmd_UP();
    bool find_cmd_DOWN();
    bool find_cmd_INFRA();
    bool find_cmd_TV();
    bool find_cmd_ZOOM_MINUS();
    bool find_cmd_ZOOM_PLUS();
    bool find_cmd_TO_CENTRE();
    bool find_cmd_TRACKING_START();
    bool find_cmd_TRACKING_STOP();

    void printDataRS232();
    void printDataRS232_format();
    uint8_t getCmdLen() const;

    uint8_t CMD() const;

    void setCMD(uint8_t newCMD);

private:
    QString _product{"1a86"}; //Синий переходник (команда lsusb показывает данный ID - первые 4 символа)
//    QString _product{"067b"};
    QString _portName{""};
    static constexpr uint8_t _cmdLen = 32;
    uint8_t _cmdBuf[_cmdLen];
    const int _speed = 115200;
    uint8_t _CMD = 0;
};



