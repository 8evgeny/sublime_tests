#ifndef MAINWIGET_H
#define MAINWIGET_H

#include <QWidget>

class MainWiget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWiget(QWidget *parent = nullptr);
    void print();

signals:

};

#endif // MAINWIGET_H
