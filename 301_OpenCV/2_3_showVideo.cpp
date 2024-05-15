#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
int main( int argc, char** argv ) {
    cv::namedWindow( "Example 2.3", cv::WINDOW_AUTOSIZE );
    cv::VideoCapture cap;
    cap.open( std::string(argv[1]) );
    cv::Mat frame;
    for(;;) {
        cap >> frame;
        if( frame.empty() ) break;
        cv::imshow( "Example 2.3", frame );
        if( cv::waitKey(33) >= 0 ) break;
#if 0
        Можно ждать сколько угодно. В данном случае мы предполагаем, что было бы правиль­
        но воспроизводить видео с частотой 30 кадров в секунду и дать пользователю возмож­
        ность прерывать воспроизведение между кадрами (поэтому мы делаем паузу на 33 мс по­
        сле каждого кадра и ждем нажатия на клавишу). На практике лучше узнать из структуры
        cv::VideoCapture истинную частоту кадров (подробнее см. главу 8).
#endif
    }
    return 0;
}
