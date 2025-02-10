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

    void send_udp();

private:
    quint16 _port = 4196;
    std::string _IP{"192.168.1.62"};
};
