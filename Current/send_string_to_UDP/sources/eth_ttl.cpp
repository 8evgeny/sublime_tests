#include <eth_ttl.hpp>
#include <iostream>
#include <QtCore>
#include <thread>
#include "boost/asio.hpp"

using namespace  boost::asio;

using namespace std;

eth_ttl::eth_ttl()
{
    cout<<"eth_ttl ctor"<<endl;
}// END eth_ttl()

eth_ttl::~eth_ttl()
{
    cout<<"eth_ttl dtor"<<endl;
}// END ~eth_ttl()


void eth_ttl::send_udp()
{
    uint8_t buf[10];
    QByteArray d;
    // AE A7 04 00 05 09 BC BE
    // AE A7 04 00 0E 12 BC BE
    d[0] = 0xAE;
    d[1] = 0xA7;
    d[2] = 0x04;
    d[3] = 0x00;
    d[4] = 0x05;
    d[5] = 0x09;
    d[6] = 0xBC;
    d[7] = 0xBE;
    io_service io_service;
    ip::udp::socket socket(io_service);
    ip::udp::endpoint ep;
    ep = ip::udp::endpoint(ip::address::from_string(_IP), _port);
    boost::system::error_code err;

//Send data to ethernet
    while(1)
    {
            socket.open(ip::udp::v4());
            socket.send_to(buffer(d, 10), ep, 0, err);
            socket.close();
            this_thread::sleep_for(std::chrono::milliseconds(3000));
    }

}// END send_udp()








