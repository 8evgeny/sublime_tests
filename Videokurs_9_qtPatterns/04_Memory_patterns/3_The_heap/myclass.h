#ifndef MYCLASS_H
#define MYCLASS_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QTime>
#include <limits>

//Notice this is NOT a Qbject

class MyClass
{
public:
    //Constructor
    MyClass();

    //Copy Constructor -  we tend to take this for granted and just let C++ copy like crazy
    MyClass (const MyClass &old);

    //Deconstructor
    ~MyClass();

    QByteArray data() const;
    void setData(const QByteArray &data);

    void log(QString message);
private:
    QByteArray m_data;
};

#endif // MYCLASS_H
