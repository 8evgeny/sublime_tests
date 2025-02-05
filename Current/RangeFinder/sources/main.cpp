#include <eth_ttl.hpp>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    unique_ptr<eth_ttl> p = make_unique<eth_ttl>();

    p->serial.setPortName(p->getPortName());
    p->serial.setBaudRate(p->getSpeed());
    if (!p->serial.open(QIODevice::ReadWrite))
    {
        cout << "Error open port!!!" << endl;
    }
    else
    {
        qDebug() << p->serial.portName();
        p->work_eth_ttl();
    }

return 0;
}// END while(1)



