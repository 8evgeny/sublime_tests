#include <serialPort.hpp>

using namespace std;

int main(int argc, char *argv[])
{
    uint8_t request[] = {0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7A};
    unique_ptr<UART> p = make_unique<UART>();
    p->work();
    return 0;
}// END int main(int argc, char *argv[])



