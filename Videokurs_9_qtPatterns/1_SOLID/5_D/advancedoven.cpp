#include "advancedoven.h"

AdvanceOven::AdvanceOven(QObject *parent) : QObject(parent)
{

}


void AdvanceOven::bake()
{
    qInfo() << this << "do anvanced oven stuff";
    flip();
    rotate();
    qInfo() << this << "bake";
}

void AdvanceOven::flip()
{
    qInfo() << this << "flip the food";
}

void AdvanceOven::rotate()
{
        qInfo() << this << "rotate";
}
