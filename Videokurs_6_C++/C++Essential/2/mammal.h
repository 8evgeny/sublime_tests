#include <string>


typedef unsigned int uint;

class Mammal
{
//default: private
public:
    Mammal();
    Mammal(uint paws);
    Mammal(const Mammal&);

    ~Mammal();
    void feed_milk();
    uint get_paws()
    {
        return paws;
    }
private:
    uint paws = 4;
    int* ptr;
};


