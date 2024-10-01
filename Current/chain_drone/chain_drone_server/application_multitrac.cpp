#include "application.hpp"


bool Application::processShats(std::list<std::unique_ptr<TracShatsContainer>> &trackers)
{
    // обновление рамки цели по текущему кадру
    bool flag = tracShats->update(frame_process_tracshats, aimRectShats);
    //std::cout << "processShats " << flag << std::endl;
    if ((aimRectShats & rct_frame) != aimRectShats)
    {
        tracShats->deinit();
        return false;
    }
    if(flag)
    {
        if(tracShats->roi)
        {
            roi = tracShats->getROI();
        } // -- END if(tracShats->roi)
        return true;
    } // -- END if(tracShats->update(frame_process_tracshats, aimRectShats))
    return false;
} // -- END processShats

void Application::workflowShats(std::list<std::unique_ptr<TracShatsContainer>> &trackers)
{
    if(isTracShatsFirstInitedFlag)
    {
#ifdef GUI_OK
        if(demonstration_mode > 2 && tracShats->isInited())
        {
            cv::circle(frame_show, Point(80, 90), 5, clr_scaling, -1);
        } // -- END if(demonstration_mode > 2 && tracShats->trac_st.zahvat)
#endif //GUI_OK

        bool flag = processShats();// обработка кадра
        if(flag)
        {
#ifdef GUI_OK
            // приведение рамки цели к абсолютным координатам
            cv::Rect2f rectShats(aimRectShats.x * frame_show.cols,
                                 aimRectShats.y * frame_show.rows,
                                 aimRectShats.width * frame_show.cols,
                                 aimRectShats.height * frame_show.rows);
            // отрисовка рамки цели
            cv::rectangle(frame_show, rectShats, color::Green::lime, 1);
            // отрисовка центра объекта
            cv::Point2f center = tracShats->getTargetCenter();
            center = cv::Point2f(center.x * frame_show.cols, center.y * frame_show.rows);
            cv::circle(frame_show, center, 2, color::red, -1);
            // добавление метки размера объекта на кадр
            if(demonstration_mode > 1)
            {
                cv::Rect2f searchRect = tracShats->getSearchRect();
                searchRect = cv::Rect2f(searchRect.x * frame_show.cols,
                                        searchRect.y * frame_show.rows,
                                        searchRect.width * frame_show.cols,
                                        searchRect.height * frame_show.rows);
                cv::rectangle(frame_show, searchRect, color::blue, 1);
                /// FENIX 2
                string delta_txt = "Delta position: [" +
                        to_string((searchRect.x + 0.5 * searchRect.width) / show2originImgRatio - frame_receive.cols * 0.5)  + "; " +
                        to_string((searchRect.y + 0.5 * searchRect.height) / show2originImgRatio - frame_receive.rows * 0.5) + "]";
                putText(frame_show, delta_txt, Point(50, 50),FONT_ITALIC, 1, color::Green::lime, 2);

                if(demonstration_mode > 3)
                {
                    cv::Point objSize(round(aimRectShats.width * frame_receive.cols),
                                      round(aimRectShats.height * frame_receive.rows));
                    std::string txt = "Object size=[" + to_string(objSize.x) + ", " + to_string(objSize.y) + "]";
                    putText(frame_show, txt, Point(100, 100), FONT_ITALIC, 1, color::Green::lime, 2);
                } // -- END if(demonstration_mode > 3)
            } // -- END if(demonstration_mode > 1)
#endif //GUI_OK
            // -- END if(flag)
        }
        else
        {
            if(!tracShats->isInited()){isTracShatsInitedFlag = false;}
        }
        // -- END if(isTracShatsFirstInitedFlag)
    }
    else if(tracShatsInitReqFlag)
    {      // инициализация трекера при поступлении запроса
        tracShatsInitReqFlag = false;
        std::cout << "Init tracker" << std::endl;
        initTracShats(aimRectShats);
    } // -- END else if(tracShatsInitReqFlag)
} // -- END workflowShats

void Application::initTracShats(std::unique_ptr<TracShatsContainer> &trac, Rect2f &rect)
{
    if(!tracShats->isInited() && ( (rect & rct_frame) == rect))
    {
        bool initFlag = false;

        if(roi_mode)
        {
            cout << "dbg:: start init!" << endl;
            initFlag = tracShats->init(rect, roi);
            cout << "dbg:: initFlag = " << initFlag << endl;
            tracShats->setWorkNumber(device->getFrameCounter());
            if(initFlag)
            {
                isRoiSetted = true;
            }
        } // END if(roi_mode)
        else
        {
            cout << "dbg:: start init!" << endl;
            initFlag = tracShats->init(rect);
            cout << "dbg:: initFlag = " << initFlag << endl;
            tracShats->setWorkNumber(device->getFrameCounter());
        }
        if(initFlag)
        {
            if(!isTracShatsFirstInitedFlag){isTracShatsFirstInitedFlag = true;}
            isTracShatsInitedFlag = true;
        } // -- END if(initFlag)
    } // -- END if(!tracShats->isInited())
    prepareFrameForTracShats();
    // обработка кадра "на месте" для корректной инициализации трекера

    workflowShats();

    return;
} // -- END initTracShats


// подготовка изображения для tracShats
void Application::prepareFrameForTracShats(std::list<std::unique_ptr<TracShatsContainer>> &trackers)
{
    for(auto &t : trackers)
    {
        if(roi_mode and isRoiSetted)
        {
            // расчет абсолютных координат ROI
            cv::Rect realSizedROI(t->roi.x * frame_receive.cols, t->roi.y * frame_receive.rows,
                                  t->roi.width * frame_receive.cols, t->roi.height * frame_receive.rows);
            t->frame = frame_receive(realSizedROI).clone();
            //                        // отрисовка ROI
            //                        cv::rectangle(frame_color, realSizedROI, color::blue, 2);
            // cv::imwrite("../test_data/img1.png", frame_process_tracshats);
        } // END roi_mode
        else
        {
            t->frame = frame_receive; //.clone();
        } // END !roi_mode
    } // END for(auto &t : trackers)
    return;
} // -- END prepareFrameForTracShats
