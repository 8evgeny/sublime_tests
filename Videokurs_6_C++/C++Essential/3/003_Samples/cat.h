#include "mammal.h"

class Cat : public Mammal
{
public:
    Cat();
    Cat(uint paws);
    uint get_paws();

    void say() override;
    ~Cat();

public:
    uint vibr;
};
