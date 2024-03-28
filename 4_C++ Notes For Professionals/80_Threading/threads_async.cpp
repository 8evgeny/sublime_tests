#include <future>
#include <iostream>

unsigned int square(unsigned int i)
{
    return i*i;
}

int main()
{
#if 0
std::async returns a std::future that holds the return value that will be calculated by the function.
When that future gets destroyed it waits until the thread completes, making your code effectively single threaded.
This is easily overlooked when you don't need the return value
std::async works without a launch policy, so std::async(square, 5); compiles. When you do that the
system gets to decide if it wants to create a thread or not
#endif
    auto f = std::async(std::launch::async, square, 8);
    std::cout << "square currently running\n"; //do something while square is running
    std::cout << "result is " << f.get() << '\n'; //getting the result from square
}
