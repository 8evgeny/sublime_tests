#pragma once

#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>

class eth_ttl
{

public:
    eth_ttl();
    ~eth_ttl();
    QSerialPort serial;
    const QString &getPortName() const;
    int getSpeed() const;
    void work_eth_ttl();

    uint8_t get_cmdLen() const;

private:
    QString _portName{"ttyUSB0"};
    const uint8_t _cmdLen = 32;
    int _speed = 9600;

};
