#include <iostream>
#include <string>
#include "mammal.h"

using namespace std;

int main()
{
    Mammal mammal(6);
    Mammal new_mammal = mammal;

    Mammal *new_m = new Mammal();


    {
        Mammal m;
    }

    cout << "\n" << new_mammal.get_paws() << "\n";

    delete new_m;

    return 0;
}
