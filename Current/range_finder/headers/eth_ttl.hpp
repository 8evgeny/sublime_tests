#pragma once

#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "boost/asio.hpp"

class eth_ttl
{

public:
    eth_ttl();
    ~eth_ttl();
    QSerialPort serial;
    const QString &getPortName() const;
    int getSpeed() const;
    void rcv_ttl_send_udp();
    void rcv_udp_send_ttl();
    void handle_receive();
    void work();
    void check_range();
    void send_cmd();
    void from_LDC();

    uint8_t get_cmdLen() const;

private:
    QString _portName{"ttyUSB0"};
    const uint8_t _cmdLen = 32;
    int _speed = 9600;
    quint16 _port = 4196;
    std::string _IP{"192.168.1.62"};
};
