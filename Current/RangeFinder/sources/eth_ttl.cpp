#include <eth_ttl.hpp>
#include <iostream>
#include <QtCore>
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

const QString &eth_ttl::getPortName() const
{
    return _portName;
}// END getPortName()

int eth_ttl::getSpeed() const
{
    return _speed;
}// END getSpeed()

uint8_t eth_ttl::get_cmdLen() const
{
    return _cmdLen;
}//END get_cmdLen()

void eth_ttl::work_eth_ttl()
{

    io_service io_service;
    ip::udp::socket socket(io_service);
    ip::udp::endpoint remote_endpoint;

    // socket.open(ip::udp::v4());
    remote_endpoint = ip::udp::endpoint(ip::address::from_string("192.168.1.37"),9000);
    boost::system::error_code err;



    uint8_t buf[get_cmdLen()];
    QByteArray data_from_port;
    QByteArray data_to_eth;
    // QUdpSocket udpSocketSend;
    // QUdpSocket udpSocketGet;
    quint16 portSend = 44444;
    quint16 portGet = 55555;
    char buferGet[32];

    // udpSocketGet.bind(44444, QUdpSocket::ShareAddress);

     while(1)
    {
//Read data from port
        if(serial.waitForReadyRead(1))
        {
            data_from_port.clear();
            data_from_port += serial.read(get_cmdLen());

//Print data_from_port
            printf( "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
                    "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
                    "\n",
                    buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7],
                    buf[8], buf[9], buf[10], buf[11], buf[12], buf[13], buf[14], buf[15],
                    buf[16], buf[17], buf[18], buf[19], buf[20], buf[21], buf[22], buf[23],
                    buf[24], buf[25], buf[26], buf[27], buf[28], buf[29], buf[30], buf[31]
                  );

//Send data to ethernet
            socket.open(ip::udp::v4());
            socket.send_to(buffer(data_from_port, get_cmdLen()), remote_endpoint, 0, err);
            socket.close();

        }//END if(serial.waitForReadyRead(1))

//Read data from ethernet


    }//END while(1)
}// END work_eth_ttl()


