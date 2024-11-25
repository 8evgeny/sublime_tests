#include "handle_message.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    // Access the Singleton instance
    handleMessage & hm = handleMessage::getInstance();
    handleMessage & hm2 = handleMessage::getInstance();

    hm.operation1();
    handleMessage::getInstance().operation3();
    hm2.operation2();
    return 0;
}

