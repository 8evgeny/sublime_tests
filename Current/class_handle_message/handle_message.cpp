#include "handle_message.hpp"
#include <iostream>
using namespace std;

// Initialize the static instance variable to nullptr
handleMessage * handleMessage::instance_ptr = nullptr;

handleMessage::handleMessage()
{
    cout << "handleMessage instance created." << endl;
} // END handleMessage()

handleMessage::~handleMessage()
{
    cout << "handleMessage instance destroyed." << endl;
} // END ~handleMessage()

void handleMessage::operation1()
{
    cout << "operation 1." << endl;
}
void handleMessage::operation2()
{
    cout << "operation 2." << endl;
}
void handleMessage::operation3()
{
    cout << "operation 3." << endl;
}
