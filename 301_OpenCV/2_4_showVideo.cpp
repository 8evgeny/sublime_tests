#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>
using namespace std;

int g_slider_position = 0;
int g_run = 1, g_dontset = 0; // начинаем в режиме покадрового просмотра
cv::VideoCapture g_cap;

void onTrackbarSlide( int pos, void *) {
    g_cap.set( cv::CAP_PROP_POS_FRAMES, pos );
    if( !g_dontset )
    g_run = 1;
    g_dontset = 0;
}

int main( int argc, char** argv ) {
//    cv::namedWindow( "Example2_4", CV_WINDOW_AUTOSIZE );
    cv::namedWindow( "Example2_4", cv::WINDOW_NORMAL );
    g_cap.open( string(argv[1]) );
    int frames = (int) g_cap.get(cv::CAP_PROP_FRAME_COUNT);
    int tmpw = (int) g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int tmph = (int) g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    cout << "В виде " << frames << " кадров размером("
    << tmpw << ", " << tmph << ")." << endl;

    cv::createTrackbar("Position", "Example2_4", &g_slider_position, frames,
    onTrackbarSlide);

    cv::Mat frame;
    for(;;) {
        if( g_run != 0 ) {
            g_cap >> frame; if(frame.empty()) break;
            int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);
            g_dontset = 1;
            cv::setTrackbarPos("Position", "Example2_4", current_pos);
            cv::imshow( "Example2_4", frame );
            g_run -= 1;
        }
        char c = (char) cv::waitKey(10);
        if(c =='s'){ //Покадровый режим
            g_run = 1;
            cout << "Покадровый режим, run = " << g_run << endl;
        }
        if(c =='r'){ //Непрерывный режим
            g_run = -1;
            cout << "Непрерывный режим, run = " << g_run << endl;
        }
        if(c == 27) //Esc
            break;
    }
    return(0);
}
