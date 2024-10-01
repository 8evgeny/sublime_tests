#include "application.hpp"


#ifdef GUI_OK
void Application::aimFrameCallback(int event, int x, int y, int flags, void *param)
{
    cv::Point *p = reinterpret_cast<cv::Point*>(param);
    p->x = x;
    p->y = y;
    p_mouse = cv::Point(x, y);
    switch(event)
    {
    case cv::EVENT_LBUTTONDOWN:
        click_down = 1;
        break;
    case cv::EVENT_LBUTTONUP:
        if(click_down){click_up = 1;}
        break;
    } // -- END switch(event)
} // -- END aimFrameCallback

#endif // GUI_OK

/// [callback] FENIX 2
#ifdef USE_ETH_CONTROLLER
bool Application::ethHandler(Rect2f & rct)
{
    //    cout << "dbg:: [" << device->getId() << "]: need_reinit = " << need_reinit << endl;
    if(need_reinit)
    {
        if(tracShats->isInited())
        {
            need_reinit = 0;
        } // END if(tracShats->isInited())
        else
        {
            initTracShats(rct_reinit);
        } // END else
    } // END if(need_reinit)

    bool ok;
    fenix2cmd_keeper_ptr->get(fenix2cmd_keep_data, ok);
    //    if(fenix2cmd_keep_data != fenix2cmd_zero_data && ok)
#ifdef USE_DBG
    {
        cout << "----------------\nfenix2cmd_keep_data:\n"
             << "track_init_posx= "<< (float)fenix2cmd_keep_data.track_init_posx << "\n" // положение трека по x, pix
             << "track_init_posy= "<< (float)fenix2cmd_keep_data.track_init_posy << "\n" // положение трека по у, pix
             << "mouse_pos_x= "<< (float)fenix2cmd_keep_data.mouse_pos_x << "\n" // положение трека по x, pix
             << "mouse_pos_y= "<< (float)fenix2cmd_keep_data.mouse_pos_y << "\n" // положение трека по у, pix
             << "quit_server    = "<< (int)fenix2cmd_keep_data.quit_server     << "\n" // команда завершения работы сервера
             << "track_size_up  = "<< (int)fenix2cmd_keep_data.track_size_up   << "\n" // команда увеличения рамки трека
             << "track_size_down= "<< (int)fenix2cmd_keep_data.track_size_down << "\n" // команда уменьшения рамки трека
             << "init_track     = "<< (int)fenix2cmd_keep_data.init_track      << "\n" // команда инициализации трека
             << "deinit_track   = "<< (int)fenix2cmd_keep_data.deinit_track    << "\n" // команда деинициализации трека
             << "poweroff_srv   = "<< (int)fenix2cmd_keep_data.poweroff_srv    << "\n" // команда отключения питания на сервере
             << "reinit         = "<< (int)fenix2cmd_keep_data.reinit          << "\n" // команда отключения питания на сервере
             << "work_mode         = "<< (int)fenix2cmd_keep_data.work_mode          << "\n" // команда отключения питания на сервере
             << "=============================\n\n" << endl;
    }
#endif // USE_DBG
    bool need_init = false;
#ifdef USE_DBG
    if(fenix2cmd_keep_data != fenix2cmd_zero_data)
    {
        cout << "----------------\nfenix2cmd_keep_data:\n"
             << "quit_server    = "<< (int)fenix2cmd_keep_data.quit_server     << "\n" // команда завершения работы сервера
             << "track_size_up  = "<< (int)fenix2cmd_keep_data.track_size_up   << "\n" // команда увеличения рамки трека
             << "track_size_down= "<< (int)fenix2cmd_keep_data.track_size_down << "\n" // команда уменьшения рамки трека
             << "init_track     = "<< (int)fenix2cmd_keep_data.init_track      << "\n" // команда инициализации трека
             << "track_init_posx= "<< (int)fenix2cmd_keep_data.track_init_posx << "\n" // положение трека по x, pix
             << "track_init_posy= "<< (int)fenix2cmd_keep_data.track_init_posy << "\n" // положение трека по у, pix
             << "deinit_track   = "<< (int)fenix2cmd_keep_data.deinit_track    << "\n" // команда деинициализации трека
             << "poweroff_srv   = "<< (int)fenix2cmd_keep_data.poweroff_srv    << "\n" // команда отключения питания на сервере
             << "reinit         = "<< (int)fenix2cmd_keep_data.reinit          << "\n" // команда отключения питания на сервере
             << "=============================\n\n" << endl;
    }
#endif // USE_DBG

    if (fenix2cmd_keep_data.poweroff_srv && !fenix2cmd_keep_data.work_mode && !tracShats->isInited())
    {
        string cmd_poweroff_str = "poweroff";
        int res = system(cmd_poweroff_str.c_str());
    }

    if(fenix2cmd_keep_data.mode_mouse)
    {
//        cout << "dbg:: mode_mouse!" << endl;
        track_confirm_flag = 0;
        fenix2cmd_keep_data.mode_mouse = 0;
    }

    if(fenix2cmd_keep_data.mode_track)
    {
//        cout << "dbg:: mode_track!" << endl;
        track_confirm_flag = 1;
        fenix2cmd_keep_data.mode_track = 0;
    }


    if (fenix2cmd_keep_data.reinit /*&& fenix2cmd_keep_data.track_init_posx != 0 && fenix2cmd_keep_data.track_init_posy != 0*/)
    {
//        cout << "dbg::cmd:: reinit = 1" << endl;
        if(tracShats->isInited()) {tracShats->deinit();}
        fenix2cmd_keep_data.reinit = 0;
        rct = {(float)fenix2cmd_keep_data.track_init_posx,
               (float)fenix2cmd_keep_data.track_init_posy,
               rct_wh_2.x * 2 * frame_w_1,
               rct_wh_2.y * 2 * frame_h_1};
        //        cout << "dbg:: is inited = " << tracShats->isInited() << endl;
        //        cout << "dbg:: rct = " << rct << " start inited!" <<  endl;
        need_reinit = 1;
        rct_reinit = rct;
        initTracShats(rct);
        if (tracShats->isInited()) {need_reinit = 0;} // END if(need_reinit)
        //        cout << "dbg:: trackShats->isInited = " << tracShats->isInited() << endl;
        //        cout << "\n\ndbg:: REINIT RECT = " << rct << "\n\n" << endl;
    } // END fenix2cmd_keep_data.reinit

    if (fenix2cmd_keep_data.init_track)
    {
        //        std::cout << "dbg::cmd:: init_track = 1" << std::endl;
        rct = {(float)fenix2cmd_keep_data.track_init_posx,
               (float)fenix2cmd_keep_data.track_init_posy ,
               rct_wh_2.x * 2 * frame_w_1,
               rct_wh_2.y * 2 * frame_h_1};
        need_init = true;
    } // if cmd init_track

    if (fenix2cmd_keep_data.track_size_up) // увеличиваем размер рамки
    {
        //        cout << "dbg::cmd:: track_size_up = 1" << endl;
        rct_wh_2 += {rct_w_change_step, rct_h_change_step};
        fenix2cmd_keep_data.track_size_up = 0;
    } // END if (key == rct_increase_button)

    if (fenix2cmd_keep_data.track_size_down) // уменьшаем размер рамки
    {
        //        cout << "dbg::cmd:: track_size_down = 1" << endl;
        rct_wh_2 -= {rct_w_change_step, rct_h_change_step};
        fenix2cmd_keep_data.track_size_down = 0;
    } // END if (key == rct_decrease_button)


    if (fenix2cmd_keep_data.deinit_track)
    {
        // деинциализация трекера по клавише ESC
        if(tracShats->isInited()) {tracShats->deinit();}
        fenix2cmd_keep_data.deinit_track = 0;
    } // END cmd deinit_track

    if (fenix2cmd_keep_data.quit_server)
    {
        std::cout << "Exit on keypress" << std::endl;
        need_quit = true;
    } // if (fenix2cmd_keep_data.quit_server)
    return need_init;

} // -- END ethHandler
#endif // USE_ETH_CONTROLLER
#ifdef GUI_OK

bool Application::mouseHandler(Mat &img, const string &win_name, uchar &key, Rect2f &object_rect)
{
    // cv::Mat tmp_img = img.clone();

    if(!isTracShatsInitedFlag)
    {
        if(click_down)
        {
            if(first_click_down)
            {
                first_click_down = 0;
                p_down = p_mouse;
            } // -- END if(first_click_down)
            rct_mouse_aim = {p_mouse - rct_wh_2, p_mouse + rct_wh_2};
            cv::drawMarker(img, p_mouse, color::green, MARKER_CROSS, rct_mouse_aim.width, 1);
            cv::rectangle(img, rct_mouse_aim, color::red, 2);
        } //--END if(click_down)

    } // -- END if(!isTracShatsInitedFlag)
    else
    {
        cv::Mat tmp_track = frame_receive(Rect(aimRectShats.x * frame_receive.cols,
                                               aimRectShats.y * frame_receive.rows,
                                               aimRectShats.width * frame_receive.cols,
                                               aimRectShats.height * frame_receive.rows)).clone();
        if (tmp_track.data)
        {
            resize(tmp_track, tmp_track, Size(256,256));
            cvtColor(tmp_track,tmp_track,COLOR_GRAY2BGR);
            tmp_track.copyTo(img(Rect(Point(img.cols - 266, 10),tmp_track.size())));
            rectangle(img, Rect(img.cols - 266, 10, 256, 256), color::black, 3);
        } // END if (tmp_track.data)
    } // END else

    if (tracShats->isInited())
    {
        Rect rct_trac = Rect(aimRectShats.x * img.cols,
                             aimRectShats.y * img.rows,
                             aimRectShats.width * img.cols,
                             aimRectShats.height * img.rows);
        rectangle(img, rct_trac, color::red, 2);
        Rect2f srch_rct;
        tracShats->getSearchRect(srch_rct);
#ifdef TKDNN
        srch_rct = Rect2f(srch_rct.x - srch_rct.width * 0.5,
                          srch_rct.y - srch_rct.height * 0.5,
                          srch_rct.width,
                          srch_rct.height);
#endif // TKDNN
        Rect srcg_rct_i = Rect(srch_rct.x * img.cols,
                               srch_rct.y * img.rows,
                               srch_rct.width * img.cols,
                               srch_rct.height * img.rows);
        rectangle(img, srcg_rct_i, color::white, 2);
    }

    cv::drawMarker(img, pt_frame_center, color::green, MARKER_CROSS, MAX(pt_frame_center.x, pt_frame_center.y) * 2, 1);
    cv::imshow(win_name, img);
    cv::moveWindow(win_name, 1990, 10);
    key = cv::waitKey(1);
    if(!keyHandler(key))
    {
        need_quit = true;
        return false;
    }
    device->keyHandler(key);

    if(!isTracShatsInitedFlag)
    {
        cv::setMouseCallback(win_name, aimFrameCallback, &p_mouse);
        if(click_up)
        {
            click_up = 0;
            rct_mouse_aim = {p_mouse - rct_wh_2, p_mouse + rct_wh_2};
            cv::rectangle(img, rct_mouse_aim, color::green, 2);
            if(rct_mouse_aim.area() > 0)
            {
                click_down = 0;
                first_click_down = 1;
                object_rect = {rct_mouse_aim.x * frame_show_w_1,
                               rct_mouse_aim.y * frame_show_h_1,
                               rct_mouse_aim.width * frame_show_w_1,
                               rct_mouse_aim.height * frame_show_h_1};
                return true;
            } // -- END if(rct.area()>0)
        } //--END if(click_up)
    } // -- END if(!isTracShatsInitedFlag)
    return false;
} // -- END mouseHandler
#endif // GUI_OK

#ifdef GUI_OK
bool Application::keyHandler(uchar &key)
{
    if (key == rct_increase_button) // увеличиваем размер рамки
    {
        rct_wh_2 += {rct_w_change_step,rct_h_change_step};
    } // END if (key == rct_increase_button)
    if (key == rct_decrease_button) // уменьшаем размер рамки
    {
        rct_wh_2 -= {rct_w_change_step,rct_h_change_step};
    } // END if (key == rct_decrease_button)
    switch(key)
    {
    case 27: // деинциализация трекера по клавише ESC
        if(tracShats->isInited())
        {
            tracShats->deinit();
        }
        break;
    case '`':       // выход из программы по клавише "`"
        std::cout << "Exit on keypress" << std::endl;
        return false;
        break;
    default:
        break;
    }  // -- END switch(key)
    return true;
} // -- END keyHandler

#endif // GUI_OK
