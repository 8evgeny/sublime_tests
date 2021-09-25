#ifndef BOB_H
#define BOB_H

#include <QObject>
#include <QDebug>

class Bob : public QObject
{
    Q_OBJECT
public:
    explicit Bob(QObject *parent = nullptr);
    void fixit(QString room, QString thing);
signals:

private:
    int m_times;
};

#endif // BOB_H
