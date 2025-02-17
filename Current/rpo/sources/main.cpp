//https://open-dev.ru/manual-odtemp1#scripts
#include <sensors.hpp>
#include <iostream>
#include <thread>

using namespace std;

int main(int argc, char *argv[])
{
    unique_ptr<sensors> p = make_unique<sensors>();

    p->serial.setPortName(p->getPortName());
    p->serial.setBaudRate(p->getSpeed());
    if (!p->serial.open(QIODevice::ReadWrite))
    {
        cout << "Error open port!!!" << endl;
    }
    else
    {
        qDebug() << p->serial.portName();
//        p->work();
        p->send_temperature();
        p->check_position();
        p->check_range();
    }

return 0;
}// END while(1)



