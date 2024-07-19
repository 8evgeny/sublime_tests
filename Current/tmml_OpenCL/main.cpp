#include "tmml.hpp"

using namespace std;
using namespace cv;
using namespace chrono;

constexpr int iter_num = 1000;
constexpr int temp_center_x = 150;
constexpr int temp_center_y = 165;
constexpr int temp_left = temp_center_x - 0.5 * TEMPLATE_WIDTH;
constexpr int temp_top = temp_center_y - 0.5 * TEMPLATE_HEIGHT;
float min_max_Val = 0.99999;

int main()
{

    Rect temp_rect{temp_left, temp_top, TEMPLATE_WIDTH, TEMPLATE_HEIGHT};
    Mat img_source = imread("image_source", CV_8UC1);
    Mat img_work, img_temp;
    Mat img_result_cpu(cv::Size(RESULT_WIDTH, RESULT_HEIGHT), CV_32FC1, cv::Scalar(0));
    Mat img_result_gpu(cv::Size(RESULT_WIDTH, RESULT_HEIGHT), CV_32FC1, cv::Scalar(0));
    Rect work_rect(Point(0, 0), Point(WORK_WIDTH, WORK_HEIGHT));
    img_work = img_source(work_rect);
    img_temp = img_source(temp_rect);
    std::chrono::duration<double> duration_1;
    std::chrono::system_clock::time_point time_point0, time_point1;
    bool tm_ok = 0;
    shared_ptr<tmml> tm = make_shared<tmml>(tm_ok, min_max_Val);
    tm->max_pix = tm->max_pix0;
    double minVal, maxVal;
    Point minLoc, maxLoc;   

//  0===============================================================
    time_point0 = system_clock::now();
    for(int iter = 0; iter < iter_num; ++iter)
    {
        matchTemplate(img_work, img_temp, img_result_cpu, TM_CCOEFF_NORMED);  // TM_CCOEFF_NORMED ;  TM_CCORR_NORMED ;TM_CCOEFF
        minMaxLoc(img_result_cpu, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
        if(maxLoc.x != temp_left || maxLoc.y != temp_top){cout << "CPU iter=" << iter << " !!!" << endl; break;}
    }  // END for(int iter = 0; iter < iter_num; ++iter)
    time_point1 = system_clock::now();
//  1===============================================================
    duration_1 = time_point1 - time_point0;
    cout << "Duration matchTemplate+minMaxLoc (OpenCV) CPU for 1 iter=" << round(1e6 * duration_1.count()/iter_num) << " mcsec" << endl;

//  ========================================================
    time_point0 = system_clock::now();
    for(int iter = 0; iter < iter_num; ++iter)
    {
        tm->work_tmml(img_work, img_temp, tm->max_pix);
        if(tm->max_pix.x != temp_left || tm->max_pix.y != temp_top){cout << "GPU iter=" << iter << " !!!" << endl; break;}
    }  // END for(int iter = 0; iter < iter_num; ++iter)
    time_point1 = system_clock::now();
//  ========================================================
    duration_1 = time_point1 - time_point0;
    cout << "                                Duration tmml for 1 iter=" << round(1e6 * duration_1.count()/iter_num) << " mcsec" << endl;

    cout << "xy=[" << (int)tm->max_pix.x << ", " << (int)tm->max_pix.y << "]; xy_ok=[";
    cout << temp_left << ", " << temp_top << "]; bright= " << tm->max_pix.bright << endl;

    tm->fill_result_array();
    double sum_diff = 0;
    for(int id = 0; id < RESULT_AREA; id++)
    {
        int x = tm->result_array_x[id];
        int y = tm->result_array_y[id];
        float bright_gpu = tm->result_array_bright[id];
        float bright_cpu = img_result_cpu.at<float>(y, x);
        img_result_gpu.at<float>(y, x) = bright_gpu;
        double diff = abs(bright_cpu - bright_gpu);
        //cout << id << "; x = " << x << "; y = " << y << "; cpu = " << bright_cpu << "; gpu = " << bright_gpu << endl;
        sum_diff += diff;
    } // END for(int id = 0; id < RESULT_AREA; id++)
    cout << "sum_diff = " << sum_diff << "; RESULT_AREA = " << RESULT_AREA << "; raitio = " << sum_diff/RESULT_AREA << endl;

    int k = 4;

    normalize(img_result_cpu, img_result_cpu, 0, 255, NORM_MINMAX);
    img_result_cpu.convertTo(img_result_cpu, CV_8UC1);
//    resize(img_result_cpu, img_result_cpu, Size(k*RESULT_WIDTH, k*RESULT_HEIGHT));
    const char* OpenCV_window = "OpenCV";
    namedWindow( OpenCV_window, WINDOW_AUTOSIZE );
    moveWindow(OpenCV_window, 900,100);
    imshow(OpenCV_window, img_result_gpu);

    normalize(img_result_gpu, img_result_gpu, 0, 255, NORM_MINMAX);
    img_result_gpu.convertTo(img_result_gpu, CV_8UC1);
//    resize(img_result_gpu, img_result_gpu, Size(k*RESULT_WIDTH, k*RESULT_HEIGHT));
    const char* CUDA_window = "CUDA";
    namedWindow( CUDA_window, WINDOW_AUTOSIZE );
    moveWindow(CUDA_window, 1300,100);
    imshow(CUDA_window, img_result_gpu);

    unsigned char key = waitKey(0);

    tm.reset();
    cout << "END MAIN!" << endl;
    return 0;
} // END main
