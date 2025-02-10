#include <eth_ttl.hpp>
#include <iostream>
#include <QtCore>
#include <thread>
#include "boost/asio.hpp"

using namespace  boost::asio;

using namespace  std::chrono_literals;
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
}//END  work()

void eth_ttl::check_range()
{
    thread send_cmd(&eth_ttl::send_cmd, this);
    thread from_LDC(&eth_ttl::from_LDC, this);

    from_LDC.join();
    send_cmd.join();
}//END check_range()

void eth_ttl::send_cmd()
{
    char b[1024];
    io_service service;
    ip::udp::socket sock(service, ip::udp::endpoint(ip::udp::v4(), _port));
    ip::udp::endpoint ep;
    ep = ip::udp::endpoint(ip::address::from_string(_IP), _port);
    bool cmdFromOperatorReceeve = false;

    while(1)
    {

        sock.receive_from(buffer(b), ep);
        printf( "CMD FROM OPERATOR:\n%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
               "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
               "\n\n",
               b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7],
               b[8], b[9], b[10], b[11], b[12], b[13], b[14], b[15],
               b[16], b[17], b[18], b[19], b[20], b[21], b[22], b[23],
               b[24], b[25], b[26], b[27], b[28], b[29], b[30], b[31]
               );
        if(b[0] == 0xAE &&
            b[1] == 0xA7 &&
            b[2] == 0x04 &&
            b[3] == 0x00 &&
            b[4] == 0x05 &&
            b[5] == 0x09 &&
            b[6] == 0xBC &&
            b[7] == 0xBE)
        {
            cmdFromOperatorReceeve = true;
        }

        if(cmdFromOperatorReceeve)
        {
            char buff[1024];
            buff[0] = 0xAE;
            buff[1] = 0xA7;
            buff[2] = 0x04;
            buff[3] = 0x00;
            buff[4] = 0x05;
            buff[5] = 0x09;
            buff[6] = 0xBC;
            buff[7] = 0xBE;
            buff[8] = 0x00;
            serial.write(buff, 9);
            serial.waitForBytesWritten(100);

            printf( "Command:\n%02X %02X %02X %02X %02X %02X %02X %02X "
                   "\n",
                   buff[0], buff[1], buff[2], buff[3], buff[4], buff[5], buff[6], buff[7]
                   );

            // this_thread::sleep_for(5000ms);
        }//END if
    }//END while(1)
}//END send_cmd()

void eth_ttl::from_LDC()
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
        if(serial.waitForReadyRead(100))
        {
            data_from_port.clear();
            data_from_port += serial.read(get_cmdLen());
            for (int i = 0; i < 32; ++i)
            {
                buf[i] = data_from_port[i];
            }
            // serial.write(data_from_port);
            //Print data_from_port
            printf( "FROM LDC:\n%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
                   "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
                   "\n\n",
                   buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7],
                   buf[8], buf[9], buf[10], buf[11], buf[12], buf[13], buf[14], buf[15],
                   buf[16], buf[17], buf[18], buf[19], buf[20], buf[21], buf[22], buf[23],
                   buf[24], buf[25], buf[26], buf[27], buf[28], buf[29], buf[30], buf[31]
                   );
            socket.open(ip::udp::v4());
            socket.send_to(buffer(data_from_port, get_cmdLen()), ep, 0, err);
            socket.close();

        }//END if(serial.waitForReadyRead(1))
    }//END while(1)
}//END from_LDC()









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
        if(serial.waitForReadyRead(100))
        {
            data_from_port.clear();
            data_from_port += serial.read(get_cmdLen());
            for (int i = 0; i < 32; ++i)
            {
                buf[i] = data_from_port[i];
            }
            // serial.write(data_from_port);
//Print data_from_port
            printf( "TTL TO UDP:\n%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
                    "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
                    "\n\n",
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
        // QByteArray buf(buff, bytes);
        // buf.chop(1); //Delete \n
        printf( "UDP TO TTL:\n%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
               "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
               "\n\n",
               buff[0], buff[1], buff[2], buff[3], buff[4], buff[5], buff[6], buff[7],
               buff[8], buff[9], buff[10], buff[11], buff[12], buff[13], buff[14], buff[15],
               buff[16], buff[17], buff[18], buff[19], buff[20], buff[21], buff[22], buff[23],
               buff[24], buff[25], buff[26], buff[27], buff[28], buff[29], buff[30], buff[31]
               );


        serial.write(buff, bytes);
        serial.waitForBytesWritten(100);
    }//END while

//Send data to port


}//END handle_receive()

void eth_ttl::rcv_udp_send_ttl()
{
    while(1)
    {
        handle_receive();
    }//END while(1)
}// END rcv_udp_send_ttl()
