#include "BaseThread.hpp"

BaseThread::BaseThread(const int32_t& executionPeriodMs)
    : _execute(false)
    , _errorFlag(false)
    , _errorID(thdNoError)
    , _thdExecutionPeriod{executionPeriodMs}
{

}

BaseThread::~BaseThread()
{
    stopThd();
}

void BaseThread::startThd()
{
    _execute.store(true);
    _thd = std::thread(&BaseThread::run, this);
    _thd.detach();
}

void BaseThread::stopThd()
{
    if(_execute.load()) // if the thread is running
    {
        _execute.store(false);
        if(_thd.joinable())
        {
            _thd.join();
        }
        closeThd();
    }
}

bool BaseThread::isRunningThd() const
{
    return _execute.load();
}

void BaseThread::run()
{
    bool error = !initThd();
    if(!error) {
        while(_execute.load()) {
            runThd();
            std::this_thread::sleep_for(std::chrono::milliseconds(_thdExecutionPeriod));
        }
        closeThd();
    } else {
        _errorID = thdInitializationError;
        closeThd();
    }
}



void BaseThread::setThdExecutionPeriodMs(const int32_t& periodMs)
{
    _thdExecutionPeriod = periodMs;
}

void BaseThread::setExecuteFlagThd(bool flag)
{
    _execute.store(flag);
}
