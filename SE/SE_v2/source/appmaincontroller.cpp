#include "appmaincontroller.h"
#include <iostream>


AppMainController::AppMainController(QObject *parent) : QObject(parent)
{
//    std::unique_ptr<MainWiget> _mainWiget(new MainWiget);
//    _mainWiget = std::make_unique<MainWiget>();

    _mainWiget.reset(new MainWiget);
    _mainWiget->print();

    _calcPos.reset(new CalculatePositionPlanets);

    _mainWindow.reset(new MainWindow);

    _myTime.reset(new MyTime);
    _myTime->printSystemTimeMsSinceEpoch();


}


