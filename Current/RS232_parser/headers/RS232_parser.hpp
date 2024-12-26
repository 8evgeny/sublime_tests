#pragma once

#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <iostream>
#include <memory>
#include <thread>

class RS232_parser
{

public:
    RS232_parser();
    ~RS232_parser();
    QSerialPort serial;
    const QString &getPortName() const;
    int getSpeed() const;
    void parsing();

    uint8_t getCmdLen() const;

private:
    QString _portName{"ttyUSB0"};
    const uint8_t cmdLen = 32;
    int _speed = 115200;

};



