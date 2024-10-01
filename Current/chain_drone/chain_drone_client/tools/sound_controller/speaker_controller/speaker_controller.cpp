#include "speaker_controller.hpp"
#include <thread>
#include <iostream>

using namespace sound;

static void initDevice(const std::string &device)
{
    std::string defaultDeviceCmd = "pactl set-default-sink " + device;
    int status = system(defaultDeviceCmd.c_str());
} // -- END initDevice

SpeakerController::SpeakerController()
{
    sync.exec.store(true, std::memory_order_release);
    std::thread(&SpeakerController::workflow, this).detach();
} // END SpeakerController

SpeakerController::~SpeakerController()
{
    quit();
} // -- END ~SpeakerController

void SpeakerController::workflow()
{
    while(sync.exec.load(std::memory_order_acquire))
    {
        std::unique_lock lock(sync.queueMtx);
        sync.queueCV.wait(lock);
        bool flag = !cmdQueue.empty();
        while(flag)
        {
            CmdData data = cmdQueue.front();
            cmdQueue.pop();
            lock.unlock();
            int status = system(data.cmd.c_str());
            lock.lock();
            flag = !cmdQueue.empty();
        } // -- END while(flag)
    } // -- END while(sync.exec.load(std::memory_order_acquire))
} // -- END workflow

SpeakerController &SpeakerController::inst()
{
    static SpeakerController instance;
    return instance;
} // -- END inst

void SpeakerController::setSettings(speaker::SettingsPtr& settings)
{
    this->settings = *settings;
    initDevice(this->settings.device);
} // -- END setSettings

void SpeakerController::volume(int val)
{
    std::unique_lock lock(sync.queueMtx);
    cmdQueue.push(CmdData{Commands::VOLUME,
                          "pactl set-sink-volume " + settings.device + " " + std::to_string(val) + "%"});
    sync.queueCV.notify_one();
} // -- END volume

void SpeakerController::defaultVolume()
{
    volume(settings.defaultVolume);
    warning_c_str = settings.sounds.warning.c_str();
} // -- END defaultVolume


void SpeakerController::f_sound()
{
   int status = system(settings.sounds.warning.c_str());
   std::this_thread::sleep_for(std::chrono::milliseconds(200));
   status = system(settings.sounds.warning.c_str());
   std::this_thread::sleep_for(std::chrono::milliseconds(200));
   status = system(settings.sounds.warning.c_str());
   std::this_thread::sleep_for(std::chrono::milliseconds(200));
   status = system(settings.sounds.warning.c_str());
   std::this_thread::sleep_for(std::chrono::milliseconds(200));
   status = system(settings.sounds.warning.c_str());
   //system(warning_c_str);
   warning_num--;
} // -- END f_sound


void SpeakerController::warning()
{
    if(warning_num < warning_num_max)
    {
       warning_num++;
       std::thread thr_sound(&SpeakerController::f_sound, this);
       thr_sound.detach();
    } // -- END if(sound_num < sound_num_max)
} // -- END warning

//void SpeakerController::warning()
//{
//    //beep(settings.sounds.warning);
//    std::unique_lock lock(sync.queueMtx);
//    cmdQueue.push(CmdData{Commands::WARNING, settings.sounds.warning});
//    sync.queueCV.notify_one();
//} // -- END warning

void SpeakerController::error()
{
//    beep(settings.sounds.error);
    std::unique_lock lock(sync.queueMtx);
    cmdQueue.push(CmdData{Commands::ERROR, settings.sounds.error});
    sync.queueCV.notify_one();
} // -- END error

void SpeakerController::quit()
{
    sync.exec.store(false, std::memory_order_release);
    sync.queueCV.notify_one();
    std::this_thread::sleep_for(std::chrono::microseconds(100));
} // -- END quit

