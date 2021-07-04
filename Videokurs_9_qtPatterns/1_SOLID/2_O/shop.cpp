#include "shop.h"
#include <iostream>
using std::cout;
using std::endl;

Shop::Shop(QObject* parent)
    : QObject(parent)
{
}

void Shop::sellDrink(QStringList list, iBrew* machine)
{
//    qInfo() << "Take the order";
    cout << "Take the order" << endl;
    machine->addIngredients(list);
    machine->brew();
//    qInfo() << "Take payment";
    cout << "Take payment" << endl;
//    qInfo() << "Give the customer their order";
    cout << "Give the customer their order" << endl;
}
