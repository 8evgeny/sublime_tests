#ifndef TEXT_H
#define TEXT_H

#include <QObject>
#include <QDebug>

class Text : public QObject
{
    Q_OBJECT
public:
    explicit Text(QObject *parent = nullptr);
    virtual void process(QString &input);
signals:

};

#endif // TEXT_H
