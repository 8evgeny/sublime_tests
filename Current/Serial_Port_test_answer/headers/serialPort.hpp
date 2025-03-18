#pragma once
#include <libserial/SerialPort.h>
#include <iostream>
#include <memory>
#include <thread>
#include <functional>
#include <atomic>

class UART
{
public:
    UART();
    ~UART();
    void printDataFromPort(uint8_t num_byte, std::string & data);
    std::string array_uint8_to_string(uint8_t * request, int num);

    void init_crc_calculation();
    uint8_t crc_calc(uint8_t *data, uint8_t size);
    void work();

private:
    std::unique_ptr<LibSerial::SerialPort> _serial_ptr = nullptr;
    bool _port_open_OK = false;
    const std::string _portName = "/dev/ttyUSB1";
    uint8_t _readBuf[512];
    std::atomic_bool handshake = {false};

    #define CRC_TABLE_SIZE 256
    uint8_t _CRC8Table[CRC_TABLE_SIZE];
    uint32_t _poly_width = 8;
    bool send_telemetry_5sec = false;
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point stop;
};//END class UART



