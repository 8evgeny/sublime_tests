#include <RS232_parser.hpp>
using namespace std;

RS232_parser::RS232_parser()
{
    cout<<"RS232_parser ctor"<<endl;
}// END RS232_parser()

RS232_parser::~RS232_parser()
{
    cout<<"RS232_parser dtor"<<endl;
}// END ~RS232_parser()

const QString &RS232_parser::getPortName() const
{
    return _portName;
}// END getPortName()

int RS232_parser::getSpeed() const
{
    return _speed;
}// END getSpeed()

uint8_t RS232_parser::getCmdLen() const
{
    return cmdLen;
}//END getCmdLen()

void RS232_parser::parsing()
{
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    QString product{"1a86"};
    for (const QSerialPortInfo &portInfo : serialPortInfos)
    {
//        qDebug() << "\n"
//                 << "Port:" << portInfo.portName() << "\n"
//                 << "Location:" << portInfo.systemLocation() << "\n"
//                 << "Description:" << portInfo.description() << "\n"
//                 << "Manufacturer:" << portInfo.manufacturer() << "\n"
//                 << "Serial number:" << portInfo.serialNumber() << "\n"
//                 << "Vendor Identifier:"
//                 << (portInfo.hasVendorIdentifier()
//                     ? QByteArray::number(portInfo.vendorIdentifier(), 16)
//                     : QByteArray()) << "\n"
//                 << "Product Identifier:"
//                 << (portInfo.hasProductIdentifier()
//                     ? QByteArray::number(portInfo.productIdentifier(), 16)
//                     : QByteArray());
        if (portInfo.manufacturer() == product)
        {
            qDebug() <<"Port:" << portInfo.portName();
        }



    }//END for (const QSerialPortInfo &portInfo : serialPortInfos)
//1a86

    uint8_t buf[getCmdLen()];
    while(1)
    {
        QByteArray requestData;
        while (serial.waitForReadyRead(1)) {this_thread::sleep_for(chrono::microseconds(1));}

        requestData += serial.read(getCmdLen());
        if (requestData != "")
        {
            for (int i = 0;i < getCmdLen(); ++i)
            {
                buf[i] = requestData[i];
// cout<<hex<<(int)buf[i]<<" ";
            } //END for (int i = 0;i < getCmdLen(); ++i)
// cout<<dec<<endl;
            printf( "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
                    "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
                    "\n",
                    buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7],
                    buf[8], buf[9], buf[10], buf[11], buf[12], buf[13], buf[14], buf[15],
                    buf[16], buf[17], buf[18], buf[19], buf[20], buf[21], buf[22], buf[23],
                    buf[24], buf[25], buf[26], buf[27], buf[28], buf[29], buf[30], buf[31]
                    );
        }//END if (requestData != "")
    }
}// END parsing()
