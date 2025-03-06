#include <serialPort.hpp>

using namespace std;
using namespace LibSerial;

UART::~UART()
{
    cout << "UART Dtor" << endl;
}//END ~UART()

UART::UART()
{
    cout << "UART Ctor" << endl;
    try
    {
        vector<string> ports =  _serial_ptr->GetAvailableSerialPorts();
        cout<<"--- available SerialPorts ---"<<endl;
        for(auto &i:ports)
        {
            if(i.find("USB") != string::npos) cout<<i<<endl;
        }
        cout<<endl;
        _serial_ptr = make_unique<SerialPort>(_portName);

        _port_open_OK = true;
    }//END try
    catch (...)
    {
        _port_open_OK = false;
        cout<<"Serial Port error opening !!!" <<endl;
    }//END catch

    if(_port_open_OK)
    {
        _serial_ptr->SetBaudRate(BaudRate::BAUD_230400);
        _serial_ptr->SetCharacterSize(CharacterSize::CHAR_SIZE_8);
        _serial_ptr->SetFlowControl(FlowControl::FLOW_CONTROL_NONE);
        _serial_ptr->SetParity(Parity::PARITY_NONE);
        _serial_ptr->SetStopBits(StopBits::STOP_BITS_1);
    }//END if(port_open_OK)
    else
    {
        cout<<"\n=====================  port not OPEN !!!  ======================\n" <<endl;
    }//END else


}// END UART()

void UART::work()
{
    cout<<"\n===============  port " <<_portName << " begin work  ================\n" <<endl;
    while(1)
    {
//        this_thread::sleep_for(chrono::milliseconds(10));
//        if (serial.isReadable())
//        {
//            ba = serial.readAll();
//            qDebug() << "ba: " << ba;
//        }
//        requestData.clear();
//        while (serial.waitForReadyRead(1))
//        {
//            this_thread::sleep_for(chrono::microseconds(1));
//        }
//        requestData += serial.read(_cmdLen);
//        if (requestData != "")
//        {
//            for (int i = 0; i < _cmdLen; ++i)
//            {
//                _cmdBuf[i] = requestData[i];
//            } //END for (int i = 0; i < _cmdLen; ++i)

//            if (_cmdBuf[1] == 0x90)
//            {
//                printDataRS232();
////                printDataRS232_format();
//            }

//            if(_cmdBuf[31] == 0x00 && _cmdBuf[1] == 0x90) //Признак команды
//            {
//                setCMD(find_cmd());
//            }//END if(_cmdBuf[31] == 0x00 && _cmdBuf[1] == 0x90)



//        }//END if (requestData != "")
    }//END while(1)
}// END work()

//void serialPort::printDataRS232()
//{
//    printf( "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
//            "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
//            "\n",
//            _cmdBuf[0], _cmdBuf[1], _cmdBuf[2], _cmdBuf[3], _cmdBuf[4], _cmdBuf[5], _cmdBuf[6], _cmdBuf[7],
//            _cmdBuf[8], _cmdBuf[9], _cmdBuf[10], _cmdBuf[11], _cmdBuf[12], _cmdBuf[13], _cmdBuf[14], _cmdBuf[15],
//            _cmdBuf[16], _cmdBuf[17], _cmdBuf[18], _cmdBuf[19], _cmdBuf[20], _cmdBuf[21], _cmdBuf[22], _cmdBuf[23],
//            _cmdBuf[24], _cmdBuf[25], _cmdBuf[26], _cmdBuf[27], _cmdBuf[28], _cmdBuf[29], _cmdBuf[30], _cmdBuf[31]
//            );
//}

