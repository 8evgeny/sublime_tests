#include "tmml.hpp"
#include "openCL.hpp"
using namespace std;
using namespace cv;
using namespace chrono;

constexpr int temp_center_x = 150;
constexpr int temp_center_y = 165;
constexpr int temp_left = temp_center_x - 0.5 * TEMPLATE_WIDTH;
constexpr int temp_top = temp_center_y - 0.5 * TEMPLATE_HEIGHT;
float min_max_Val = 0.99999;

int main()
{
    int iter_num = NUM_ITERATIONS;
#ifdef SQDIFF_NORMED
    int match_method = tmml_cl::matchMetod::TM_SQDIFF_NORMED;
#elif CCOEFF_NORMED
    int match_method = tmml_cl::matchMetod::TM_CCOEFF_NORMED;
#elif COMBINED
    int match_method = tmml_cl::matchMetod::TM_COMBINED;
#endif

    string mm;
    switch (match_method)
    {
        case tmml_cl::matchMetod::TM_SQDIFF_NORMED:
        {
            mm = "TM_SQDIFF_NORMED"; break;
        }
        case tmml_cl::matchMetod::TM_CCOEFF_NORMED:
        {
            mm = "TM_CCOEFF_NORMED"; break;
        }
        case tmml_cl::matchMetod::TM_COMBINED:
        {
            mm = "TM_COMBINED"; break;
        }
    }
    cout<<"match metod: "<< mm << endl;
    cout<<"iterations: "<< iter_num << endl << endl;
    Rect temp_rect{temp_left, temp_top, TEMPLATE_WIDTH, TEMPLATE_HEIGHT};
    Mat img_work, img_temp;
    Mat img_source = imread("image_source", CV_8UC1);
    Rect work_rect(Point(0, 0), Point(WORK_WIDTH, WORK_HEIGHT ));
    img_work = img_source(work_rect);
    img_temp = img_source(temp_rect);
    duration<double> duration_matching;
    high_resolution_clock::time_point time_start, time_end;
    bool tm_ok = 0;
    shared_ptr<tmml> tm = make_shared<tmml>(tm_ok, min_max_Val);
    tm->max_pix = tm->max_pix0;
    double minVal, maxVal;
    Point minLoc, maxLoc;   

//OpenCV
    Mat img_result_cpu(cv::Size(RESULT_WIDTH, RESULT_HEIGHT), CV_32FC1, cv::Scalar(0));
    time_start = high_resolution_clock::now();
    for(int iter = 0; iter < iter_num; ++iter)
    {
        matchTemplate(img_work, img_temp, img_result_cpu, match_method);//TM_CCOEFF_NORMED
        minMaxLoc(img_result_cpu, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
        if(maxLoc.x != temp_left || maxLoc.y != temp_top){cout << "CPU iter=" << iter << " !!!" << endl; break;}
    }  // END for(int iter = 0; iter < iter_num; ++iter)
    time_end = high_resolution_clock::now();
    auto time_matching_CPU = std::chrono::duration_cast<chrono::microseconds>(time_end - time_start);
    printf("Duration OpenCV =  \t%.2f mks \n", (float)time_matching_CPU.count() / iter_num );
    cout << "OpenCV xy =\t\t[" << temp_left << ", " << temp_top << "] "<<endl<<endl;
    normalize(img_result_cpu, img_result_cpu, 0, 255, NORM_MINMAX);
    img_result_cpu.convertTo(img_result_cpu, CV_8UC1);
    int k = 2;
    resize(img_result_cpu, img_result_cpu, Size(k*RESULT_WIDTH, k*RESULT_HEIGHT));
    const char* OpenCV_window = "OpenCV";

//CUDA
    time_start = high_resolution_clock::now();
    for(int iter = 0; iter < iter_num; ++iter)
    {
        tm->work_cuda(img_work, img_temp, tm->max_pix);
        if(tm->max_pix.x != temp_left || tm->max_pix.y != temp_top){cout << "CUDA iter " << iter << " error !!!" << endl; break;}
    }  // END for(int iter = 0; iter < iter_num; ++iter)
    time_end = high_resolution_clock::now();
    auto time_matching_CUDA = std::chrono::duration_cast<chrono::microseconds>(time_end - time_start);
    printf("Duration OpenCV =  \t%.2f mks \n", (float)time_matching_CUDA.count() / iter_num );
    cout << "cuda xy =\t\t[" << (int)tm->max_pix.x << ", " << (int)tm->max_pix.y << "] " /*<<"   bright= " << tm->max_pix.bright*/ << endl<<endl;
    tm->fill_result_array();
    double sum_diff = 0;
    Mat img_result_cuda(cv::Size(RESULT_WIDTH, RESULT_HEIGHT), CV_32FC1, cv::Scalar(0));
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
    normalize(img_result_cuda, img_result_cuda, 0, 255, NORM_MINMAX);
    img_result_cuda.convertTo(img_result_cuda, CV_8UC1);
    resize(img_result_cuda, img_result_cuda, Size(k*RESULT_WIDTH, k*RESULT_HEIGHT));
    const char* CUDA_window = "CUDA";

//OpenCL
    unique_ptr<tmml_cl> tm_cl = make_unique<tmml_cl>(temp_left, temp_top);
    Mat img_result_CL(cv::Size(RESULT_WIDTH, RESULT_HEIGHT), CV_32SC1, cv::Scalar(0));
    tm_cl->matchingOpenCL(tm_cl, img_work, img_temp, img_result_CL, match_method, iter_num);
    normalize(img_result_CL, img_result_CL, 0, 255, NORM_MINMAX);
    img_result_CL.convertTo(img_result_CL, CV_8UC1);
    resize(img_result_CL, img_result_CL, Size(k*RESULT_WIDTH, k*RESULT_HEIGHT));
    const char* CL_window = "OpenCL";
    namedWindow( CL_window, WINDOW_AUTOSIZE );
    moveWindow(CL_window, 900,600);
    imshow(CL_window, img_result_CL);
    cv::cvtColor(img_work,img_work,cv::COLOR_GRAY2BGR);
    cv::rectangle(img_work, cv::Point(tm_cl->res.xpos, tm_cl->res.ypos), cv::Point(tm_cl->res.xpos+img_temp.cols, tm_cl->res.ypos+img_temp.rows),cv::Scalar(0,0,255),3);
    const char* OpenCL = "matchingOpenCL";

    namedWindow( OpenCV_window, WINDOW_AUTOSIZE );
    moveWindow(OpenCV_window, 900,100);
    imshow(OpenCV_window, img_result_cpu);

    namedWindow( CUDA_window, WINDOW_AUTOSIZE );
    moveWindow(CUDA_window, 1300,100);
    imshow(CUDA_window, img_result_cuda);

    namedWindow( OpenCL, WINDOW_AUTOSIZE );
    moveWindow(OpenCL, 1300,600);
    resize(img_work, img_work, Size(k*RESULT_WIDTH, k*RESULT_HEIGHT));
    imshow(OpenCL, img_work);

    unsigned char key = waitKey(0);
    tm.reset();
    return 0;
} // END main
