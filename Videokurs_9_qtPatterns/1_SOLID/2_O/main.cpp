/*open–closed principle states "software entities (classes, modules, functions, etc.)
should be open for extension, but closed for modification";[1] that is, such an entity
can allow its behaviour to be extended without modifying its source code*/

#include "caffinator3000.h"
#include "coffeemachine.h"
#include "shop.h"
#include <QCoreApplication>
#include <QDebug>
#include <QStringList>

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    Shop shop;
    QStringList list;
    list << "Sugar"
         << "Flavoring";

    //    CoffeeMachine machine;
    caffinator3000 c3000;

    //    shop.sellDrink(list, &machine);
    shop.sellDrink(list, &c3000);
    a.exit(0);
//    return a.exec();
}
