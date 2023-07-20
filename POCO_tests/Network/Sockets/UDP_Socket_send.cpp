// DatagramSocket send example
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"

int main(int argc, char** argv)
{
    //в консоли набрать:  sudo nc -nlvu 514
    Poco::Net::SocketAddress sa("localhost", 514);
    Poco::Net::DatagramSocket dgs;
    dgs.connect(sa);
    Poco::Timestamp now;
    std::string msg = Poco::DateTimeFormatter::format(now, "year:%y month:%m day:%f %w Time:%H:%M:%S Hello, world!");
    dgs.sendBytes(msg.data(), msg.size());
    return 0;
}
