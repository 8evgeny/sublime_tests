#include "cat.h"
#include <iostream>

Cat::Cat()
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

Cat::Cat(uint paws)
{
    paws = paws;
}

void Cat::say()
{
    std::cout << "meow\n";
}
