#include <iostream>
#include <string>
#include "cat.h"
#include <typeinfo>

using namespace std;

class A
{};

class B : public A
{};

int main()
{
    Animal* animal = new Cat();

    A* a = static_cast<A*>(new B());

    Animal* an = animal;
    Pedigreed* ptr_ped = dynamic_cast<Pedigreed*>(an);

    if(dynamic_cast<void*>(animal) == dynamic_cast<void*>(ptr_ped))
    {
        cout << "yes";
    }

    auto ped = dynamic_cast<Pedigreed*>(animal);
    auto cat = dynamic_cast<Cat*>(ped);
    if ( auto dom = dynamic_cast<Domestic*>(cat) )
    {
        cout << "Domestic";
        cout << dom->get_name();
    }
    return 0;
}
