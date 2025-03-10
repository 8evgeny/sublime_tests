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
#include <sstream>

string UART::array_uint8_to_string(uint8_t * request, int num)
{
    std::ostringstream conv;
    for (int i = 0; i < num; ++i)
    {
        conv << request[i];
    }//END for (int i = 0; i < num; ++i)
    return conv.str();
}//END array_uint8_to_string(uint8_t * request, int num)

void UART::work()
{
    uint8_t request[] = {0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7A};
    uint8_t answer[] = {0xAA, 0x81};

    string good = array_uint8_to_string(request, sizeof(request));
    string answ = array_uint8_to_string(answer, sizeof(answer));
    printf( "Good string:   ");
    printDataFromPort(10, good);
    cout<<"\n===============  port " <<_portName << " begin work  ================\n" <<endl;
    string data;
    while(1)
    {
        this_thread::sleep_for(chrono::milliseconds(10));
        if(_serial_ptr->IsDataAvailable())
        {
            int numByte = _serial_ptr->GetNumberOfBytesAvailable();
            _serial_ptr->Read(data, numByte);
            cout << "Received from " << _portName << " port:   ";
            printDataFromPort(numByte, data);
            if (data == good)
            {
                cout <<"read request...\n";
                cout <<"ansver 0xAA, 0x81\n";
                _serial_ptr->Write(answ);
            }//END if (data == goog_request)

        }//END if(_serial_ptr->IsDataAvailable())
    }//END while(1)
}// END work()

void UART::printDataFromPort(uint8_t num_byte, string & data)
{
    int k = 0;
    for (int i = 0; i < num_byte; ++i)
    {
        _readBuf[i] = data[i];
    }
    for (int i = 0; i < num_byte; ++i, ++k)
    {
        if (k == 14) { k = 0; printf( "  " );}
        printf( "%02X ", _readBuf[i]);
    }
    printf("\n");
}

