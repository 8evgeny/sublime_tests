#include "Counter.h"

#include <QDebug>
#include <QTimerEvent>

Counter::Counter(QObject* parent)
    : QObject(parent)
    , mValue(0)
{
    setValue(0);
    startTimer(2000);
}

int Counter::getValue() const
{
    return mValue;
}

void Counter::setValue(int value)
{
    mValue = value;
    emit valueChanged(value);
}

void Counter::timerEvent(QTimerEvent* event)
{
    qDebug() << "timerEvent" << event->timerId();
    setValue(mValue + 1);
}
