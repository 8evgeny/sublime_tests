#include "beeper_controller.hpp"
#include <thread>
#include <iostream>

#include <JetsonGPIO.h>

using namespace sound;

BeeperController::BeeperController()
{
    std::cout << " --- BEGIN конструктор объекта класса BeeperController" << std::endl;
    if(GPIO::getmode() != GPIO::BOARD)
    {
        GPIO::setmode(GPIO::BOARD);
    }
    sync.exec.store(true, std::memory_order_release);
    sync.workflow_done.store(false, std::memory_order_release);
    std::thread(&BeeperController::workflow, this).detach();
    std::cout << " --- END конструктор объекта класса BeeperController" << std::endl;
}

BeeperController::~BeeperController()
{
    std::cout << " --- BEGIN деструктор объекта класса BeeperController" << std::endl;
    quit();
    std::cout << " --- END деструктор объекта класса BeeperController" << std::endl;
}

void BeeperController::workflow()
{
    if(GPIO::getmode() != GPIO::BOARD)
    {
        GPIO::setmode(GPIO::BOARD);
    }
    while(sync.exec.load(std::memory_order_acquire))
    {
        std::unique_lock lock(sync.queueMtx);
        sync.queueCV.wait(lock);
        bool flag = !cmdQueue.empty();
        //std::cout << " ---- FLAG = " << flag << std::endl;
        //std::cout << "[BEFORE while(flag)] cmdQueue.size()  = " << cmdQueue.size() << "\n";
        while(flag)
        {
            CmdData data = cmdQueue.front();
            //std::cout << "cmdQueue.size() = " << cmdQueue.size() << "\n";
            cmdQueue.pop();
            if(data.id == Commands::SYSTEM ||
                    (data.id == Commands::ALARM &&
                     (std::chrono::system_clock::now() - data.time) <
                     std::chrono::duration(std::chrono::milliseconds(data.length * 3))) )
            {
                lock.unlock();
                switch(settings.defaultLavel)
                {
                case beeper::LAVEL::HIGH:
                default:
                    low();
                    break;
                case beeper::LAVEL::LOW:
                    high();
                    break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(data.length));
                switch(settings.defaultLavel)
                {
                case beeper::LAVEL::HIGH:
                default:
                    high();
                    break;
                case beeper::LAVEL::LOW:
                    low();
                    break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(data.length));
                lock.lock();
            }
            flag = !cmdQueue.empty();
        }
    }
    sync.workflow_done.store(true, std::memory_order_release);
}

BeeperController &BeeperController::inst()
{
    static BeeperController instance;
    return instance;
}

void BeeperController::setSettings(beeper::SettingsPtr &settings)
{
    this->settings = *settings;
    for(const auto &pin : this->settings.pins)
    {
        GPIO::setup(pin, GPIO::OUT);
        GPIO::output(pin, static_cast<int>(this->settings.defaultLavel));
        std::cout << "PIN №" << static_cast<int>(pin) << " установлен BeeperController'ом как OUTPUT" << std::endl;
    }
}

void BeeperController::system()
{
    std::unique_lock lock(sync.queueMtx);
    cmdQueue.push(CmdData{Commands::SYSTEM,
                          std::chrono::system_clock::now(),
                          settings.sounds.system});
    sync.queueCV.notify_one();
}

void BeeperController::alarm()
{
    std::unique_lock lock(sync.queueMtx);
    cmdQueue.push(CmdData{Commands::ALARM,
                          std::chrono::system_clock::now(),
                          settings.sounds.alarm});
    sync.queueCV.notify_one();
}

void BeeperController::high()
{
//    std::cout << "high()" << std::endl;
    for(const auto &pin : settings.pins)
    {
        //std::cout << " === beeper output HIGH" << std::endl;
        GPIO::output(pin, GPIO::HIGH);
    }
}

void BeeperController::low()
{
//    std::cout << "low()" << std::endl;
    for(const auto &pin : settings.pins)
    {
        //std::cout << " === beeper output LOW" << std::endl;
        GPIO::output(pin, GPIO::LOW);
    }
}

void BeeperController::quit()
{
    if(quit_was_apply)
    {
        std::cout << "BeeperController::quit() was apply earlier" << std::endl;
        return;
    }
    std::cout << " --- BEGIN BeeperController::quit()" << std::endl;
    sync.exec.store(false, std::memory_order_release);
    // Если остаточное пищание очень продолжительное, то здесь можно заблокировать мбютекс очереди и очистить ее
    sync.queueCV.notify_one();

    std::cout << " ---- BeeperController :: Wait when workflow_done \n";

    while(!sync.workflow_done.load(std::memory_order_acquire))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    std::this_thread::sleep_for(std::chrono::microseconds(100));
    std::cout << " ---- Cleanup pins beeper controller" << std::endl;
    for(const auto &pin : settings.pins)
    {
        GPIO::cleanup(pin);
    }
//    switch(settings.defaultLavel)
//    {
//    case beeper::LAVEL::HIGH:
//    default:
//        high();
//        break;
//    case beeper::LAVEL::LOW:
//        low();
//        break;
//    }
    quit_was_apply = true;
    std::cout << " --- END BeeperController::quit()" << std::endl;
}

