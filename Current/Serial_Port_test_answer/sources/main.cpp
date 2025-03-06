#include <serialPort.hpp>

using namespace std;

int main(int argc, char *argv[])
{
    unique_ptr<UART> p = make_unique<UART>();
    p->work();
    return 0;
}// END int main(int argc, char *argv[])



