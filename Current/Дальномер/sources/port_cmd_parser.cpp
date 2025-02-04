#include <port_cmd_parser.hpp>
#include <xserial.hpp>

using namespace std;

port_cmd_parser::port_cmd_parser()
{
    // инициализируем доступный COM порт, без проверки бита четности, с 8-мью битами данных и одним стоп битом.
    xserial::ComPort com(115200,com.COM_PORT_NOPARITY, 8, com.COM_PORT_ONESTOPBIT);
    if (!com.getStateComPort())
    {// Если порт не открылся
        cout << "Error: com port is not open!" << endl;
    }

    // выводим список доступых портов
    com.printListSerialPorts();


    cout << "port_cmd_parser Ctor" << endl;
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &portInfo : serialPortInfos)
    {
        if (portInfo.manufacturer() == _product)
        {
            _portName = portInfo.portName();
            cout <<"Port:" << portInfo.portName().toStdString() << endl;
        }
    }//END for (const QSerialPortInfo &portInfo : serialPortInfos)
}// END port_cmd_parser()

port_cmd_parser::~port_cmd_parser()
{
    cout << "port_cmd_parser Dtor" << endl;
}// END ~port_cmd_parser()

const QString &port_cmd_parser::getPortName() const
{
    return _portName;
}// END getPortName()

const int port_cmd_parser::getSpeed() const
{
    return _speed;
}// END getSpeed()

uint8_t port_cmd_parser::getCmdLen() const
{
    return _cmdLen;
}

uint8_t port_cmd_parser::CMD() const
{
    return _CMD;
}

void port_cmd_parser::setCMD(uint8_t newCMD)
{
    _CMD = newCMD;
}//END getCmdLen()

void port_cmd_parser::parsing()
{
    uint8_t buf_print[getCmdLen()];
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

            if (_cmdBuf[1] == 0x90)
            {
                printDataRS232();
//                printDataRS232_format();
            }

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
//                        cout << ". . . " << endl;
                        i = 0;
                    }
                }
            }// END switch (CMD())

            setCMD(CMD::notCMD);

        }//END if (requestData != "")
    }//END while(1)
}// END parsing()

void port_cmd_parser::printDataRS232()
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

void port_cmd_parser::printDataRS232_format()
{
    printf( "x: %02X%02X  y: %02X%02X"
            "\n",
            _cmdBuf[4], _cmdBuf[3], _cmdBuf[6], _cmdBuf[5]
            );

    /// dbg::
    int16_t x_dec;
    int16_t y_dec;

    uint8_t _xBuf[2];
    _xBuf[0]=_cmdBuf[3];
    _xBuf[1]=_cmdBuf[4];
    memcpy(&x_dec, _xBuf, 2);
    uint8_t _yBuf[2];
    _yBuf[0]=_cmdBuf[5];
    _yBuf[1]=_cmdBuf[6];
    memcpy(&y_dec, _yBuf, 2);

    printf( "1: x: %i  y: %i"
            "\n",
            x_dec, y_dec
            );


    memcpy(&x_dec, _cmdBuf + 3, 2);
    memcpy(&y_dec, _cmdBuf + 5, 2);
    printf( "2: +"
            "x: %i  y: %i"
            "\n",
            x_dec, y_dec
            );

}//END printDataRS232()
