#include <RS232_parser.hpp>
using namespace std;

RS232_parser::RS232_parser()
{
    cout << "RS232_parser Ctor" << endl;
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &portInfo : serialPortInfos)
    {
        if (portInfo.manufacturer() == _product)
        {
            _portName = portInfo.portName();
            cout <<"Port:" << portInfo.portName().toStdString() << endl;
        }
    }//END for (const QSerialPortInfo &portInfo : serialPortInfos)
}// END RS232_parser()

RS232_parser::~RS232_parser()
{
    cout << "RS232_parser Dtor" << endl;
}// END ~RS232_parser()

const QString &RS232_parser::getPortName() const
{
    return _portName;
}// END getPortName()

const int RS232_parser::getSpeed() const
{
    return _speed;
}// END getSpeed()

uint8_t RS232_parser::getCmdLen() const
{
    return _cmdLen;
}

uint8_t RS232_parser::CMD() const
{
    return _CMD;
}

void RS232_parser::setCMD(uint8_t newCMD)
{
    _CMD = newCMD;
}//END getCmdLen()

void RS232_parser::parsing()
{
//    uint8_t buf_print[getCmdLen()];
    QByteArray requestData;
    int i = 0;
    while(1)
    {
        requestData.clear();
        while (serial.waitForReadyRead(1))
        {
            this_thread::sleep_for(chrono::microseconds(1));
        }
        requestData += serial.read(_cmdLen);
        if (requestData != "")
        {
            for (int i = 0; i < _cmdLen; ++i)
            {
                _cmdBuf[i] = requestData[i];
            } //END for (int i = 0; i < _cmdLen; ++i)

//            printDataRS232();

            if(_cmdBuf[31] == 0x00 && _cmdBuf[1] == 0x90) //Признак команды
            {
                setCMD(find_cmd());
            }//END if(_cmdBuf[31] == 0x00 && _cmdBuf[1] == 0x90)

            switch (CMD())
            {
                case CMD::STOP: {cout<<"CMD::STOP"<<endl; break;}
                case CMD::LEFT: {cout<<"CMD::LEFT"<<endl; break;}
                case CMD::RIGHT: {cout<<"CMD::RIGHT"<<endl; break;}
                case CMD::UP: {cout<<"CMD::UP"<<endl; break;}
                case CMD::DOWN: {cout<<"CMD::DOWN"<<endl; break;}
                case CMD::INFRA: {cout<<"CMD::INFRA"<<endl; break;}
                case CMD::TV: {cout<<"CMD::TV"<<endl; break;}
                case CMD::ZOOM_MINUS: {cout<<"CMD::ZOOM_MINUS"<<endl; break;}
                case CMD::ZOOM_PLUS: {cout<<"CMD::ZOOM_PLUS"<<endl; break;}
                case CMD::TO_CENTRE: {cout<<"CMD::TO_CENTRE"<<endl; break;}
                case CMD::TRACKING_START: {cout<<"CMD::TRACKING_START"<<endl; break;}
                case CMD::TRACKING_STOP: {cout<<"CMD::TRACKING_STOP"<<endl; break;}

                default:
                {
                    ++i;
                    if (i == 30)
                    {
                        cout << ". . . " << endl;
                        i = 0;
                    }
                }
            }// END switch (CMD())

            setCMD(CMD::notCMD);

        }//END if (requestData != "")
    }//END while(1)
}// END parsing()

void RS232_parser::printDataRS232()
{
    printf( "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
            "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
            "\n",
            _cmdBuf[0], _cmdBuf[1], _cmdBuf[2], _cmdBuf[3], _cmdBuf[4], _cmdBuf[5], _cmdBuf[6], _cmdBuf[7],
            _cmdBuf[8], _cmdBuf[9], _cmdBuf[10], _cmdBuf[11], _cmdBuf[12], _cmdBuf[13], _cmdBuf[14], _cmdBuf[15],
            _cmdBuf[16], _cmdBuf[17], _cmdBuf[18], _cmdBuf[19], _cmdBuf[20], _cmdBuf[21], _cmdBuf[22], _cmdBuf[23],
            _cmdBuf[24], _cmdBuf[25], _cmdBuf[26], _cmdBuf[27], _cmdBuf[28], _cmdBuf[29], _cmdBuf[30], _cmdBuf[31]
            );
}//END printDataRS232()
