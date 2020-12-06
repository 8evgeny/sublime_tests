#include "mammal.h"
#include <iostream>

Mammal::Mammal()
{
    std::cout << "Ctor was called";
    ptr = new int[10];
}

Mammal::Mammal(uint paws) : paws(paws)
{
    std::cout << "User Ctor was called";
    ptr = new int[10];
}

Mammal::Mammal(const Mammal& other)
{
    paws = other.paws;
    ptr = new int[10];
}

void Mammal::feed_milk()
{
    std::cout << "done!" << "\n";
}

Mammal::~Mammal()
{
    delete[] ptr;
    std::cout << "Dtor done!" << "\n";
}
