#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QSerialPort serial;
    serial.setPortName("ttyUSB0");
    serial.setBaudRate(115200);
    serial.open(QIODevice::ReadOnly);
    qDebug() << serial.portName();
    uint8_t buf[32];
    uint8_t forParsing[32];
    for(;;)
    {
        QByteArray requestData;
        while (serial.waitForReadyRead(1))
            requestData += serial.read(36);

        if (requestData != "")
        {
            for (int i = 0;i<32;++i)
            {
                forParsing[i] = requestData[i];
                buf[i] = requestData[i];
//                cout<<hex<<(int)buf[i]<<" ";
            }
//            cout<<dec<<endl;
            printf("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
            "\n",
            buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], buf[8], buf[9], buf[10], buf[11], buf[12], buf[13], buf[14], buf[15],
            buf[16], buf[17], buf[18], buf[19], buf[20], buf[21], buf[22], buf[23], buf[24], buf[25], buf[26], buf[27], buf[28], buf[29], buf[30], buf[31]
            );
        }
    }

return 0;
}



