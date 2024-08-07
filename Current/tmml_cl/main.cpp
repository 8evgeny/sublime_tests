#include "tmml_cl.hpp"

using namespace std;
using namespace cv;
using namespace chrono;
float min_max_Val = 0.76;
const int iter_num = 1000;
const int koef_resize = 2;

constexpr int temp_center_x = 150;
constexpr int temp_center_y = 165;
constexpr int temp_left = temp_center_x - 0.5 * TEMPLATE_WIDTH;
constexpr int temp_top = temp_center_y - 0.5 * TEMPLATE_WIDTH;

int main()
{
#ifdef CCOEFF_NORMED
    cout<<"match metod: CCOEFF_NORMED" << endl;
#endif // END #ifdef CCOEFF_NORMED
#ifdef COMBINED
    cout<<"match metod: COMBINED" << endl;
#endif // END #ifdef COMBINED
    cout<<"iterations: "<< iter_num << endl << endl;
    Rect temp_rect{temp_left, temp_top, TEMPLATE_WIDTH, TEMPLATE_WIDTH};
    Mat img_source = imread("image_source", CV_8UC1);
    Rect work_rect(Point(0, 0), Point(WORK_WIDTH, WORK_WIDTH));
    __attribute__((aligned(512))) Mat img_work = img_source(work_rect).clone();
    __attribute__((aligned(512))) Mat img_temp = img_source(temp_rect).clone();
    duration<double> duration_matching;
    high_resolution_clock::time_point time_start, time_end;
    Mat img_work1;

//OpenCV
    double minVal, maxVal;
    Point minLoc, maxLoc;
    Mat img_result_cpu(Size(RESULT_WIDTH, RESULT_WIDTH), CV_32FC1, Scalar(0));

    time_start = high_resolution_clock::now();
    for(int iter = 0; iter < iter_num; ++iter)
    {
        matchTemplate(img_work, img_temp, img_result_cpu, TM_CCOEFF_NORMED);
        minMaxLoc(img_result_cpu, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
        if(maxLoc.x != temp_left || maxLoc.y != temp_top){cout << "CPU iter=" << iter << " !!!" << endl; break;}
    }  // END for(int iter = 0; iter < iter_num; ++iter)
    time_end = high_resolution_clock::now();
    auto time_matching_CPU = duration_cast<microseconds>(time_end - time_start);
    printf("Duration OpenCV =  \t%.2f mks \n", (float)time_matching_CPU.count() / iter_num );
    cout << "OpenCV xy = [" << temp_left << ", " << temp_top << "]" << endl << endl;

#ifdef find_diff_result
    Mat img_result_show, img_result_cpu_show;
    normalize(img_result_cpu, img_result_cpu_show, 0, 255, NORM_MINMAX);
    img_result_cpu_show.convertTo(img_result_cpu_show, CV_8UC1);
    resize(img_result_cpu_show, img_result_cpu_show, Size(koef_resize*RESULT_WIDTH, koef_resize*RESULT_WIDTH));
    const char* OpenCV_window = "result_CPU";
#endif

//OpenCL
    bool ok = false;
    unique_ptr<tmml_cl> tm = make_unique<tmml_cl>(ok, min_max_Val);
    if(ok)
    {
        time_start = high_resolution_clock::now();
        for(int iter = 0; iter < iter_num; ++iter)
        {
            tm->work_tmml(img_work, img_temp, tm->max_pix);
            if(tm->max_pix.x != temp_left || tm->max_pix.y != temp_top)
            {
                cout << "CL iter " << iter << " error !!!" << endl;
                ok = false;
                break;
            }
        }//-- END -- for(int iter = 0; iter < iter_num; ++iter)
        time_end = high_resolution_clock::now();
        if (ok)
        {
            auto time_matching_CL = duration_cast<microseconds>(time_end - time_start);
            printf("Duration CL =  \t\t%.2f mks \n", (float)time_matching_CL.count() / iter_num );
            cout << "openCL xy = [" << ((int)tm->max_pix.x) << ", " << ((int)tm->max_pix.y) << "]" << endl << endl;
        }// END if (ok)

//Results
    #ifdef find_diff_result
        normalize(tm->img_result, img_result_show, 0, 255, NORM_MINMAX);
        img_result_show.convertTo(img_result_show, CV_8UC1);
        resize(img_result_show, img_result_show, Size(koef_resize*RESULT_WIDTH, koef_resize*RESULT_WIDTH));
        const char* CL_window = "result_cl";
        namedWindow( CL_window, WINDOW_AUTOSIZE );
        moveWindow(CL_window, 900,600);
        imshow(CL_window, img_result_show);
        cvtColor(img_work, img_work1, COLOR_GRAY2BGR);
        rectangle(img_work1, Point(tm->max_pix.x, tm->max_pix.y), Point(tm->max_pix.x+img_temp.cols, tm->max_pix.y+img_temp.rows), Scalar(0,0,255), 3);
        const char* OpenCL = "matchingCL";
        namedWindow( OpenCL, WINDOW_AUTOSIZE );
        moveWindow(OpenCL, 1300, 600);
        resize(img_work1, img_work1, Size(koef_resize*WORK_WIDTH, koef_resize*WORK_WIDTH));
        imshow(OpenCL, img_work1);
    #endif // #ifdef find_diff_result

    }// END if (!init_ok)
    else { cout << "error init OpenCL !!!\n"; return 1; }

#ifdef find_diff_result
    namedWindow( OpenCV_window, WINDOW_AUTOSIZE );
    moveWindow(OpenCV_window, 900, 100);
    imshow(OpenCV_window, img_result_cpu_show);
#endif
    unsigned char key = waitKey(0);

    tm.reset();
    cout << "END MAIN!" << endl;
    return 0;
} // END main
