#include "tkdnn_container.hpp"

using namespace std;
using namespace cv;

TKDNNContainer::TKDNNContainer()
{
    cout << "Конструктор TKDNNContainer!" << endl;
    return;
}

TKDNNContainer::TKDNNContainer(const std::string &config_path, cv::Mat &frame_process_0, bool &ok)
{
    cout << "TracContainer::Constructor" << endl;
    ok = true;
    cout << "TracContainer::Constructor is " << ok << endl;

    ok = get_ini_params(config_path,"main_settings");
    if(!ok) {cout << "ERROR TKDNNContainer::get_ini_params!" << endl; return;}
    trac_nnet_ptr = make_shared<TracTKDNN>(config_path, frame_process_0, ok);
    if(!ok)
    {
        cout << "TKDNNContainer::NOT OK create trac_nnet_ptr: quit!" << endl;
        return;
    } // END if(!ok)
    cout << "dbg:: Start new frame!" << endl;
    trac_nnet_ptr->trac_str.new_frame = 1;
#ifdef USE_LOGGER
    bool create_logger_status;
    logger_artem::create(config_path, create_logger_status);
    if(!create_logger_status)
    {
        ok = false;
        return;
    } // END if(!create_logger_status)
#endif //USE_LOGGER

} // -- END TKDNNContainer

bool TKDNNContainer::get_ini_params(const string &config_path, const string &section)
{
    cout << "Begin TKDNNContainer::get_ini_params[" << section << "], path: " << config_path << "\n";
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

    if(ok)
    {
        this->roi_mode = roi_mode;
    } // END if(ok)
    cout << "END get_ini_params Application" << endl;
    return ok;
} // -- END get_ini_params


TKDNNContainer::~TKDNNContainer()
{
    cout << "Деструктор TKDNNContainer!" << endl;
    return;
} // -- END TKDNNContainer

#ifdef  USE_TKDNN
bool TKDNNContainer::update(cv::Rect2f & aimRectShats, cv::Mat & frame_show)
{
    bool flag_zahvat = trac_nnet_ptr->update(frame_process_tkdnn, aimRectShats);
#ifdef USE_LOGGER
    LoggerArtem::inst().logTimedBasedFPS("Scan FPS = ", trac_nnet_ptr->trac_str.scan_exec_time);
    LoggerArtem::inst().logTimedBasedFPS("YOLO FPS = ", trac_nnet_ptr->trac_str.yolo_exec_time);
#endif // USE_LOGGER

#ifdef GUI_OK
    frame_show_width = frame_show.cols;
    frame_show_height = frame_show.rows;

    if(trac_nnet_ptr->find_)
    {
        int num = 0;
        for(list<trac_data>::iterator trac = trac_nnet_ptr->ltrac_data_ptr->begin(); trac != trac_nnet_ptr->ltrac_data_ptr->end(); trac++)
        {
            // приведение рамки цели к абсолютным координатам
            Point lt(trac->x * frame_show_width - trac->w * frame_show_width, trac->y * frame_show_height - trac->h * frame_show_height);
            Point br(trac->x * frame_show_width + trac->w * frame_show_width, trac->y * frame_show_height + trac->h * frame_show_height);
            Rect rectShats(lt, br);
            Point2f center_show = 0.5 * (lt + br);
            if(num == num_main)
            {
                // отрисовка рамки цели
                rectangle(frame_show, rectShats, clr_main, thik + 1);
                // отрисовка центра объекта
                circle(frame_show, center_show, thik + 1 , clr_main, -1);
                putText(frame_show, to_string(num), br, FONT_HERSHEY_SIMPLEX, font_scale, clr_main,  thik + 1);
                Point pt_text = Point(frame_show.cols - 200, 30 + num * 20);
                string txt_pos = "tkdnn " + to_string(num);
                putText(frame_show, txt_pos, pt_text + Point(20, 10), 2, 0.8, clr_main, thik);
            } // END if(num == num_main)
            else
            {
                // отрисовка рамки цели
                rectangle(frame_show, rectShats, clr_txt, thik);
                // отрисовка центра объекта
                circle(frame_show, center_show, thik, clr_txt, -1);
                putText(frame_show, to_string(num), br, FONT_HERSHEY_SIMPLEX, font_scale, clr_txt, thik);
                Point pt_text = Point(frame_show.cols - 200, 30 + num * 20);
                string txt_pos = "tkdnn " + to_string(num);
                putText(frame_show, txt_pos, pt_text + Point(20, 10), 2, 0.8, clr_txt, thik);
            } // END else
            num++;
        } // END for(vector<trac_data>::iterator trac = vtrac->begin(); trac != vtrac->end(); trac++)
    } // END if(trac_nnet_ptr->find_)
#endif // END #if defined(GUI_OK)

    return flag_zahvat;
} // -- END update

bool TKDNNContainer::keyHandler(uchar & key, cv::Rect2f & rct)
{
    if(key == 'q')
    {
        if(num_main < trac_nnet_ptr->ltrac_data_ptr->size() - 1) {num_main++;}
        else {num_main = 0;}
        return false;
    } // END if(key == 'q')

    if(key == 'w')
    {
        if(num_main < trac_nnet_ptr->ltrac_data_ptr->size())
        {
            list<trac_data>::iterator it = trac_nnet_ptr->ltrac_data_ptr->begin();
            advance(it,num_main);
            rct = {it->x - it->w,
                   it->y - it->w,
                   2 * it->w,
                   2 * it->h};
            return true;
        } // END if(num_main < trac_nnet_ptr->ltrac_data_ptr.size())
    } // END if(key == 'w')
    return false;
} // -- END keyHandler

void TKDNNContainer::prepareFrameForTKDNN(cv::Mat & frame_receive)
{
    if(roi_mode and isRoiSetted)
    {
        // расчет абсолютных координат ROI
        Rect realSizedROI(roi.x * frame_receive.cols, roi.y * frame_receive.rows,
                          roi.width * frame_receive.cols, roi.height * frame_receive.rows);
        frame_process_tkdnn = frame_receive(realSizedROI).clone();
    } // END if(roi_mode and isRoiSetted)
    else
    {
        frame_process_tkdnn = frame_receive.clone();
    } // END if(!(roi_mode and isRoiSetted))

} // -- END prepareFrameForTKDNN

int TKDNNContainer::isFind()
{
    return trac_nnet_ptr->find_;
} // -- END isFind

std::shared_ptr<std::list<trac_data>> TKDNNContainer::getList()
{
    return trac_nnet_ptr->ltrac_data_ptr;
} // -- END getList
#endif // USE_TKDNN
