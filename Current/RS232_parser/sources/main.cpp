#include <RS232_parser.hpp>

using namespace std;

int main(int argc, char *argv[])
{
    unique_ptr<RS232_parser> p = make_unique<RS232_parser>();

    p->serial.setPortName(p->getPortName());
    p->serial.setBaudRate(p->getSpeed());

    p->serial.open(QIODevice::ReadOnly);
    qDebug() << p->serial.portName();

    p->parsing();

return 0;
}// END while(1)



