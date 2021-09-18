#pragma once

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include <QThread>

class test : public QObject
{
    Q_OBJECT
public:
    explicit test(QObject *parrent = nullptr);

signals:

public slots:
    void timeout();
    void start();

private:
    QTimer timer;
};
