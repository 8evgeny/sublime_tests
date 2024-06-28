#ifndef SHARED_MEMORY_HPP
#define SHARED_MEMORY_HPP

#include "devices/device.hpp"
#include "shared_memory_settings.hpp"
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <atomic>
#include <condition_variable>
#include <memory>


namespace devices
{
    class SharedMemory : public Device
    {
    public:
        SharedMemory(const shared_memory::UserSettings &settings);
        ~SharedMemory();
        void setup() override;
        void start() override;
        void quit() override;

        // uint8_t* receiveFrame(int &w, int &h, int &id, int &num) override; // временно не используется
        void getFormatedImage(uint8_t *f, int w, int h, int id, cv::Mat &image) override; 
        int getId() override {return frame_id;}
        bool getState()  override {return 1;};
        int getColorChannels() override;
        bool isBayerColorChannel() override;
        void keyHandler(uchar &key) override;
        void workflow() override;
    private:
        void exec(); // прием фреймов из gst конвейера + конвертация формата

        /*
        Временной интервал (шаг) запроса фрейма из gst-конвейера. 
        Рассчитывается автоматически на основании ini-параметра "fps_output".
        При увеличении частоты запроса фреймов увеличивается ресурсоемкость процесса поставки фреймов application'у, 
        следовательно, снижается кадровая частота основного цикла приложения (fps_scan);
        */ 
        int frame_request_delay_ms = 50; //Рассчитывается автоматически на базе fps_output

        /*
            need_io_resize -- Флаг состояния соответствия разрешений
                входного (из gst) и выходного (в application) crop-изображений
        */
        bool need_io_resize = true; // need Input/Output resize
        bool use_videorate = true; // if cam fps not equal out fps (if fps_denominator not equal 1 not use videorate)

        shared_memory::UserSettings settings;
        shared_memory::Settings gen_settings;
        
        struct Sync
        {
            std::atomic<bool> execute           = {false};
            std::atomic<bool> exec_complete     = {false};
            std::atomic<bool> quit_was_call     = {false};
            std::atomic<bool> success_quit  = {false};
        } sync; // примитивы внутренней синхронизации

        cv::Mat frame_receive; // фрейм, принимаемый напрямую из gst-конвейера
#if defined(CCM_8UC3)
        cv::Mat frame_intermediate; // промежуточный преобразованный фрейм
#endif
        cv::Mat frame_prepared; // подготовленный к отправке подписчикам фрейм
        cv::Mat frame_crop;
        std::string pipeline;
        cv::VideoCapture gst_cap; // pipeline management
        int frame_id = 0;
        int watchdog_close_time_ms = 3'000;
    };
} // -- END namespace devices

#endif //SHARED_MEMORY_HPP
