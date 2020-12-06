#include "mammal.h"
#include <iostream>

Mammal::Mammal()
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

Mammal::Mammal(uint paws) : paws(paws)
{
}

Mammal::Mammal(const Mammal& other)
{
    paws = other.paws;
}

void Mammal::feed_milk()
{
}

void Mammal::say()
{
    std::cout << "say something\n";
}

Mammal::~Mammal()
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
}
