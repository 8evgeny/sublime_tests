#include "Animal.h"

Animal::Animal(const QString &type, const QString &size)
    : mType(type), mSize(size)
{
}

QString Animal::type() const
{
    return mType;
}

QString Animal::size() const
{
    return mSize;
}

void Animal::setType(const QString &type)
{
    mType = type;
}

void Animal::setSize(const QString &size)
{
    mSize = size;
}
