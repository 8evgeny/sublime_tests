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
    void printDataFromPort(uint8_t num_byte, std::string & data);
    std::string array_uint8_to_string(uint8_t * request, int num);

//    const int getSpeed() const;
    void work();

//    void Read();

private:
    std::unique_ptr<LibSerial::SerialPort> _serial_ptr = nullptr;
    bool _port_open_OK = false;
    const std::string _portName = "/dev/ttyUSB1";
    uint8_t _readBuf[512];

};//END class UART



