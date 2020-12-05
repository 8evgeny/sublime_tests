#ifndef ANIMAL_H
#define ANIMAL_H

#include <QString>

class Animal
{
public:
    Animal(const QString &type, const QString &size);

    QString type() const;
    QString size() const;

    void setType(const QString &type);
    void setSize(const QString &size);

private:
    QString mType;
    QString mSize;
};

#endif // ANIMAL_H
