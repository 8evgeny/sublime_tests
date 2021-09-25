#include "bird.h"

Bird::Bird(QObject *parent) : QObject(parent)
{

}

void Bird::fly()
{
    qDebug() << this << "Flying";
}

void Bird::land()
{
    qDebug() << this << "Land";
}
