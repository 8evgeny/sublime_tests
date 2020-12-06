#include "cat.h"
#include <iostream>

Cat::Cat()
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

Cat::Cat(uint paws) : Mammal(paws)
{
}

Cat::~Cat()
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

void Cat::say()
{
    std::cout << "meow\n";
}
