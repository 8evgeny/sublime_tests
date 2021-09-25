#include "coffeemachine.h"
#include <iostream>
using std::cout;
using std::endl;

CoffeeMachine::CoffeeMachine(QObject* parent)
    : QObject(parent)
{
}

void CoffeeMachine::addIngredients(QStringList& list)
{
    foreach (QString item, list) {
//        qDebug() << "Adding: " << item;
        std::cout << "Adding: " << item.toStdString() << endl;
    }
}

void CoffeeMachine::brew()
{
//    qDebug() << "Heating";
    std::cout << "Heating" << endl;
//    qDebug() << "Pour";
    std::cout << "Pour" << endl;
//    qDebug() << "Beep";
    std::cout << "Beep" << endl;
}
