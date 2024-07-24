#include "tmml_cl.hpp"

using namespace std;
using namespace cv;
using namespace chrono;

int main()
{
#ifdef CCOEFF_NORMED
    cout<<"match metod: CCOEFF_NORMED" << endl;
#elif COMBINED
    cout<<"match metod: COMBINED" << endl;
#endif
    int iter_num = NUM_ITERATIONS;
    cout<<"iterations: "<< iter_num << endl << endl;
    Rect temp_rect{temp_left, temp_top, TEMPLATE_WIDTH, TEMPLATE_HEIGHT};
    Mat img_work, img_temp;
    Mat img_source = imread("image_source", CV_8UC1);
    Rect work_rect(Point(0, 0), Point(WORK_WIDTH, WORK_HEIGHT ));
    img_work = img_source(work_rect);
    img_temp = img_source(temp_rect);
    duration<double> duration_matching;
    high_resolution_clock::time_point time_start, time_end;

//OpenCV
    double minVal, maxVal;
    Point minLoc, maxLoc;
    Mat img_result_cpu(Size(RESULT_WIDTH, RESULT_HEIGHT), CV_32FC1, Scalar(0));

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
    cout << "OpenCV xy =\t\t[" << temp_left << ", " << temp_top << "] "<<endl<<endl;
    normalize(img_result_cpu, img_result_cpu, 0, 255, NORM_MINMAX);
    img_result_cpu.convertTo(img_result_cpu, CV_8UC1);
    int k = 2;
    resize(img_result_cpu, img_result_cpu, Size(k*RESULT_WIDTH, k*RESULT_HEIGHT));
    const char* OpenCV_window = "result_CPU";

//OpenCL
    bool init_ok = true;
    unique_ptr<tmml_cl> cl = make_unique<tmml_cl>(init_ok, temp_left, temp_top, img_work, img_temp);
    if (init_ok)
    {
        Mat img_result_CL(Size(RESULT_WIDTH, RESULT_HEIGHT), CV_32SC1, Scalar(0));

        time_start = high_resolution_clock::now();
        for(int iter = 0; iter < iter_num; ++iter)
        {
            cl->matchingCL(img_work, img_temp );
            if(cl->temp_leftOK != temp_left || cl->temp_topOK != temp_top){cout << "CL iter " << iter << " error !!!" << endl; break;}
        }//-- END -- for(int iter = 0; iter < iter_num; ++iter)
        time_end = high_resolution_clock::now();

        auto time_matching_CL = duration_cast<microseconds>(time_end - time_start);
        printf("Duration CL =  \t\t%.2f mks \n", (float)time_matching_CL.count() / iter_num );
        cout << "openCL xy =\t\t[" << cl->res.xpos << ", " << cl->res.ypos <<  "] " <<endl<<endl;

        cl->uintToMat(cl->mData_ptr.get(), img_result_CL);
        normalize(img_result_CL, img_result_CL, 0, 255, NORM_MINMAX);
        img_result_CL.convertTo(img_result_CL, CV_8UC1);
        resize(img_result_CL, img_result_CL, Size(k*RESULT_WIDTH, k*RESULT_HEIGHT));
        const char* CL_window = "result_cl";
        namedWindow( CL_window, WINDOW_AUTOSIZE );
        moveWindow(CL_window, 900,600);
        imshow(CL_window, img_result_CL);
        cvtColor(img_work,img_work, COLOR_GRAY2BGR);
        rectangle(img_work, Point(cl->res.xpos, cl->res.ypos), Point(cl->res.xpos+img_temp.cols, cl->res.ypos+img_temp.rows),Scalar(0,0,255),3);
        const char* OpenCL = "matchingCL";

        namedWindow( OpenCV_window, WINDOW_AUTOSIZE );
        moveWindow(OpenCV_window, 900,100);
        imshow(OpenCV_window, img_result_cpu);

        namedWindow( OpenCL, WINDOW_AUTOSIZE );
        moveWindow(OpenCL, 1300,600);
        resize(img_work, img_work, Size(k*RESULT_WIDTH, k*RESULT_HEIGHT));
        imshow(OpenCL, img_work);

        unsigned char key = waitKey(0);
    }// END if (!init_ok)
    else { cout << "error init OpenCL !!!\n"; return -1; }

    return 0;
} // END main
