#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include <iostream>
//#include <fstream>
using namespace std;

int main( int argc, char** argv ) {
    cv::Mat image = cv::imread(argv[1],-1);
    cv::namedWindow( "Example2_5-in", cv::WINDOW_AUTOSIZE );
    cv::namedWindow( "Example2_5-out", cv::WINDOW_AUTOSIZE );
    cv::imshow( "Example2_5-in", image );
    cv::Mat out;
//Сглаживаем
//    GaussianBlur(), blur(), medianBlur() bilateralFilter()
//    cv::GaussianBlur(image, out, cv::Size(5,5), 3, 3);
    cv::GaussianBlur(image, out, cv::Size(11,11), 3, 3);
    cv::GaussianBlur( out, out, cv::Size(11,11), 3, 3);
#if 0
    Сначала исходное изображение размыва­ется гауссовым сверточным фильтром размера 5x5,
    и результат записывается в out. Размеры гауссова ядра всегда должны быть нечетными,
    поскольку это ядро (его раз­мер задан с помощью объекта c v ::Size(5,5))
    вычисляется относительно центрально­го пикселя в указанной области.
#endif
    cv::imshow( "Example2_5-out", out );
    cv::moveWindow("Example2_5-in", 300, 50);
    cv::moveWindow("Example2_5-out", 1000, 50);
    cv::waitKey( 0 );
    return(0);
}
