#ifndef MYRUNNABLE_H
#define MYRUNNABLE_H

#include <QObject>
#include <QDebug>
#include <QMutexLocker>
#include <QThread>
#include <QRunnable>
#include <QSharedPointer>
#include <QRandomGenerator>
#include "myclass.h"

class MyRunnable: public QRunnable
{
public:
    MyRunnable();
    void run() override;

    QSharedPointer<MyClass> pointer() const;
    void setPointer(const QSharedPointer<MyClass> &pointer);

private:
    QSharedPointer<MyClass> m_pointer;
};

#endif // MYRUNNABLE_H
