#include <iostream>
#include <string>
#include "cat.h"

using namespace std;

void foo(Mammal * m)
{
    m->say();
}

int main()
{
    Cat cat;
    cat.say();

    Mammal *mammal = new Cat();
    mammal->say();

    Mammal mam;

    Mammal* mammals[2];

    mammals[0] = &cat;
    mammals[1] = &mam;

    for(int i = 0; i < 2; i++)
    {
        mammals[i]->say();
    }

    foo(mammal);

    foo(&cat);

    return 0;
}
