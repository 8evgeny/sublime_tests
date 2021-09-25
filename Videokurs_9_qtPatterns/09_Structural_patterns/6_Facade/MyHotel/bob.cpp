#include "bob.h"

Bob::Bob(QObject *parent) : QObject(parent)
{
    m_times = 0;
}

void Bob::fixit(QString room, QString thing)
{
    m_times++;
    if(m_times < 9)
    {
        qInfo() << "Yea Yea I'll get to it";
        return;
    }

    qInfo() << "OK OK, im headed there to" << room << "to fix" << thing;
}
