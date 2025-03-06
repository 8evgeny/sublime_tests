#pragma once
#include <libserial/SerialPort.h>
#include <iostream>
#include <memory>
#include <thread>

class UART
{

public:
    UART();
    ~UART();

    const int getSpeed() const;
    void work();

    void Read();

private:
    std::unique_ptr<LibSerial::SerialPort> _serial_ptr = nullptr;
    bool _port_open_OK = false;
    const std::string _portName = "/dev/ttyUSB0";

};



