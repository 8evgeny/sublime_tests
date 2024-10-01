#include "trac_container.hpp"

using namespace std;
using namespace cv;

namespace mtrac
{

Scalar get_color(int num)
{
    switch(num)
    {
    case RED:       { return color::red;}
    case BLUE:      { return color::blue;}
    case GREEN:     { return color::green;}
    case WHITE:     { return color::white;}
    case GRAY:      { return color::gray;}
    case BLACK:     { return color::black;}
    case VIOL:      { return color::viol;}
    case CYAN:      { return color::cyan;}
    case YELLOW:    { return color::yell;}
    case ORANGE:    { return color::orange;}
    case DARKORANGE:{ return color::darkorange;}
    case BROWN:     { return color::brown;}
    default:        { return color::black;}
    } // -- END switch num
} // -- END get_color

TracContainer::TracContainer()
{
    cout << "TracContainer::Constructor" << endl;
} // -- END TracContainer

TracContainer::TracContainer(const string &config_path, Mat &frame, std::shared_ptr<Device> *device_, bool &ok)
{
    cout << "TracContainer::Constructor" << endl;
    ok = true;
    this->config_path = config_path;
    cout << "dbg:: TracContainer:: config_path = " << config_path << endl;
    ok = get_ini_params(this->config_path, "main_settings");
    cout << "TracContainer::get ini params OK is " << ok << endl;
    device = *device_;
    tracShats = make_shared<TracShats>(config_path, frame, ok);
    frame_show_w_1 = 1.f / frame.cols;
    frame_show_h_1 = 1.f / frame.rows;

    cout << "TracContainer::Constructor is " << ok << endl;
    return;
} // -- END TracContainer const string &config_path, Mat &frame, std::shared_ptr<Device> *device_, bool &ok

bool TracContainer::processShats()
{
    //    cout << "TracContainer::processShats::frame_process_tracshats size = " << frame_process_tracshats.size() << endl;
    //    cout << "TracContainer::processShats::tracShats->getROI() = " << tracShats->getROI() << endl;
    //    cout << "TracContainer::processShats::tracShats->getROI() = " << tracShats->getROI() << endl;
    // обновление рамки цели по текущему кадру
    //    cout << "aimRectShats before = " << aimRectShats << endl;
    rect2f_in_border(aimRectShats);
    //    cout << "aimRectShats =after " << aimRectShats << endl;
    //    cout << "tracShats->roi = " << tracShats->roi << endl;
    bool flag = tracShats->update(frame_process_tracshats, aimRectShats);
    //    cout << "TracContainer::processShats:: flag = " << flag << endl;
    if(flag)
    {
        if(tracShats->roi)
        {
            roi = tracShats->getROI();
        } // END if(tracShats->roi)
        return true;
    } // -- END if(flag)
    return false;
} // -- END processShats

void TracContainer::prepareFrameForTracShats(cv::Mat &frame_receive)
{
    //    cout << "TracContainer::prepareFrameForTracShats:: frame_receive.size = " << frame_receive.size() << endl;
    //    cout << "roi_mode = " << roi_mode<< endl;
    //    cout << "isRoiSetted = " << isRoiSetted << endl;
    if(roi_mode and isRoiSetted)
    {
        // расчет абсолютных координат ROI
        roi = tracShats->getROI();
        rect2f_in_border(roi);
        Rect realSizedROI(roi.x * frame_receive.cols, roi.y * frame_receive.rows,
                          roi.width * frame_receive.cols, roi.height * frame_receive.rows);
        //        cout << "realSizedROI = " << realSizedROI << endl;
#ifdef CCM_8UC1
        if(frame_process_tracshats.channels() == 1)
        {
            frame_process_tracshats = frame_receive(realSizedROI).clone();
        } // END if(frame_process_tracshats.channels() == 1)
#elif CCM_8UC3
        if(realSizedROI.width && realSizedROI.height )
        {
            cvtColor(frame_receive(realSizedROI), frame_process_tracshats, COLOR_BGR2GRAY);
        } // END if(realSizedROI.width && realSizedROI.height)
#endif // END CCM_8UC3
        //        rectangle(frame_color, realSizedROI, color::blue, 2);
    } // END if(roi_mode and isRoiSetted)
    else
    {
#ifdef CCM_8UC1
        frame_process_tracshats = frame_receive; //.clone();
#elif CCM_8UC3
        cvtColor(frame_receive, frame_process_tracshats, COLOR_BGR2GRAY);
#endif // END CCM_8UC3
    } // END if(!(roi_mode and isRoiSetted))

} // -- END prepareFrameForTracShats

void TracContainer::workflowShats(cv::Mat & frame_receive, cv::Mat & frame_show, int pos, int pos_main)
{
    int frame_show_width = frame_show.cols;
    int frame_show_height = frame_show.rows;
    Point pt_text = Point(30, 30 + pos * 20);
    prepareFrameForTracShats(frame_receive);

    float thik_pos = 1;
    if(pos == pos_main) {thik_pos++;}

    //    cout << "frame_receive.size = " << frame_receive.size() << "; frame_show.size = " << frame_show.size() << endl;
    if(isTracShatsFirstInitedFlag)
    {
        //        cout << "TracContainer::workflowShats::isTracShatsFirstInitedFlag=" << isTracShatsFirstInitedFlag << endl;
#ifdef GUI_OK
        if(demonstration_mode > 2 && tracShats->isInited())
        {
            string txt_pos = to_string(pos) + ":" + to_string(tracShats->trac_str.trac_id);
            // приведение рамки цели к абсолютным координатам
            Rect2f rectShats(aimRectShats.x * frame_show_width, aimRectShats.y * frame_show_height,
                             aimRectShats.width * frame_show_width, aimRectShats.height * frame_show_height);
            if(pos == pos_main)
            {
                putText(frame_show, txt_pos, pt_text + Point(20, 10), 2, 0.8, clr_pos_main, thik_pos);
                if(flag_zahvat)
                {
                    putText(frame_show, to_string(pos), Point(rectShats.tl()) + Point(2,12), 1, 1, clr_pos_main, thik_pos);
                } // END if(flag_zahvat)
            } // END if(pos == pos_main)
            else
            {
                putText(frame_show, txt_pos, pt_text + Point(20, 10), 2, 0.8, clr_pos, thik_pos);
                if(flag_zahvat)
                {
                    putText(frame_show, to_string(pos), Point(rectShats.tl()) + Point(2,12), 1, 1, clr_pos, thik_pos);
                } // END if(flag_zahvat)
            } // END else

#ifdef USE_CUDA
            rectangle(frame_show, Rect(pt_text - Point(7, 7), pt_text + Point(7, 7)), color::black, -1);
            rectangle(frame_show, Rect(pt_text - Point(3, 3), pt_text + Point(3, 3)), color::white, -1);
#endif // END ifdef USE_CUDA
#ifdef USE_CPU
            circle(frame_show, pt_text, 7, color::black, -1);
            circle(frame_show, pt_text, 3, color::white, -1);
#endif // END ifdef USE_CPU
#ifdef USE_CL
            rectangle(frame_show, Rect(pt_text - Point(7, 7), pt_text + Point(7, 7)), color::white, -1);
            rectangle(frame_show, Rect(pt_text - Point(3, 3), pt_text + Point(3, 3)), color::black, -1);
#endif // END ifdef USE_CL
        } // -- END if(demonstration_mode > 2 && tracShats->isInited())
#endif // END GUI_OK

        //        cout << "TracContainer::workflowShats::start process shats" << endl;
        flag_zahvat = processShats(); // обработка кадра
        //        cout << "TracContainer::workflowShats:: flag_zahvat = " << flag_zahvat << endl;
        if(flag_zahvat)
        {
            //            Scalar clr_pos = get_color(pos);
#ifdef GUI_OK
            // приведение рамки цели к абсолютным координатам
            Rect2f rectShats(aimRectShats.x * frame_show_width, aimRectShats.y * frame_show_height,
                             aimRectShats.width * frame_show_width, aimRectShats.height * frame_show_height);
            // отрисовка рамки цели
            if(pos == pos_main)
            {
                rectangle(frame_show, rectShats, clr_pos_main, thik_pos);
            } // END if(pos == pos_main)
            else
            {
                rectangle(frame_show, rectShats, clr_pos, thik_pos);
            } // END else
            // отрисовка центра объекта
            Point2f dimless_cent(tracShats->trac_str.obj_xy_x, tracShats->trac_str.obj_xy_y);
            Point2f center_show = Point2f(dimless_cent.x * frame_show_width, dimless_cent.y * frame_show_height);
            circle(frame_show, center_show, 2, color::white, -1);

            // добавление метки размера объекта на кадр
            if(demonstration_mode > 1)
            {
                tracShats->getSearchRect(searchRect);
                searchRect = Rect2f(searchRect.x * frame_show_width, searchRect.y * frame_show_height,
                                    searchRect.width * frame_show_width, searchRect.height * frame_show_height);
                //                rectangle(frame_show, searchRect, color::white, 1);
                if(demonstration_mode > 3)
                {
                    Point objSize(round(aimRectShats.width * frame_receive.cols),
                                  round(aimRectShats.height * frame_receive.rows));
                    string txt = ". TracShats: Object size=[" + to_string(objSize.x) + ", " + to_string(objSize.y) + "]";
                    if(pos == pos_main)
                    {
                        putText(frame_show, txt, pt_text + Point(30, 10), 2, 0.8, clr_pos_main, thik_pos);
                        //                        putText(frame_show, to_string(pos), Point(rectShats.tl()) + Point(2,12), 1, 1, clr_pos_main, thik_pos);
                    } // END if(pos == pos_main)
                    else
                    {
                        putText(frame_show, txt, pt_text + Point(30, 10), 2, 0.8, clr_pos, thik_pos);
                        //                        putText(frame_show, to_string(pos), Point(rectShats.tl()) + Point(2,12), 1, 1, clr_pos, thik_pos);
                    } // END else
                } // -- END if(demonstration_mode > 3)
            } // -- END if(demonstration_mode > 1)
#endif // END GUI_OK
        } // END if(flag_zahvat)
        else
        {
            if(!tracShats->isInited()){isTracShatsInitedFlag = false;}
        } // END if(!flag_zahvat)
    } // -- END if(isTracShatsFirstInitedFlag)
    else if(tracShatsInitReqFlag)
    {
        // инициализация трекера при поступлении запроса
        tracShatsInitReqFlag = false;
        rect2f_in_border(aimRectShats);
        rect2f_in_border(roi);
        //        cout << "dbg:: TracContainer::workflowShats aimRectShats = " << aimRectShats << endl;
        //        cout << "dbg:: TracContainer::workflowShats roi = " << roi << endl;
        //        cout << "Init tracker" << endl;
        if(!tracShats->isInited())
        {
            bool initFlag = false;
            //            cout << "NOT OK INIT IN aimRectShats = " << aimRectShats << endl;
            if(roi_mode)
            {
                initFlag = tracShats->init(aimRectShats, roi);
                tracShats->setWorkNumber(device->getFrameCounter());
                if(initFlag){isRoiSetted = true;}
            } // END if(roi_mode)
            else
            {
                initFlag = tracShats->init(aimRectShats);
                tracShats->setWorkNumber (device->getFrameCounter());
            } // END if(!roi_mode)
            if(initFlag)
            {
                if(!isTracShatsFirstInitedFlag){isTracShatsFirstInitedFlag = true;}
                isTracShatsInitedFlag = true;
            } // -- END if(initFlag)
            // подготовка нового кадра (т.к. для неинициализированного трекера кадр для обработки не подготовлен)
            prepareFrameForTracShats(frame_receive);
            // обработка кадра "на месте" для корректной инициализации трекера
            workflowShats(frame_receive, frame_show, pos, pos_main);
        } // -- END if(!tracShats->isInited())
    } // -- END else if(tracShatsInitReqFlag)
} // -- END workflowShats

bool TracContainer::get_ini_params(const string &config_path, const string &section)
{
    cout << "Begin TracContainer::get_ini_params[" << section << "], path: " << config_path << "\n";
    bool ok = true;

    INIReader reader(config_path);
    if(reader.ParseError() < 0)
    {
        cout << "ini reader parse error!\n";
        ok = false;
        return ok;
    } // END if(reader.ParseError() < 0)
    int roi_mode = 0, handle_flag = 0, get_rect_manual = 0, parallel = 0;

    ok &=  ext_ini::GetInteger(reader, section, "roi_mode", roi_mode);
    ok &=  ext_ini::GetInteger(reader, section, "handle_flag", handle_flag);
    ok &=  ext_ini::GetInteger(reader, section, "get_rect_manual", get_rect_manual);
    ok &=  ext_ini::GetInteger(reader, section, "parallel", parallel);
    ok &=  ext_ini::GetInteger(reader, section, "num_trac_max", num_trac_max);
    ok &=  ext_ini::GetInteger(reader, "demonstration_settings", "demonstration_mode", demonstration_mode);

    if(ok)
    {
        this->roi_mode = roi_mode;
        this->handle_flag = handle_flag;
        this->get_rect_manual = get_rect_manual;
        this->parallel = parallel;
    } // END if(ok)
    cout << "END get_ini_params Application" << endl;
    return ok;
} // -- END get_ini_params

void TracContainer::rect2f_in_border(Rect2f &rect)
{
    if(rect.x < 0) {rect.x = 0;}
    if(rect.y < 0) {rect.y = 0;}
    if((rect.x + rect.width) > 0.99999)
    {
        rect. x = 0.99999 - rect.width;
    } // END if((rect.x + rect.width) > 0.9999)
    if((rect.y + rect.height) > 0.99999)
    {
        rect.y = 0.99999 - rect.height;
    } // END if((rect.x + rect.width) > 0.9999)
} // -- END rect2f_in_border

bool TracContainer::init_trac(Rect2f &rectm, cv::Mat & frame_show)
{
    frame_show_w_1 = 1.f / frame_show.cols;
    frame_show_h_1 = 1.f / frame_show.rows;
    // инициализация трекера, если указана новая рамка цели
    rectm = Rect2f(rectm.x * frame_show_w_1, rectm.y * frame_show_h_1,
                   rectm.width * frame_show_w_1, rectm.height * frame_show_h_1);
    //    cout << "TracContainer::init_trac::rectm before = " << rectm << endl;
    rect2f_in_border(rectm);
    //    cout << "TracContainer::init_trac::rectm after = " << rectm << endl;
    bool initFlag = false;

    if(!tracShats->isInited())
    {
        if(roi_mode)
        {
            //            cout << "Application:: try init in " << rectm << endl;
            initFlag = tracShats->init(rectm, roi);
            tracShats->setWorkNumber(device->getFrameCounter());
            if(initFlag)
            {
                cout << "TracContainer:: OK init in " << rectm << ";\n roi = " << roi << endl;
                isRoiSetted = true;
            } // END if(initFlag)
            else
            {
                cout << "Application:: NOT OK init in " << rectm << endl;
            } // END else
        } // END if(roi_mode)
        else
        {
            initFlag = !tracShats->init(rectm);
            tracShats->setWorkNumber(device->getFrameCounter());
        } // END if(!roi_mode)
        if(initFlag)
        {
            cout << "TracContainer::handle treatment:: set isTracShatsFirstInitedFlag" << endl;
            if(!isTracShatsFirstInitedFlag) {isTracShatsFirstInitedFlag = true;}
            isTracShatsInitedFlag = true;
            tracShats->trac_str.trac_id;
        } // -- END if(initFlag)
    } // -- END if(!tracShats->isInited())
    cout << "TracContainer::init_trac::rectm = " << rectm << endl;
    //    cout << "TracContainer::init_trac::roi = " << roi << endl;
    rect2f_in_border(roi);
    return initFlag;
} // -- END init_trac

bool TracContainer::quit()
{
    return true;
} // -- END quit

}; // -- END namespace mtrac
