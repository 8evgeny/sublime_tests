#include "mytime.h"
#include<iostream>

MyTime::MyTime(QObject *parent) : QObject(parent)
{

}

std::chrono::time_point<std::chrono::system_clock> MyTime::getSystemTime() const
{
    return std::chrono::system_clock::now();
}

std::chrono::time_point<std::chrono::system_clock> MyTime::getNativBighTime() const
{
    return _nativBighTime;
}

void MyTime::setNativBighTime(std::chrono::time_point<std::chrono::system_clock> newNativBighTime)
{
    _nativBighTime = newNativBighTime;
}

void MyTime::printSystemTimeMsSinceEpoch()
{
    auto t = getSystemTime();
    auto tt = t.time_since_epoch();
    std::cout<<tt.count()<<std::endl;
}

