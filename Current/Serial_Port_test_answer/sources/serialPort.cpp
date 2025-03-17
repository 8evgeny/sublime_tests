#include <serialPort.hpp>

using namespace std;
using namespace LibSerial;

uint8_t request_data[] =    {0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7A};
uint8_t answer_data[] =     {0xAA, 0x81};
uint8_t cmd_reset_data[] =  {0xAA, 0x00, 0x00, 0x00, 0x00, 0xF1, 0x00, 0x00, 0x00, 0xF1};
uint8_t telemetry_data[] =
{
    0xAA,                   //STATE BYTE
    0x81,                   //CMD
    0x00,                   //STATUS
    0x00, 0xEE,             //SRC
    0x00, 0x00,             //DST
    0x00, 0x0A,             //WORLD CNT
    0x00, 0x00, 0x00, 0xFF, //1 State
    0x00, 0x00, 0x00, 0x00, //2 Errors
    0x01, 0x02, 0x03, 0x04, //3 AngleZ
    0x05, 0x06, 0x07, 0x08, //4 AngleX
    0x09, 0x0A, 0x0B, 0x0C, //5 SpeedZ
    0x0D, 0x0E, 0x0F, 0x00, //6 SpeedX
    0x00, 0x00, 0x00, 0x00, //7 MemsSpeedX
    0x00, 0x00, 0x00, 0x00, //8 MemsSpeedY
    0x00, 0x00, 0x00, 0x00, //9 MemsSpeedZ
    0x00, 0x00, 0x00, 0x00, //A Reserv
    0xFF                    //CRC
};//END uint8_t telemetry_data[]


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
    string cmd_request_str = array_uint8_to_string(request_data, sizeof(request_data));
    string cmd_reset_str = array_uint8_to_string(cmd_reset_data, sizeof(cmd_reset_data));
    string answ_str = array_uint8_to_string(answer_data, sizeof(answer_data));

    printf( "Good string:   ");
    printDataFromPort(10, cmd_request_str);
    cout<<"\n===============  port " <<_portName << " begin work  ================\n" <<endl;
    string read_data_str;

    function read_RS485 = [&]()
    {
        cout << "thread read_from_Port started...\n";
        int numByte1 = 0;
        int numByte2 = 0;
        while(1)
        {
            mut.lock();
            if(_serial_ptr->IsDataAvailable())
            {
                numByte1 = _serial_ptr->GetNumberOfBytesAvailable();
                this_thread::sleep_for(10ms);
                numByte2 = _serial_ptr->GetNumberOfBytesAvailable();
                if (numByte1 == numByte2)
                {
                    _serial_ptr->Read(read_data_str, numByte1);
                    cout << "Received from " << _portName << " port:   ";
                    printDataFromPort(numByte1, read_data_str);

                    if (read_data_str == cmd_request_str)
                    {
                        handshake = false;
                        cout <<"received read request...\n";
                        _serial_ptr->FlushOutputBuffer();
                        this_thread::sleep_for(50ms);
                        _serial_ptr->FlushOutputBuffer();
                        _serial_ptr->Write(answ_str);

                    }//END if (read_data_str == good_str)

                    if (read_data_str == cmd_reset_str)
                    {
                        reset = true;
                        cout <<"received cmd reset...\n";
                        handshake = true;
                        _serial_ptr->FlushOutputBuffer();
                        cout <<"send telemrtry data...\n";
                    }//END if (read_data_str == good_str)
                }
            }//END if(_serial_ptr->IsDataAvailable())
            mut.unlock();
            this_thread::sleep_for(10ms);
        }//END while(1)
    };//END function read_RS485 = [&]()
    handshake = false;
    thread readPort(read_RS485);
    readPort.detach();

    string telemetry_str = array_uint8_to_string(telemetry_data, sizeof(telemetry_data));

    cout << "thread write_to_Port started...\n";



    while (1)  //in main thread send dats as telemetry
    {
        if (handshake)
        {
            mut.lock();
            _serial_ptr->Write(telemetry_str);
            mut.unlock();
        }//END if (handshake)
        this_thread::sleep_for(10ms);
    }//END while (1)


}// END work()

void UART::printDataFromPort(uint8_t num_byte, string & data)
{
    int k = 0;
    for (int i = 0; i < num_byte; ++i)
    {
        _readBuf[i] = data[i];
    }//END for (int i = 0; i < num_byte; ++i)
    for (int i = 0; i < num_byte; ++i, ++k)
    {
//        if (k == 14) { k = 0; printf( "  " );}
        printf( "%02X ", _readBuf[i]);
    }//END for (int i = 0; i < num_byte; ++i, ++k)
    printf("\n");
}//Endn printDataFromPort

