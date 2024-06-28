#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include <opencv2/core/core.hpp>
#include "devices/device.hpp"
#include "devices/iframehandler.h"
#include "INIReader.h"
#include "tools/time_keeper/time_keeper.hpp"
#include "tools/colors.h"

#include "tracshats/tracshats.hpp"

#include <cstring>
#include <thread>
#include <functional>
#include <condition_variable>
#include <signal.h>

#ifdef USE_FOLDER_READER
   #include "devices/FolderReader/folderreader.h"
#endif // USE_FOLDER_READER

#ifdef USE_VIDEO_READER
   #include "devices/VideoReader/videoreader.h"
#endif //USE_VIDEO_READER

#ifdef USE_WEB_CAMERA
   #include "devices/WebCamera/webcamera.hpp"
#endif //USE_WEB_CAMERA

#ifdef USE_COLIBRI_TV
   #include "devices/colibritv/colibritv.h"
#endif //USE_COLIBRI_TV

#ifdef USE_RASPBERRY_HQ_CAMERA
#include "devices/RaspberryHQCamera/factory.hpp"
#endif // USE_RASPBERRY_HQ_CAMERA

#ifdef USE_IMX219_CAMERA_MIPI
#include "devices/IMX219CameraMIPI/imx219_camera_mipi_factory.hpp"
#endif // USE_IMX219_CAMERA_MIPI

#ifdef USE_IMX477_SQUARE_CAMERA_MIPI
#include "devices/imx477squareCameraMIPI/imx477_square_camera_mipi_factory.hpp"
#endif // USE_IMX477_SQUARE_CAMERA_MIPI

#ifdef USE_SHARED_MEMORY
//   #include "devices/SharedMemory/sharedmemory.hpp"
#include "devices/SharedMemory/shared_memory_factory.hpp"
#endif // USE_SHARED_MEMORY

#ifdef USE_HIKVISION
   #include "devices/EthCameraRtsp/rtsp_h265_device_factory.hpp"
#endif // USE_HIKVISION

#ifdef USE_LOGGER
#include "logger/factory.h"
#endif //USE_LOGGER

#include "tools/watchdog.h"
#include <iomanip>
typedef unsigned char uchar;

class Application : public IFrameHandler // обработка приема фреймов
{
public:
	Application(const std::string &pathToConfig, bool &ok);
	~Application();
	void quit(); // TODO: сделать private, т.к. небезопасен при внешнем вызове
    void stop(); // поднимаем флаг need_quit
	/*
	Вызывает quit только при завершении работы цикла в exec();
	(но с определенным лимитом по времени ожидания watchdog_wait_close_exec_time);
	Возвращает true в случае, если удалось дождаться закрытия exec за
	выделенное лимитированное время. quit() вызывается вне зависимости от успешности операции
	ожидания.
	*/
	bool quit_async();  
	void start();
	void exec();    // основная функция выполнения приложения    

private:
	// перечень устройств-источников видеопотока
	enum Devices
	{
		FOLDER = 0,
		VIDEO = 1,
		WEBCAMERA = 2,
		COLIBRITV = 3,
		RASPBERRY_HQ_CAMERA = 4,
        IMX477_SQUARE_CAMERA_MIPI = 5,
        IMX219_CAMERA_MIPI = 6,
        RTSP_H265 = 7,
        SHARED_MEMORY = 8,
        HVGS_GRAY_USB_CAMERA = 9
    }; // -- END enum Devices

    cv::Mat frame_process_0; // двойная буфферизация

	std::atomic<bool> _execute = false;     // флаг нахождения программы в процессе выполнения
	std::atomic<bool> _exec_complete_success = false; // флаг успешного завершения метода exec(), исполняемого в отдельном потоке 
	std::atomic<bool> _quit_async_complete = false; // флаг окончания выполнения метода quit_async()

	std::atomic<bool> quit_was_called = false; // устанавливается при первом вызове метода quit() данного класса
	std::atomic<bool> _quit_async_was_called = false; // флаг устанавливается при первом вызове метода quit_async();
	
	std::atomic<bool> frameReady = false; // флаг готовности фрейма

	std::mutex frame_proc_0_mutex, frame_proc_1_mutex;
	
    cv::Mat frame_receive, frame_receive0;	
	cv::Mat frame_process_1;

    cv::Mat frame_process_tracshats;    // кадр для обработки трекером
	cv::Mat frame_show;                 // кадр для показа на экране
	
	std::atomic<int> process_frame_id = 0; // номер (0,1) текущего обрабатываемого фрейма в главном цикле программы

	// флаг готовности кадра для обработки трекером

    bool isTracShatsFirstInitedFlag = false;           // флаг инициации трекера
    bool isTracShatsInitedFlag = false;                // флаг инициации трекера
    bool tracShatsInitReqFlag = false;
    cv::Rect2f searchRect;
    cv::Rect2f rectm;

    unsigned char key = 0;
    int cross_on = 0;
    unsigned char cross_on_color = 0;

    // данные для захвата цели мышью
    int get_rect_manual = 1;       // признак разрешения ручного захвата цели
    static bool click_down;
    static bool click_up;
    static cv::Point p_mouse;
    static cv::Point p_down;
    int zahvat_size = 24;
    cv::Point2i wh_2_zahvat = cv::Point(24, 24);
    bool first_click_down = 1;

    cv::Rect rct_center = cv::Rect(500, 600, 500, 500);
    float show2originImgRatio = 1.f;
    float orig2show = 1.f/show2originImgRatio;
    int frame_show_height = 1;    
    int frame_show_width_2, frame_show_height_2;
    float frame_show_w_1, frame_show_h_1;
    float frame_h_w = 1.f;

    cv::Point2i wh_2_ext[256];

    // данные для работы в режиме ROI         
	int roi_mode = 0;				// признак работы в режиме ROI
    bool isRoiSetted = false;           // признак установки ROI
    int scaleROI = 5;                   // масштаб ROI относительно размера цели
    int scale = 0;
    cv::Scalar clr_scaling = color::green;
    cv::Rect2f roi = cv::Rect2f(0,0,0,0);       // текущий ROI
    cv::Rect2f aimRectShats = cv::Rect2f(0,0,0,0); // текущая рамка цели

    // results demonstration
    int frame_show_width = 640;         // ширина отображаемого кадра
    int demonstration_mode = 0;         // признак режима показа

	// устройство считвания кадров
	std::shared_ptr<Device> device = nullptr;				// источник видеопотока

    std::shared_ptr<TracShats> tracShats = nullptr;  // трекер

	int device_id = 0; // в соответствии с enum Devices

	std::string config_path;

	bool parallel = 0;
	bool need_quit = false;		// флаг запроса на выход из приложения, устанавливается методами 
	
 #ifdef GUI_OK
	std::string app_win_name = "Application";
 #endif // GUI_OK

	// Временные точки для нахождения времени обработки кадра.
	std::chrono::system_clock::time_point 
		time_point_tracker0, time_point_tracker1,
		time_point_device0, time_point_device1;
	// обработка изображения (трекинг)
	inline bool processShats();
	// рабочий цикл трекеров
	inline void workflowShats();


	#ifdef GUI_OK
	// колл-бэк метод обработки событий мыши
	static void aimFrameCallback(int event, int x, int y, int flags, void* param);
	#endif // GUI_OK
	
	#ifdef GUI_OK
	// обработчик событий мыши (основной регулярный цикл)
    bool mouseHandler(cv::Mat& img, cv::Rect2f& object_rect);
	#endif // GUI_OK
	
 #ifdef GUI_OK
	// обработчик событий клавиатуры
    void keyHandler();
 #endif //GUI_OK

    // загрузка рамки цели из файла
    bool loadRectFromFile(std::string);
	// подготовка изображения для tracShats
    inline void prepareFrameForTracShats();	
	bool get_ini_params(const std::string& config);
	// обработчик события поступления кадра при приёме от устройства
	void handleDeviceFrame(uint8_t * f, int w, int h, int num, int id);	
	bool FileIsExist(const std::string& filePath);
    void work_TKDNN();
}; // -- END class Application
#endif // APPLICATION_H
