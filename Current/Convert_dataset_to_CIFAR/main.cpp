#include "convert2cifar.hpp"
using namespace std;
using namespace cv;
using namespace chrono;

int main()
{
    bool ok = false;
    unique_ptr<convert2cifar> converter = make_unique<convert2cifar>("../config.ini", ok);



} // END main
