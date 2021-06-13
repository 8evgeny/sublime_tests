#include "coffeemachine.h"

CoffeeMachine::CoffeeMachine(QObject* parent)
    : QObject(parent)
{
}

void CoffeeMachine::addIngredients(QStringList& list)
{
    foreach (QString item, list) {
        qDebug() << "Adding: " << item;
    }
}

void CoffeeMachine::brew()
{
    qDebug() << "Heating";
    qDebug() << "Pour";
    qDebug() << "Beep";
}
