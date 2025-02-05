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


void eth_ttl::work()
{
    thread ttl_udp(&eth_ttl::rcv_ttl_send_udp, this);
    thread udp_ttl(&eth_ttl::rcv_udp_send_ttl, this);

    ttl_udp.join();
    udp_ttl.join();
}


void eth_ttl::rcv_ttl_send_udp()
{
    uint8_t buf[get_cmdLen()];
    QByteArray data_from_port;
    io_service io_service;
    ip::udp::socket socket(io_service);
    ip::udp::endpoint ep;
    ep = ip::udp::endpoint(ip::address::from_string(_IP), _port);
    boost::system::error_code err;
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
            socket.send_to(buffer(data_from_port, get_cmdLen()), ep, 0, err);
            socket.close();
        }//END if(serial.waitForReadyRead(1))
    }//END while(1)
}// END rcv_ttl_send_udp()



void eth_ttl::handle_receive()
{
    char buff[1024];
    io_service service;
    ip::udp::socket sock(service, ip::udp::endpoint(ip::udp::v4(), _port));
    ip::udp::endpoint ep;
    while ( true)
    {
        int bytes = sock.receive_from(buffer(buff), ep);
        std::string msg(buff, bytes);
        cout<<"Received from UDP: " << msg << endl;
        QByteArray data_from_udp(buff, bytes);
        qDebug()<<data_from_udp;
    }
}

void eth_ttl::rcv_udp_send_ttl()
{
    while(1)
    {
        handle_receive();
    }//END while(1)
}// END rcv_udp_send_ttl()
