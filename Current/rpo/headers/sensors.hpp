#pragma once
//Receive and sent temperature
//cat /dev/ttyACM0 | socat - udp-datagram:192.168.1.62:5000
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "boost/asio.hpp"

class sensors
{

public:
    sensors();
    ~sensors();
    QSerialPort serial;
    const QString &getPortName() const;
    int getSpeed() const;
//    void rcv_ttl_send_udp();
//    void rcv_udp_send_ttl();
//    void handle_receive();
//    void work();
    void check_range();
    void send_temperature();
    void check_position();
    void position();
    void temperature();
    void send_cmd();
    void from_LDC();

    uint8_t get_cmdLen() const;

private:
    QString _portName{"ttyUSB0"};
    const uint8_t _cmdLen = 32;
    int _speed = 9600;
    quint16 _port_laser_range_finder = 4196;
    int _port_send_temperature = 5000;
    std::string _IP{"192.168.1.18"};
};
