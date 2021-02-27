#include <string>
#include <iostream>

typedef unsigned int uint;

class Mammal
{
//default: private
public:
    Mammal();
    Mammal(uint paws);
    Mammal(const Mammal&);

    virtual ~Mammal();
    void feed_milk();
    uint get_paws()
    {
        return paws;
    }

    virtual void say();

protected:
    uint paws = 4;

};


