#include "basicoven.h"

BasicOven::BasicOven(QObject *parent) : QObject(parent)
{

}


void BasicOven::bake()
{
    qInfo()<< this << "doing basic stuff";
    qInfo()<< this << "backing";
    qInfo()<< this << "BLAAAAA";
}
