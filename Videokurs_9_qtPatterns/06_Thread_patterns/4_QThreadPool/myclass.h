#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QThread>
#include <QRunnable>
#include <QDebug>
#include <QRandomGenerator>

class MyClass : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit MyClass(QObject *parent = nullptr);
    ~MyClass();

signals:
    void started();
    void finished();
    void progress(int value);


    // QRunnable interface
public:
    void run() override;
};

#endif // MYCLASS_H
