#ifndef MYTIME_H
#define MYTIME_H

#include <QObject>
#include <chrono>

class MyTime : public QObject
{
    Q_OBJECT
public:
    explicit MyTime(QObject *parent = nullptr);

    std::chrono::time_point<std::chrono::system_clock> getSystemTime() const;

    std::chrono::time_point<std::chrono::system_clock> getNativBighTime() const;
    void setNativBighTime(std::chrono::time_point<std::chrono::system_clock> newNativBighTime);
    void printSystemTimeMsSinceEpoch();
signals:
private:
    std::chrono::time_point<std::chrono::system_clock> _systemTime; //текущее системное время
    std::chrono::time_point<std::chrono::system_clock> _nativBighTime;
};

#endif // MYTIME_H
