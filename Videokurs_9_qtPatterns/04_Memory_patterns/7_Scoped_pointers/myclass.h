#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QDebug>

class MyClass : public QObject
{
    Q_OBJECT
public:
    explicit MyClass(QObject *parent = nullptr, QString name = "");
    ~MyClass();
    void test();
signals:

};

#endif // MYCLASS_H
