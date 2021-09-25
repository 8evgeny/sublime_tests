#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QThread>
#include <QDebug>

class MyClass : public QObject
{
    Q_OBJECT
public:
    explicit MyClass(QObject *parent = nullptr);
    ~MyClass();

signals:
    void finished();

public slots:
    void run();

};

#endif // MYCLASS_H
