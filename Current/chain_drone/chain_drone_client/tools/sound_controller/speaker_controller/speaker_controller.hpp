#ifndef SPEAKER_CONTROLLER_HPP
#define SPEAKER_CONTROLLER_HPP

#include "settings.hpp"

#include <atomic>
#include <mutex>
#include <queue>
#include <condition_variable>

namespace sound
{
   class SpeakerController
   {
   public:
       static SpeakerController& inst();
       void setSettings(sound::speaker::SettingsPtr &settings);
       void volume(int val);
       void defaultVolume();
       void f_sound();
       void warning();
       void error();
       void quit();

   private:
       enum class Commands
       {
           VOLUME,
           WARNING,
           ERROR
       }; // -- END Commands

       struct CmdData
       {
           Commands id;
           std::string cmd;
       }; // -- END CmdData

       SpeakerController();
       SpeakerController(const SpeakerController & root) = delete;
       SpeakerController(SpeakerController &&root) = delete;
       SpeakerController& operator=(SpeakerController &&) = delete;
       ~SpeakerController();

       void workflow();

       sound::speaker::Settings settings;

       struct Sync
       {
              std::mutex queueMtx;
              std::atomic<bool> exec;
              std::condition_variable queueCV;
       } sync;

       std::queue<CmdData> cmdQueue;
       const char * warning_c_str;
       std::atomic<int> warning_num = 0;
       int warning_num_max = 25;
   }; // -- END SpeakerController
} // -- END sound

#endif // SPEAKER_CONTROLLER_HPP
