#include <iostream>
#include <thread>
//#include <chrono>
using namespace  std;
//Free function example - executes a function on a separate thread

void foo(int a)
{
    std::cout << a << '\n';
}
int main()
{
    // Create and execute the thread
    std::thread thread(foo, 10); // foo is the function to execute, 10 is the
    // argument to pass to it

// Keep going; the thread is executed separately
// Wait for the thread to finish; we stay here until it is done
thread.join();
return 0;
}
