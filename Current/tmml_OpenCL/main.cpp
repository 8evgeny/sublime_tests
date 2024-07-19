#include "tmml.hpp"
#include "openCL.hpp"

using namespace std;
using namespace cv;
using namespace chrono;

int iter_num = 1000;
constexpr int temp_center_x = 150;
constexpr int temp_center_y = 165;
constexpr int temp_left = temp_center_x - 0.5 * TEMPLATE_WIDTH;
constexpr int temp_top = temp_center_y - 0.5 * TEMPLATE_HEIGHT;
float min_max_Val = 0.99999;
Mat img_work, img_temp;

#ifdef SQDIFF_NORMED
int match_method = matchMetod::TM_SQDIFF_NORMED;
#endif
#ifdef CCOEFF_NORMED
int match_method = matchMetod::TM_CCOEFF_NORMED;
#endif
#ifdef COMBINED
int match_method = matchMetod::TM_COMBINED;
#endif

int main()
{
    string mm;
    switch (match_method)
    {
        case matchMetod::TM_SQDIFF_NORMED:
        {
            mm = "TM_SQDIFF_NORMED";break;
        }
        case matchMetod::TM_CCOEFF_NORMED:
        {
            mm = "TM_CCOEFF_NORMED";break;
        }
        case matchMetod::TM_COMBINED:
        {
            mm = "TM_COMBINED";break;
        }
    }
    cout<<"match metod: "<<mm<<endl;
    cout<<"iterations: "<<iter_num<<endl<<endl;

    Rect temp_rect{temp_left, temp_top, TEMPLATE_WIDTH, TEMPLATE_HEIGHT};
    Mat img_source = imread("image_source", CV_8UC1);

    Mat img_result_cpu(cv::Size(RESULT_WIDTH, RESULT_HEIGHT), CV_32FC1, cv::Scalar(0));
    Mat img_result_cuda(cv::Size(RESULT_WIDTH, RESULT_HEIGHT), CV_32FC1, cv::Scalar(0));
    Rect work_rect(Point(0, 0), Point(WORK_WIDTH, WORK_HEIGHT));
    img_work = img_source(work_rect);
    img_temp = img_source(temp_rect);
    std::chrono::duration<double> duration_matching;
    std::chrono::system_clock::time_point time_start, time_end;
    bool tm_ok = 0;
    shared_ptr<tmml> tm = make_shared<tmml>(tm_ok, min_max_Val);
    tm->max_pix = tm->max_pix0;
    double minVal, maxVal;
    Point minLoc, maxLoc;   


//OpenCV
    cout << "origin xy =\t\t[" << temp_left << ", " << temp_top << "] "<<endl;
    time_start = system_clock::now();
    for(int iter = 0; iter < iter_num; ++iter)
    {
        matchTemplate(img_work, img_temp, img_result_cpu, match_method);
        minMaxLoc(img_result_cpu, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
        if(maxLoc.x != temp_left || maxLoc.y != temp_top){cout << "CPU iter=" << iter << " !!!" << endl; break;}
    }  // END for(int iter = 0; iter < iter_num; ++iter)
    time_end = system_clock::now();
    duration_matching = time_end - time_start;
    cout.precision(2);
    std::cout.setf(std::ios::fixed);
    cout << "Duration OpenCV =\t" << 1e3 * duration_matching.count()/iter_num << " ms" << endl;

//CUDA
    time_start = system_clock::now();
    for(int iter = 0; iter < iter_num; ++iter)
    {
        tm->work_cuda(img_work, img_temp, tm->max_pix);
        if(tm->max_pix.x != temp_left || tm->max_pix.y != temp_top){cout << "GPU iter=" << iter << " !!!" << endl; break;}
    }  // END for(int iter = 0; iter < iter_num; ++iter)
    time_end = system_clock::now();
    duration_matching = time_end - time_start;
    cout << "Duration CUDA =\t\t" << 1e3 * duration_matching.count()/iter_num  << " ms" << endl;
    cout << "cuda xy =\t\t[" << (int)tm->max_pix.x << ", " << (int)tm->max_pix.y << "] " /*<<"   bright= " << tm->max_pix.bright*/ << endl;

//OpenCL
    matchesOpenCL();


    tm->fill_result_array();
    double sum_diff = 0;
    for(int id = 0; id < RESULT_AREA; id++)
    {
        int x = tm->result_array_x[id];
        int y = tm->result_array_y[id];
        float bright_gpu = tm->result_array_bright[id];
        float bright_cpu = img_result_cpu.at<float>(y, x);
        img_result_cuda.at<float>(y, x) = bright_gpu;
        double diff = abs(bright_cpu - bright_gpu);
        //cout << id << "; x = " << x << "; y = " << y << "; cpu = " << bright_cpu << "; gpu = " << bright_gpu << endl;
        sum_diff += diff;
    } // END for(int id = 0; id < RESULT_AREA; id++)
//    cout << "sum_diff = " << sum_diff << "; RESULT_AREA = " << RESULT_AREA << "; raitio = " << sum_diff/RESULT_AREA << endl;

    normalize(img_result_cpu, img_result_cpu, 0, 255, NORM_MINMAX);
    img_result_cpu.convertTo(img_result_cpu, CV_8UC1);
    const char* OpenCV_window = "OpenCV";
    namedWindow( OpenCV_window, WINDOW_AUTOSIZE );
    moveWindow(OpenCV_window, 900,100);
    imshow(OpenCV_window, img_result_cuda);

    normalize(img_result_cuda, img_result_cuda, 0, 255, NORM_MINMAX);
    img_result_cuda.convertTo(img_result_cuda, CV_8UC1);
    const char* CUDA_window = "CUDA";
    namedWindow( CUDA_window, WINDOW_AUTOSIZE );
    moveWindow(CUDA_window, 1300,100);
    imshow(CUDA_window, img_result_cuda);

    unsigned char key = waitKey(0);
    tm.reset();
    return 0;
} // END main
