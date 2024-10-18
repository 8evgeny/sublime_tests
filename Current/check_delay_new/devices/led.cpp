#include <iostream>
#include <chrono>
#include <thread>
#include <time.h>
#include "application.hpp"
#include <cmath>
extern int frame_w;
extern int frame_h;
extern int frame_fps;

template<typename Tp>
void getGraph(  const std::vector<Tp> & vfunc_t,
                int step,
                std::string winname = "win",
                int type_ = 0,
                cv::Mat img = cv::Mat(cv::Size(1200,800), CV_8UC3,cv::Scalar(255,255,255))
              )
{
    using namespace cv;
    using namespace std;
    vector<double> vfunc;
    vfunc.resize(vfunc_t.size());
    for (int i = 0; i < vfunc_t.size(); i++)
    {
        auto buf = vfunc_t[i];
        vfunc[i] = buf;
    } // END for (int i = 0; i < vfunc_t.size(); i++)

    img = Scalar(255,255,255);
    if (!vfunc.size())
    {
        cout << "Not correct size func data!" << endl;
        return;
    } // END if (!vfunc.size())


    float maxf = *max_element(vfunc.begin(), vfunc.end());
    float minf = *min_element(vfunc.begin(), vfunc.end());
    std::vector<double> vbuf = vfunc;
    minf = 0;
    if (maxf == 0 && minf == 0)
    {
        minf = 0;
        maxf = 1;
    }
    if (type_ == 2)
    {
        minf = 0;
    }
    for(int i = 0; i < vbuf.size(); i++)
    {
        vbuf[i] = (vfunc[i] - minf) / (maxf - minf);
    } // END for(int i = 0; i < vbuf.size(); i++)

    int y0 = img.rows;
    if (minf < 0 && maxf > 0)
    {
        int y0 = round(maxf / (abs(minf) + maxf) * img.rows);
        line(img, Point(0, y0), Point(img.cols, y0), Scalar(100,100,100));
    } // END if ((minf <  0 && maxf > 0))
    double kf_ysz =  (double)img.rows;                      //смещение единичное ( в пикселях ) по Y
    double kf_xsz = (double)img.cols / (double)vfunc.size(); //смещение единичное ( в пикселях ) по X
    for (int i = 1; i < vfunc.size(); i++)
    {
        Point p_0 = Point(round((i-1) * kf_xsz), img.rows - round(vbuf[i-1] * kf_ysz));
        Point p_1 = Point(round((i) * kf_xsz), img.rows - round(vbuf[i] * kf_ysz));
        if (type_ == 0) // кривая
        {line(img, p_0 , p_1, Scalar(0,0,255), 1);}
        if (type_ == 1) // точки + мнк
        {circle(img, p_1, 0, Scalar(0,0,255), 1);}
        if (type_ == 2) // "гистограмма
        {
            Scalar clr = Scalar(127,127,127);
            Point p_y = Point(round((i-1) * kf_xsz), y0);
            Rect rct_hist_i(p_1, p_y);
            rectangle(img, rct_hist_i, color::Green::lime, -1);
            rectangle(img, rct_hist_i, color::green, 1);
            Point p_text = 0.5 * (rct_hist_i.tl() + rct_hist_i.br()) - Point(15, 0);

            if (vbuf[i])
            {
                putText(img, to_string((int)round(((float)i - 0.5) * step)), p_text, 1, 1, Scalar(0,0,255), 1);
                cout << "dbg:: vbuf[" << i << "]=" << vbuf[i] << endl;
                cout << "dbg:: vfunc[" << i << "]=" << vfunc[i] << endl;
                cout << "dbg:: " << ((float)i - 0.5) * step << endl;
            }
        } // END if (type_ == 2)
    } // END for (int i = 1; i < vfunc.size(); i++)



    for (int i = 1; i < 8 ; i++)
    {
        line(img, Point((1000/frame_fps ) * kf_xsz * i / step, img.rows ),
             Point((1000/frame_fps ) * kf_xsz * i / step , img.rows * 3 / 4),
             Scalar(255,0,0), 2, 8);
        putText(img, to_string(1000 * i/frame_fps),
                Point((1000 /frame_fps ) * kf_xsz * i / step - 15, img.rows * 3 / 4 - 10),
                2, 1, Scalar(255,0,0));
    }

    putText(img, to_string((int)maxf), Point(img.cols - to_string((int)maxf).size() * 10 - 80, 30), 2, 1, Scalar(0,0,0));
    putText(img, to_string((int)minf), Point(img.cols - to_string((int)minf).size() * 10 - 80, img.rows - 10), 2, 1, Scalar(0,0,0));
    return;
} // -- END void getGraph()template<typename Tp>

int Application::rnd(int N1){
   struct timespec time_n;
   clock_gettime(CLOCK_MONOTONIC, &time_n);
   int rnd2 = time_n.tv_nsec;
   srand(rnd2);
   return (int)(rand() % N1);
}

void Application::led_handler()
{
    while (true)
    {
        if (led_single_flash_enable)
        {
            switch (flash_duration)
            {
                case 1:
                system(cmd_led_blink_100_us);
                break;
                case 2:
                system(cmd_led_blink_200_us);
                break;
                case 3:
                system(cmd_led_blink_300_us);
                break;
                case 4:
                system(cmd_led_blink_400_us);
                break;
                case 5:
                system(cmd_led_blink_500_us);
                break;
                case 6:
                system(cmd_led_blink_600_us);
                break;
                case 7:
                system(cmd_led_blink_700_us);
                break;
                case 8:
                system(cmd_led_blink_800_us);
                break;
                case 9:
                system(cmd_led_blink_900_us);
                break;
                default:
                system(cmd_led_blink_900_us);
                break;
            } // end switch (flash_duration)
            ++num_send;
            time_flash_start = high_resolution_clock::now();
//            this_thread::sleep_for(nanoseconds(flash_duration));
//            system(cmd_led_off);
            led_single_flash_enable = false;
            this_thread::sleep_for(milliseconds(min_time_between_flash));
            this_thread::sleep_for(milliseconds(rnd(max_time_between_flash)));
        }
    }
}

void Application::setup_delay_find()
{
    hist_max_len = (1000 * num_wait) / frame_fps; //ms
    step = hist_max_len/ num_bin;
    results.resize(hist_max_len, 0);
    plot.resize(hist_max_len/step, 0);
#ifdef GUI_OK
    plot_pic = "../../Plot/Plot" + to_string(num_flash) + "_gui_ON.png";
#endif
#ifndef GUI_OK
    plot_pic = "../../Plot/Plot" + to_string(num_flash) + "_gui_OFF.png";
#endif

    rct_work = cv::Rect(x, y, w, h);
    img_led_area_1 = 1.f/rct_work.area();
    unique_ptr<thread> ptr = make_unique<thread>(&Application::led_handler, this);
    led_ptr.swap(ptr);

}// -- void Application::setup_delay_find()

void Application::delay_find(std::shared_ptr<Device> device)
{
    time_img_recive = high_resolution_clock::now();
    img_led = frame_show(rct_work);
    float tresh_bright = (float)norm(img_led, NORM_L1) * img_led_area_1;
    if (!led_single_flash_enable && num_send == num_receive)
    {
        led_single_flash_enable = true; //Разрешаем одну вспышку
    }
    if((tresh_bright > tresh_bright_min) && (num_send > num_receive ))
    {

            ++num_receive;
        if (!first_10_image_ignore)
        {
            auto time_tresh_bright = high_resolution_clock::now();
            duration<double> delay(time_tresh_bright - time_flash_start);
            int delay_ms = round(delay.count()*1000.f); // Время в миллисекундах
            std::cout << num_receive <<"; delay_ms="<< delay_ms <<" ms\r\n";

            results[delay_ms]++;
            plot[delay_ms/step]++;
            SV1 += delay_ms;
            SV2 += delay_ms * delay_ms;

            if(num_receive >= num_flash)
            {
                double midDEL =  SV1 / num_flash;
                double disp = SV2 / num_flash -  midDEL* midDEL;
                double sq_disp = sqrt(disp);
                cout << endl;
                cout << "========== midDEL=" << midDEL << endl;
                cout << "========== sq_disp=" << sq_disp << endl;
                cout << endl;
                cout << "receive/total = " << num_receive << "/"<< num_lost + num_receive  <<endl;

                namedWindow(plot_pic, WINDOW_NORMAL);
                cv::Mat img_plot = cv::Mat(cv::Size(1200,800), CV_8UC3, color::white);
                getGraph(plot, step, plot_pic, 2, img_plot);
                char tmp2[20];
                sprintf(tmp2,"%3.2f",round(midDEL * 100) / 100);
                string mid_DEL(tmp2);
                putText(img_plot, "middle delay=" + mid_DEL + " ms", Point(10, 30), 1, 2, Scalar(0,0,255), 2);
                sprintf(tmp2,"%3.2f",round(sq_disp * 100) / 100);
                string dispers(tmp2);
                putText(img_plot, "sq_disp=" + dispers + " ms", Point(10, 60), 1, 2, Scalar(0,0,255), 2);
                putText(img_plot, "receive/total=" + to_string(num_receive) + "/"+ to_string(num_lost + num_receive) + " frames" , Point(10, 90), 1, 2, Scalar(0,0,255), 2);
                putText(img_plot, "fps=" + to_string(frame_fps) + " frames/s" , Point(10, 120), 1, 2, Scalar(0,0,255), 2);
                putText(img_plot, "frame wight=" + to_string(frame_w) +  ", frame_height=" + to_string(frame_h), Point(10, 150), 1, 2, Scalar(0,0,255), 2);

    #ifdef GUI_OK
                putText(img_plot, "gui=ON" , Point(10, 180), 1, 2, Scalar(0,0,255), 2);
    #endif
    #ifndef GUI_OK
                putText(img_plot, "GUI=OFF" , Point(10, 150), 1, 2, Scalar(0,0,255), 2);
    #endif

                imwrite(plot_pic , img_plot);
                this_thread::sleep_for(chrono::milliseconds(1000));
                imshow(plot_pic, img_plot);
                led_ptr->detach();
                unsigned char key = waitKey(0);
                need_quit = 1;

                cout << "need quit" << endl;
                quit();
                need_break = true;
            } // if(number >= numCheck)
        } // -- if (!first_10_image_ignore)
        else
        {
// First 10 received delays ignored
            cout <<  num_receive<< "; ===== Ignored =====" << endl;
            if (num_receive == 10)
            {
                num_receive = 0;
                first_10_image_ignore = false;
            }
        }
    } // -- if(tresh_bright > tresh_bright_min)
    else
    {
        if (!led_single_flash_enable && (time_img_recive - time_flash_start > milliseconds(hist_max_len)))
        {
            ++num_lost;
            cout <<  num_lost<< "; =============== Flash not received =====" << endl;
// Разрешаем одну вспышку
            led_single_flash_enable = true;
        }
        else
        {
//            cout << "tresh_bright=" << tresh_bright << "\r\n";
        }
    }// -- else  if(tresh_bright > tresh_bright_min)
}// -- void Application::delay_find()
