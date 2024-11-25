#include "handle_message.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    // Access the Singleton instance
    handleMessage * hmPtr = handleMessage::getInstance();

    hmPtr->operation1();
    hmPtr->operation3();

    delete hmPtr;

    return 0;
}

