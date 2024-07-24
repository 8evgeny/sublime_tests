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

//OpenCV
    double minVal, maxVal;
    Point minLoc, maxLoc;
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
    const char* OpenCV_window = "result_CPU";

//OpenCL
    unique_ptr<tmml_cl> tm_cl = make_unique<tmml_cl>(temp_left, temp_top);
    Mat img_result_CL(cv::Size(RESULT_WIDTH, RESULT_HEIGHT), CV_32SC1, cv::Scalar(0));

    tm_cl->initOpenCL(img_work, img_temp, match_method );

    time_start = high_resolution_clock::now();
    for(int iter = 0; iter < iter_num; ++iter)
    {
        tm_cl->matchingCL(img_work, img_temp );
        if(tm_cl->temp_leftOK != temp_left || tm_cl->temp_topOK != temp_top){cout << "CL iter " << iter << " error !!!" << endl; break;}
    }//-- END -- for(int iter = 0; iter < iter_num; ++iter)
    time_end = high_resolution_clock::now();

    auto time_matching_CL = std::chrono::duration_cast<chrono::microseconds>(time_end - time_start);
    printf("Duration CL =  \t\t%.2f mks \n", (float)time_matching_CL.count() / iter_num );
    cout << "openCL xy =\t\t[" << tm_cl->res.xpos << ", " << tm_cl->res.ypos <<  "] " <<endl<<endl;

    tm_cl->uintToMat(tm_cl->mData.get(), img_result_CL);
    normalize(img_result_CL, img_result_CL, 0, 255, NORM_MINMAX);
    img_result_CL.convertTo(img_result_CL, CV_8UC1);
    resize(img_result_CL, img_result_CL, Size(k*RESULT_WIDTH, k*RESULT_HEIGHT));
    const char* CL_window = "result_cl";
    namedWindow( CL_window, WINDOW_AUTOSIZE );
    moveWindow(CL_window, 900,600);
    imshow(CL_window, img_result_CL);
    cv::cvtColor(img_work,img_work,cv::COLOR_GRAY2BGR);
    cv::rectangle(img_work, cv::Point(tm_cl->res.xpos, tm_cl->res.ypos), cv::Point(tm_cl->res.xpos+img_temp.cols, tm_cl->res.ypos+img_temp.rows),cv::Scalar(0,0,255),3);
    const char* OpenCL = "matchingCL";

    namedWindow( OpenCV_window, WINDOW_AUTOSIZE );
    moveWindow(OpenCV_window, 900,100);
    imshow(OpenCV_window, img_result_cpu);

    namedWindow( OpenCL, WINDOW_AUTOSIZE );
    moveWindow(OpenCL, 1300,600);
    resize(img_work, img_work, Size(k*RESULT_WIDTH, k*RESULT_HEIGHT));
    imshow(OpenCL, img_work);

    unsigned char key = waitKey(0);
    return 0;
} // END main
