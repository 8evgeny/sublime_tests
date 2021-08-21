#ifndef APPMAINCONTROLLER_H
#define APPMAINCONTROLLER_H

#include <QObject>
#include <QWidget>
#include "mainwiget.h"
#include "calculatepositionplanets.h"
#include "mainwindow.h"
#include "mytime.h"

class AppMainController : public QObject
{
    Q_OBJECT
public:
    explicit AppMainController(QObject *parent = nullptr);

signals:

private:
    //Здесь указатели на все контроллеры
     std::unique_ptr<MainWiget> _mainWiget = nullptr;
     std::unique_ptr<CalculatePositionPlanets> _calcPos = nullptr;
     std::unique_ptr<MainWindow> _mainWindow = nullptr;
     std::unique_ptr<MyTime> _myTime = nullptr;

};

#endif // APPMAINCONTROLLER_H
