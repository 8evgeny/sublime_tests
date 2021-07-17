//The Dependency inversion principle: "Depend upon abstractions, [not] concretions."

#include <QCoreApplication>
#include "basicoven.h"
#include "advancedoven.h"
#include "badoven.h"
#include "interfaces/IEvenHeat.h"

void cook(iOven *oven)
{
    oven->bake();
}

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    BasicOven basicoven;
    AdvanceOven advanceoven;
    BadOven badoven;

    cook(&basicoven);
    cook(&advanceoven);
    cook(&badoven);



    a.exit(0);
//    return a.exec();
}
