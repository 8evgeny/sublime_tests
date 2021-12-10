#include <future>
#include <iostream>

unsigned int square(unsigned int i)
{
    return i*i;
}

int main()
{
    auto f = std::async(std::launch::async, square, 8);
    std::cout << "square currently running\n"; //do something while square is running
    std::cout << "result is " << f.get() << '\n'; //getting the result from square
}
