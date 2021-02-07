#include <iostream>
#include <thread>
//#include <chrono>
using namespace  std;
//Member function example - executes a member function on a separate thread

class Bar
{
public:
    void foo(int a)
    {
        std::cout << a << '\n';
    }
};

int main()
{
    Bar bar;
    // Create and execute the thread
    std::thread thread(&Bar::foo, &bar, 10); // Pass 10 to member function

// The member function will be executed in a separate thread
// Wait for the thread to finish, this is a blocking operation
thread.join();
return 0;

}
