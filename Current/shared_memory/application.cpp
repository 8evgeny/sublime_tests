#include "application.hpp"

using namespace std;
using namespace cv;
using namespace chrono;

bool Application::click_down = 0;
bool Application::click_up = 0;
Point Application::p_mouse(0, 0);
Point Application::p_down(0, 0);

Application::~Application(){cout << "Деструктор Application" << endl;}

Application::Application(const string & pathToConfig,
                         bool &ok) : config_path(pathToConfig)
{
    cout << "config_path=" << config_path << endl;
    ok = get_ini_params(config_path);
    if(!ok){cout << "Not ok get_ini_params!" << endl; return;}

    #ifdef USE_LOGGER
        bool create_logger_status; 
        logger_artem::create(config_path, create_logger_status);
        if(!create_logger_status)
        {
            ok = false;
            quit();
            return;
        }
    #endif //USE_LOGGER

    switch(device_id)
    {
#ifdef USE_FOLDER_READER
    case FOLDER:
        device = make_shared<FolderReader>(config_path, ok);
        cout << "make_shared<FolderReader> OK=" << ok << endl;
        if(!ok){cout << "Not ok FolderReader!" << endl; return;}
        break;
#endif // END USE_FOLDER_READER
#ifdef USE_COLIBRI_TV
    case COLIBRITV:
        device = make_shared<ColibriTV>(config_path, ok);
        if(!ok){cout << "Not ok ColibriTV!" << endl; return;}
        device->setup();
        break;
#endif // END USE_COLIBRI_TV
#ifdef USE_VIDEO_READER
    case VIDEO:
        device = make_shared<VideoReader>(config_path, ok);
        if(!ok){return;}
        break;
#endif
#ifdef USE_WEB_CAMERA
    case WEBCAMERA:
        device = make_shared<WebCamera>(config_path, ok);
        if(!ok){return;}
        break;
#endif // END USE_WEB_CAMERA
#ifdef USE_SHARED_MEMORY
    case SHARED_MEMORY:
        device = devices::shared_memory::create(config_path);
        device->setup();
        break;
#endif // END USE_SHARED_MEMORY
#ifdef USE_RASPBERRY_HQ_CAMERA
    case RASPBERRY_HQ_CAMERA:
        device = devices::raspberry_hq_camera::create(config_path);
        device->setup();
        break;
#endif // END USE_RASPBERRY_HQ_CAMERA
#ifdef USE_IMX219_CAMERA_MIPI
    case IMX219_CAMERA_MIPI:
        device = devices::imx219_camera_mipi::create(config_path);
        device->setup();
        break;
#endif // END USE_IMX219_CAMERA_MIPI
#ifdef USE_IMX477_SQUARE_CAMERA_MIPI
    case IMX477_SQUARE_CAMERA_MIPI:
        device = devices::imx477_square_camera_mipi::create(config_path);
        device->setup();
        break;
#endif

#ifdef USE_HIKVISION
    case RTSP_H265:
        device = devices::rtsp_h265_device::create(config_path, "rtsp_h265_device");
        device->setup();
        break;

#endif // USE_HIKVISION
    default:
        break;
    } // -- END switch

    if(device != nullptr)
    {
        if(!parallel && !(device_id == FOLDER || device_id == VIDEO))
        {
            parallel = true;
        }
        if(parallel)
        {
            device->register_frame_handler(this);
            register_frame_handler(bind(&Application::handleDeviceFrame, this,
                                        placeholders::_1, placeholders::_2,
                                        placeholders::_3, placeholders::_4,
                                        placeholders::_5));
        } // -- END if(parallel)
    }
    else
    {
        #ifdef USE_LOGGER
            LoggerArtem::inst().log("Device doesn't exist: choose correct device in configuration file or rebuild application with current device");
        #endif //USE_LOGGER
        quit();
    } // END if(device == nullptr)
    for(int key = 0; key < 256; key++){wh_2_ext[key] = Point(0, 0);}
    wh_2_ext['z'] = Point(-1, -1);
    wh_2_ext['x'] = Point(1, 1);
    wh_2_ext['4'] = Point(-1, 0);
    wh_2_ext['7'] = Point(-1, 1);
    wh_2_ext['8'] = Point(0, 1);
    wh_2_ext['9'] = Point(1, 1);
    wh_2_ext['6'] = Point(1, 0);
    wh_2_ext['3'] = Point(-1, 1);
    wh_2_ext['2'] = Point(0, -1);
    wh_2_ext['1'] = Point(-1, -1);
 #ifdef GUI_OK
    namedWindow(app_win_name, WINDOW_NORMAL);
 #endif //GUI_OK
} // -- END Application

bool Application::FileIsExist(const string& filePath)
{
    bool isExist = false;
    ifstream fin(filePath.c_str());
    if(fin.is_open()){isExist = true;}
    fin.close();
    return isExist;
} // -- END FileIsExist

void Application::quit()
{
    if(quit_was_called.load())
    {
        return;
    }
    quit_was_called.store(true);

    _execute.store(false, memory_order_release);
        
    cout << " --- BEGIN Application::quit" << endl;
    #ifdef USE_LOGGER
        cout << "\t --- BEGIN logger::quit()" << endl;
        bool logger_quit_report = LoggerArtem::inst().quit();
        if(logger_quit_report)
        {
            cout << "\tlogger quit success" << endl;
        }
        else
        {
            cout << "\t logger quit failed" << endl;
        }
        cout << " \t --- END logger::quit()" << endl;
    #endif //USE_LOGGER

    if(device != nullptr)
    {
        cout << "\t --- BEGIN device->quit()" << endl;
        if(device != nullptr)
        {
            device->quit();
        }
        cout << "\t --- END device->quit()" << endl;
    }
#ifdef GUI_OK
    destroyAllWindows();
#endif
    cout << " --- END Application::quit" << endl;
} // -- END quit

void Application::stop()
{
    cout << "Application::stop()\n";
    need_quit = true;
}  // -- END stop()

bool Application::quit_async()
{
    /*
        Проверка на предмет раннего вызова метода quit() или quit_async();
        Для гарантии безопасного выхода требуется
        обеспечить возможность только единократного вызова quit() или quit_async()
    */
    if(_quit_async_was_called.load() || quit_was_called.load()){return true;}

    _quit_async_was_called.store(true);
    cout << "BEGIN quit_async()" << endl;
    _execute.store(false);
    // Максимально допустимое время ожидания закрытия основного цикла приложения
    // При превышении приложение закрывается не дожидаясь закрытия потока функции exec()ж
    const int watchdog_close_exec_time_ms = 3000;  
    // Общее количество отсчетов, которое выполняется
    const int subdivisions_total = 100;
    // Временной интервал проверки состояния потока метода exec() за предмет завершенности (закрытости)
    int check_interval_ms = 1; 
    
    // Проверки безопасности введенных пользовательских значений watchdog_close_exec_time_ms и subdivisions_total
    if(subdivisions_total > 0){check_interval_ms = watchdog_close_exec_time_ms / subdivisions_total;}
    if(check_interval_ms <= 0){check_interval_ms = 1;}

    cout << "\t watchdog_close_exec_time_ms = " << watchdog_close_exec_time_ms << endl;
    cout << "\t subdivisions_total = " << subdivisions_total << endl;
    cout << "\t check_interval_ms = " << check_interval_ms << endl;
    bool success_close_exec = false;
    for(int i = 0; i < subdivisions_total; ++i)
    {
        if(_exec_complete_success.load())
        {
            cout << "\tSuccess close exec(), total wait time = " << i * check_interval_ms << " (ms)" << endl;
            success_close_exec = true;
            break;
        }
        this_thread::sleep_for(milliseconds(check_interval_ms));
    } // END for(int i = 0; i < subdivisions_total; ++i)

    if(!success_close_exec){cout << "Error close exec()!" << endl;}
    quit();
    _quit_async_complete.store(true);
    cout << "END quit_async()" << endl;
    return success_close_exec;
} // -- END quit_async

void Application::start()
{
    device->start();
    _execute.store(true, memory_order_release);
    exec();    
} // -- END start


void Application::work_TKDNN()
{
    bool flag = tracShats->update(frame_process_tracshats, aimRectShats);
    tracShats->getSearchRect(searchRect);
 #if defined(GUI_OK)
//    Rect2f searchRect_show(frame_show_width * searchRect.x, frame_show_height * searchRect.y,
//                           frame_show_width * searchRect.width, frame_show_height * searchRect.height);
//    rectangle(frame_show, searchRect_show, color::white, 1);
    if(tracShats->find_)
    {
       int num = 0;
       for(vector<trac_data>::iterator trac = tracShats->trac_str.vtrac_data.begin(); trac != tracShats->trac_str.vtrac_data.end(); trac++)
       {
          // приведение рамки цели к абсолютным координатам
          Point lt(trac->x * frame_show_width - trac->w * frame_show_width, trac->y * frame_show_height - trac->h * frame_show_height);
          Point br(trac->x * frame_show_width + trac->w * frame_show_width, trac->y * frame_show_height + trac->h * frame_show_height);
          Rect rectShats(lt, br);
          // отрисовка рамки цели
          rectangle(frame_show, rectShats, color::white, 2);
          // отрисовка центра объекта
          Point2f center_show = 0.5*(lt + br);
          circle(frame_show, center_show, 2, color::white, -1);
          putText(frame_show, to_string(num), br, FONT_HERSHEY_SIMPLEX, 0.7, color::white, 2);
          num++;
       } // END for(vector<trac_data>::iterator trac = vtrac->begin(); trac != vtrac->end(); trac++)
    } // END if(tracShats->find_)
 #endif // END #if defined(GUI_OK)
} // END work_TKDNN()


void Application::exec()
{
    bool ok = false;
    cout << "Application::exec START" << endl;
    if(parallel)
    {
        while(!frameReady.load())
        {
            this_thread::sleep_for(milliseconds(1));
        }
    } // END if(parallel)
    else
    {
        if(!device->getFirstFrame(frame_process_0)){quit();}
        frameReady.store(true);
    } // END if(!parallel)

    int frame_w = frame_process_0.cols;
    int frame_h = frame_process_0.rows;
    cout << "exec:: frame size : frame_w = " << frame_w << "; frame_h = " << frame_h << endl;
    tracShats = make_shared<TracShats>(config_path, frame_process_0, ok);
    if(!ok)
    {
        quit();
        return;
    }
    show2originImgRatio = (float)frame_show_width / frame_w;
    orig2show = 1.f / show2originImgRatio;
    zahvat_size = round(zahvat_size * show2originImgRatio);
    wh_2_zahvat = Point2i(zahvat_size, zahvat_size);

    frame_h_w = (float)frame_h/frame_w;
    frame_show_height = round(frame_h_w * frame_show_width);
    frame_show_width_2 = 0.5 * frame_show_width;
    frame_show_height_2 = 0.5 * frame_show_height;
    frame_show_w_1 = 1.f / frame_show_width;
    frame_show_h_1 = 1.f / frame_show_height;
    rct_center.height = round(frame_h_w*rct_center.width);    
 #if defined(TKDNN)
    isTracShatsFirstInitedFlag = true;
    isTracShatsInitedFlag = true;
    tracShats->trac_str.new_frame = 1;
 #endif // END #if defined(TKDNN)    

    // основной цикл выполнения пиложения
    while(_execute.load(memory_order_acquire))
    {
        if(!parallel)
        {
  #ifdef USE_LOGGER
            time_point_device0 = high_resolution_clock::now();
  #endif // END USE_LOGGER

  #ifdef USE_ROI_TMP
            device->getFrame(frame_receive0);
            resize(frame_receive0(rct_center), frame_receive, Size(frame_w, frame_h));
  #endif // END USE_ROI_TMP
  #ifndef USE_ROI_TMP
            device->getFrame(frame_receive);
  #endif // END NOT USE_ROI_TMP

  #ifdef USE_LOGGER
            time_point_device1 = high_resolution_clock::now();
            LoggerArtem::inst().logTimedBasedFPS(
                "Device FPS = ",
                duration<double>(time_point_device1 - time_point_device0).count());
  #endif // END USE_LOGGER
            frameReady.store(true);
        } // END if(!parallel)

        if(frameReady.load())
        {
            if(parallel) // TODO: паттерн "стратегия" с назначением lambda
            {
                /*
                Обособленный mutex'ом фрагмент не осуществляет клонирования frame, 
                реализуется оптимальная передача по ссылке, 
                но дополнительная потокобезопасность обеспечивается 
                frame_proc_(0/1)_mutex без существенных накладных расходов
                */
                switch(process_frame_id) // id буффера на предыдущем шаге
                {
                    case 0:
                    {
                        frame_proc_1_mutex.lock();
                        process_frame_id = 1;
                        frame_receive = frame_process_1;
                        frame_proc_1_mutex.unlock();
                    }
                    break;

                    case 1:
                    {
                        frame_proc_0_mutex.lock();
                        process_frame_id = 0;
                        frame_receive = frame_process_0;
                        frame_proc_0_mutex.unlock();
                    }
                    break;

                    default:
                    {
                        throw runtime_error("Error: incorrect process_frame_id");
                    }
                    break;
                }
            } // -- END if(parallel)

            frameReady.store(false);
            prepareFrameForTracShats();

   #ifdef GUI_OK
            resize(frame_receive, frame_show, Size(frame_show_width, frame_receive.rows * show2originImgRatio));
            if(cross_on)
            {
                line(frame_show, Point(0, frame_show_height_2), Point(frame_show_width, frame_show_height_2), cross_on_color, 2);
                line(frame_show, Point(frame_show_width_2, 0), Point(frame_show_width_2, frame_show_height), cross_on_color, 2);
            } // END cross_on
   #endif //GUI_OK

   #ifdef USE_LOGGER
            time_point_tracker0 = system_clock::now();
   #endif // END USE_LOGGER

 #if !defined(TKDNN)
           workflowShats();
 #endif // END #if !defined(TKDNN)  
 #if defined(TKDNN)
           work_TKDNN();
 #endif // END #if defined(TKDNN)

   #ifdef USE_LOGGER
           time_point_tracker1 = system_clock::now();
           if(tracShats->isInited())
           {
               LoggerArtem::inst().logTimedBasedFPS("TrackShats FPS = ",
                           duration<double>(time_point_tracker1 - time_point_tracker0).count());

               #if defined(TKDNN)
                  LoggerArtem::inst().logTimedBasedFPS("Scan FPS = ", tracShats->trac_str.scan_exec_time);
                  LoggerArtem::inst().logTimedBasedFPS("YOLO FPS = ", tracShats->trac_str.yolo_exec_time);
               #endif // END #if defined(TKDNN)
           } // END if(tracShats->isInited())
   #endif // USE_LOGGER

   #if defined(GUI_OK)
            if(tracShats->trac_str.work_in_round)
            {
               circle(frame_show, Point(frame_show_width_2, frame_show_height_2), frame_show_height_2, color::white, 1);
            } // END if(tracShats->trac_str.work_in_round)
            if(mouseHandler(frame_show, rectm))
            {
                // инициализация трекера, если указана новая рамка цели
                rectm = Rect2f(rectm.x * frame_show_w_1, rectm.y * frame_show_h_1,
                                rectm.width * frame_show_w_1, rectm.height * frame_show_h_1);
                bool initFlag = false;
                if(!tracShats->isInited())
                {
                    if(roi_mode)
                    {
                        initFlag = tracShats->init(rectm, roi);
                        tracShats->setWorkNumber(device->getFrameCounter());
                        if(initFlag)
                        {
                            isRoiSetted = true;
                        }
                    }
                    else
                    {
                        initFlag = tracShats->init(rectm);
                        tracShats->setWorkNumber(device->getFrameCounter());
                    }
                    if(initFlag)
                    {
                        if(!isTracShatsFirstInitedFlag){isTracShatsFirstInitedFlag = true;}
                        isTracShatsInitedFlag = true;
                    } // -- END if(initFlag)
                } // -- END if(!tracShats->isInited())
            } // -- END if(mouseHandler(frame_show, rect))
            if(need_quit)
            {
                cout << "need quit" << endl;
                quit();
                break;
            } // END if(need_quit)
   #endif // END #if defined(GUI_OK)
        } // END if(frameReady.load())
        else
        {
            bool ws_ok1 = false;
            bool need_brake_quit = false;
            tracShats->trac_str.new_frame = 0;        
            while(!frameReady.load())
            {
                if(parallel)
                {
                    #if !defined(TKDNN)
                     this_thread::sleep_for(milliseconds(5));
                    #endif // END #if !defined(TKDNN)
                    #if defined(TKDNN)
                     work_TKDNN();
                    #endif // END #if defined(TKDNN)
                } // -- END if(!parallel)
                else
                {                    
                   break;
                } // END if(!parallel)
            } // -- END while(!frameReady.load())
            tracShats->trac_str.new_frame = 1;
        } // -- END if(!frameReady.load())
    } // -- END while(_execute.load(memory_order_acquire))

    cout << "Complete Application::exec()" << endl;
    _exec_complete_success.store(true);
    this_thread::sleep_for(milliseconds(10));
    bool success_wait_quit_async_complete = false; // флаг успешного завершения работы метода quit_async()
    if(_quit_async_was_called.load())
    {
        for(int i = 0; i < 100; ++i)
        {
            if(_quit_async_complete.load())
            {
                success_wait_quit_async_complete = true;
                cout << "_quit_async_complete detected <<true>>" << endl;
                this_thread::sleep_for(milliseconds(20));
                break;
            } // if(_quit_async_complete.load())
        } // END for(int i = 0; i < 100; ++i)
    } // END if(_quit_async_complete.load())
    cout << "END exec" << endl;
} // -- END exec

bool Application::get_ini_params(const string &config)
{
    cout << "BEGIN get_ini_params Application" << endl;
    setlocale(LC_NUMERIC, "en_US.UTF-8");

#ifdef USE_FILESYSTEM
    bool configFileExists = filesystem::exists(config);
#else
    bool configFileExists = FileIsExist(config);
#endif
    if(!configFileExists)
    {
        cout << "Config file '" << config << "' not exist!" << endl;
        return 0;
    }
    INIReader reader(config);
    if(reader.ParseError() < 0)
    {
        cout << "Can't load '" << config << "'\n";
        return 0;
    }

    parallel = reader.GetInteger("main_settings", "parallel", -1);
    if(parallel == -1)
    {
        cout << "parallel not declared!!" << endl;
        return 0;
    }
    cout << "parallel = " << parallel << ";\n";

    device_id = reader.GetInteger("main_settings", "device_id", -1);
    if(device_id == -1)
    {
        cout << "device_id not declared!\n";
        return 0;
    }
    cout << "device_id = " << device_id << ";\n";

    get_rect_manual = reader.GetInteger("main_settings", "get_rect_manual", -1);
    if(get_rect_manual == -1)
    {
        cout << "Not found get_rect_manual in Application::getMainSettings!\n";
        return false;
    }

    roi_mode = reader.GetInteger("main_settings", "roi_mode", -1);
    if(roi_mode == -1)
    {
        cout << "Not found roi_mode in Application::getMainSettings!\n";
        return false;
    }

    scale = reader.GetInteger("tracking", "scaling", -1);
    if(scale == -1)
    {
        cout << "Not found scaling in Application::getMainSettings!\n";
        return false;
    }
    if(scale == 1){clr_scaling = color::blue;}
    if(scale == 2){clr_scaling = color::red;}

    zahvat_size = reader.GetInteger("tracking", "zahvat_size", -1);
    if(zahvat_size == -1)
    {
        cout << "Not found zahvat_size in Application::getMainSettings!\n";
        return false;
    }
    wh_2_zahvat = Point2i(zahvat_size, zahvat_size);

    frame_show_width = reader.GetInteger("demonstration_settings", "frame_show_width", -1);
    if(frame_show_width == -1)
    {
        cout << "Not found width in Application::getMainSettings!\n";
        return false;
    }

    demonstration_mode = reader.GetInteger("demonstration_settings", "demonstration_mode", -1);
    if(demonstration_mode == -1)
    {
        cout << "Not found mode in Application::getMainSettings!\n";
        return false;
    }

    cross_on = reader.GetInteger("copter1", "cross_on", -1);
    if(cross_on == -1)
    {
        cout << "Not found cross_on in Application::getMainSettings!\n";
        return false;
    }

    cross_on_color = reader.GetInteger("copter1", "cross_on_color", -1);
    if(cross_on_color == -1)
    {
        cout << "Not found cross_on_color in Application::getMainSettings!\n";
        return false;
    }

    if(!get_rect_manual && device_id == FOLDER)
    {
        string way2init_rect = reader.Get("folder", "way2init_rect", "oops");
        if(way2init_rect == "oops")
        {
            cout << "Not found way2init_rect in Application::getMainSettings!\n";
            return 0;
        } // END if(way2init_rect == "oops")
        else
        {
            loadRectFromFile(way2init_rect);
        } // END if(way2init_rect != "oops")
    }  // -- END if(!get_rect_manual and device_id == FOLDER)

    cout << "END get_ini_params Application" << endl;
    return 1;
} // -- END get_ini_params

bool Application::processShats()
{
    // обновление рамки цели по текущему кадру
    bool flag = tracShats->update(frame_process_tracshats, aimRectShats);
    //cout << "processShats " << flag << endl;
    if(flag)
    {
        if(tracShats->roi){roi = tracShats->getROI();}
        return true;
    } // -- END if(flag)
    return false;
} // -- END processShats

void Application::workflowShats()
{    
    //cout << "isTracShatsFirstInitedFlag=" << isTracShatsFirstInitedFlag << endl;
    if(isTracShatsFirstInitedFlag)
    {
 #ifdef GUI_OK
        if(demonstration_mode > 2 && tracShats->isInited())
        {
 #ifdef USE_CUDA
          frame_show(Rect(Point(80, 90) - Point(7, 7), Point(80, 90) + Point(7, 7))) = color::black;
          frame_show(Rect(Point(80, 90) - Point(3, 3), Point(80, 90) + Point(3, 3))) = color::white;
 #endif // END ifdef USE_CUDA
 #ifndef USE_CUDA
          circle(frame_show, Point(80, 90), 14, color::black, -1);
          circle(frame_show, Point(80, 90), 6, color::white, -1);
 #endif // END ifndef USE_CUDA
        } // -- END if(demonstration_mode > 2 && tracShats->isInited()) 
 #endif // END GUI_OK
        
        bool flag = processShats();// обработка кадра

        //cout << "processShats flag=" << flag << endl;
        if(flag)
        {              
 #ifdef GUI_OK
            if(tracShats->find_)
            {
                // приведение рамки цели к абсолютным координатам
                Rect2f rectShats(aimRectShats.x * frame_show_width, aimRectShats.y * frame_show_height,
                                 aimRectShats.width * frame_show_width, aimRectShats.height * frame_show_height);
                // отрисовка рамки цели
                rectangle(frame_show, rectShats, color::white, 1);
                // отрисовка центра объекта
                Point2f center = tracShats->getTargetCenter();
                center = Point2f(center.x * frame_show_width, center.y * frame_show_height);
                circle(frame_show, center, 2, color::white, -1);
            } // END if(tracShats->find_)

            // добавление метки размера объекта на кадр
            if(demonstration_mode > 1)
            {
                tracShats->getSearchRect(searchRect);
                searchRect = Rect2f(searchRect.x * frame_show_width, searchRect.y * frame_show_height,
                                    searchRect.width * frame_show_width, searchRect.height * frame_show_height);
                rectangle(frame_show, searchRect, color::white, 1);
                if(demonstration_mode > 3)
                {
                    Point objSize(round(aimRectShats.width * frame_receive.cols),
                                  round(aimRectShats.height * frame_receive.rows));
                    string txt = "Object size=[" + to_string(objSize.x) + ", " + to_string(objSize.y) + "]";
                    putText(frame_show, txt, Point(100, 100), FONT_ITALIC, 1, color::Green::lime, 2);
                } // -- END if(demonstration_mode > 3)
            } // -- END if(demonstration_mode > 1)
 #endif // END GUI_OK
        } // END if(flag)
        else
        {
            if(!tracShats->isInited()){isTracShatsInitedFlag = false;} 
        } // END if(!flag)
    } // -- END if(isTracShatsFirstInitedFlag)
    else if(tracShatsInitReqFlag)
    {      // инициализация трекера при поступлении запроса
        tracShatsInitReqFlag = false;
        cout << "Init tracker" << endl;
        if(!tracShats->isInited())
        {
            bool initFlag = false;
            if(roi_mode)
            {
                initFlag = tracShats->init(aimRectShats, roi);
                tracShats->setWorkNumber(device->getFrameCounter());
                if(initFlag){isRoiSetted = true;}
            } // END if(roi_mode)
            else
            {
                initFlag = tracShats->init(aimRectShats);
                tracShats->setWorkNumber(device->getFrameCounter());
            } // END if(!roi_mode)
            if(initFlag)
            {
                if(!isTracShatsFirstInitedFlag){isTracShatsFirstInitedFlag = true;}
                isTracShatsInitedFlag = true;
            } // -- END if(initFlag)
            // подготовка нового кадра (т.к. для неинициализированного трекера кадр для обработки не подготовлен)
            prepareFrameForTracShats();
            // обработка кадра "на месте" для корректной инициализации трекера
            workflowShats();
        } // -- END if(!tracShats->isInited())
    } // -- END else if(tracShatsInitReqFlag)
} // -- END workflowShats


#ifdef GUI_OK
void Application::aimFrameCallback(int event, int x, int y, int flags, void *param)
{
    Point *p = reinterpret_cast<Point*>(param);
    p->x = x;
    p->y = y;
    p_mouse = Point(x, y);
    switch(event)
    {
       case EVENT_LBUTTONDOWN:
           click_down = 1;
           break;
       case EVENT_LBUTTONUP:
           if(click_down){click_up = 1;}
           break;
    } // -- END switch(event)
} // -- END aimFrameCallback
#endif // END GUI_OK

#ifdef GUI_OK
bool Application::mouseHandler(Mat& img, Rect2f& object_rect)
{    
 #if !defined(TKDNN)
    if(!isTracShatsInitedFlag)
    {
        if(click_down)
        {
            if(zahvat_size)
            {
               if(first_click_down)
               {
                   first_click_down = 0;
                   p_down = p_mouse;
               } // -- END if(first_click_down)
               Rect rct(p_mouse - wh_2_zahvat, p_mouse + wh_2_zahvat);
               rectangle(img, rct, color::white, 1);
            }
            else
            {
                if(first_click_down)
                {
                    first_click_down = 0;
                    p_down = p_mouse;
                } // -- END if(first_click_down)
                int left  = MIN(p_mouse.x, p_down.x);
                int right = MAX(p_mouse.x, p_down.x);
                int top   = MIN(p_mouse.y, p_down.y);
                int down  = MAX(p_mouse.y, p_down.y);
                Rect rct(Point(left, top), Point(right, down));
                rectangle(img, rct, color::white, 1);
            } // END if(!zahvat_size)
        } //--END if(click_down)
    } // -- END if(!isTracShatsInitedFlag)
 #endif // END #if !defined(TKDNN)

    imshow(app_win_name, img);
    //moveWindow(win_name, 10, 10);
    key = waitKey(1);
    keyHandler();
    device->keyHandler(key);
    if(key == '`'){need_quit = 1; return 0;}

 #if !defined(TKDNN)
    wh_2_zahvat += wh_2_ext[key];
    if(!isTracShatsInitedFlag)
    {
        setMouseCallback(app_win_name, aimFrameCallback, &p_mouse);
        if(click_up)
        {
            if(zahvat_size)
            {
                click_up = 0;
                click_down = 0;
                first_click_down = 1;
                object_rect = Rect(p_mouse - wh_2_zahvat, p_mouse + wh_2_zahvat);
                return true;
            }
            else
            {
               click_up = 0;
               int left  = MIN(p_mouse.x, p_down.x);
               int right = MAX(p_mouse.x, p_down.x);
               int top   = MIN(p_mouse.y, p_down.y);
               int down  = MAX(p_mouse.y, p_down.y);
               Rect rct(Point(left, top), Point(right, down));
               if(rct.area() > 0)
               {
                   click_down = 0;
                   first_click_down = 1;
                   object_rect = rct;
                   return true;
               } // -- END if(rct.area()>0)
            } // END if(!zahvat_size)
        } //--END if(click_up)
    } // -- END if(!isTracShatsInitedFlag)
 #endif // END  #if !defined(TKDNN)
  return false;
} // -- END mouseHandler
#endif // GUI_OK

#ifdef GUI_OK
void Application::keyHandler()
{
    switch(key)
    {
#if !defined(TKDNN)
       case 27: // деинциализация трекера по клавише ESC
           if(tracShats->isInited())
           {
               tracShats->deinit();
           }
           break;
#endif // END !defined(TKDNN)
       case '`':       // выход из программы по клавише '`'.
           cout << "Exit on keypress" << endl;
           break;
       default:
           break;
    }  // -- END switch(key)
} // -- END keyHandler
#endif // END GUI_OK


bool Application::loadRectFromFile(string path)
{
    ifstream f_in(path);
    if(!f_in.is_open())
    {
        cout << "File " << path << " NOT open!" << endl;
        return false;
    } // -- END if(!f_in.is_open())
    string item0, item1, item2, item3, item4, item5;
    f_in >> item0; // Безразмерная x-координата центра объекта в единицах ширины фрейма,
    f_in >> item1; // Безразмерная y-координата центра объекта в единицах высоты фрейма,
    f_in >> item2; // Безразмерная полуширина прямоугольника цели в единицах ширины фрейма,
    f_in >> item3; // Безразмерная полувысота прямоугольника цели в единицах высоты фрейма,
    f_in >> item4; // Номер первого фрейма,
    f_in >> item5; // Номер последнего фрейма.
    f_in.close();
    float obj_wh_2_w = stof(item2);
    float obj_wh_2_h = stof(item3);
    float obj_xy_x = stof(item0);
    float obj_xy_y = stof(item1);
    aimRectShats.x = obj_xy_x - obj_wh_2_w;
    aimRectShats.y = obj_xy_y - obj_wh_2_h;
    aimRectShats.width = obj_wh_2_w * 2;
    aimRectShats.height = obj_wh_2_h * 2;
    tracShatsInitReqFlag = true;
    return true;
} // -- END loadRectFromFile

// подготовка изображения для tracShats
void Application::prepareFrameForTracShats()
{
    if(roi_mode and isRoiSetted)
    {
        // расчет абсолютных координат ROI
        Rect realSizedROI(roi.x * frame_receive.cols, roi.y * frame_receive.rows,
                              roi.width * frame_receive.cols, roi.height * frame_receive.rows);
        frame_process_tracshats = frame_receive(realSizedROI).clone();
        //                        // отрисовка ROI
        //                        rectangle(frame_color, realSizedROI, color::blue, 2);
        // imwrite("../test_data/img1.png", frame_process_tracshats);
    }
    else
    {
        frame_process_tracshats = frame_receive; //.clone();
    } // END if(!(roi_mode and isRoiSetted))
} // -- END prepareFrameForTracShats

void Application::handleDeviceFrame(uint8_t *f, int w, int h, int num, int id)
{
    static auto prevFrameReceiveTime = high_resolution_clock::now();
    auto receiveTime = high_resolution_clock::now();

    #ifdef USE_LOGGER
        LoggerArtem::inst().logTimedBasedFPS(
                    "Device FPS = ",
                    duration<double>(receiveTime - prevFrameReceiveTime).count());
    #endif //USE_LOGGER

    prevFrameReceiveTime = receiveTime;
    
    static bool first_frame = true;

    if(first_frame)
    {
#if defined(CCM_8UC1)
        int cvmat_type = CV_8UC1;
#elif defined(CCM_8UC3)
        int cvmat_type = CV_8UC3;
#else
        throw runtime_error("Error: not recognize/supported color channel mode");
#endif
        frame_proc_0_mutex.lock();
        frame_process_0 = Mat(Size(w,h), cvmat_type);
        device->getFormatedImage(f, w, h, id, frame_process_0);        
        frame_proc_0_mutex.unlock();

        frame_proc_1_mutex.lock();
        frame_process_1 = frame_process_0.clone();
        frame_proc_1_mutex.unlock();

        first_frame = false;
        frameReady.store(true);
    }
    else if(!frameReady.load()) // -- END if(first_frame)
    {
        switch(process_frame_id) // двойная буфферизация 
        {
            case 0:
                frame_proc_1_mutex.lock();
                device->getFormatedImage(f, w, h, id, frame_process_1); 
                frame_proc_1_mutex.unlock();
            break;

            case 1:
                frame_proc_0_mutex.lock();
                device->getFormatedImage(f, w, h, id, frame_process_0);
                frame_proc_0_mutex.unlock();
            break;

            default:
                throw runtime_error("Error: incorrect process_frame_id");
            break;
        } // END switch(process_frame_id)
        frameReady.store(true);
    } // -- END if(!frameReady.load())
} // -- END handleDeviceFrame
