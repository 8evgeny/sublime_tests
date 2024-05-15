#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char **argv)
{
    Mat in_frame, out_frame;
    Mat in_frame2, out_frame2;
    const char win1[]="Захват1", win2[]="Запись1";
    const char win3[]="Захват2", win4[]="Запись2";
    double fps=30; // Число кадров в секунду
    char file_out[]="../recorded.avi";
    char file_out2[]="../recorded2.avi";
    VideoCapture inVid(2); // Открыть камеру по умолчанию
    VideoCapture inVid2(0);

    if (!inVid.isOpened()) { // Проверка ошибок
        cout << "Ошибка! Камера не готова...\n";
        return -1;
    }
    // Получаем ширину и высоту входного видео
    int width = (int)inVid.get(CV_CAP_PROP_FRAME_WIDTH);
    int height = (int)inVid.get(CV_CAP_PROP_FRAME_HEIGHT);
    int width2 = (int)inVid2.get(CV_CAP_PROP_FRAME_WIDTH);
    int height2 = (int)inVid2.get(CV_CAP_PROP_FRAME_HEIGHT);
    VideoWriter recVid(file_out,
           CV_FOURCC('D', 'I', 'V', 'X'),
//                       CV_FOURCC('P','I','M','1')    = MPEG-1 codec
//                       CV_FOURCC('M','J','P','G')    = motion-jpeg codec
//                       CV_FOURCC('M', 'P', '4', '2'),// = MPEG-4.2 codec
//                       CV_FOURCC('D', 'I', 'V', '3') = MPEG-4.3 codec
//                       CV_FOURCC('D', 'I', 'V', 'X') = MPEG-4 codec
//                       CV_FOURCC('U', '2', '6', '3'),// = H263 codec
//                       CV_FOURCC('I', '2', '6', '3') = H263I codec
//                       CV_FOURCC('F', 'L', 'V', '1') = FLV1 codec
            fps, Size(width, height));
    VideoWriter recVid2(file_out2,
           CV_FOURCC('D', 'I', 'V', 'X'),
//                       CV_FOURCC('P','I','M','1')    = MPEG-1 codec
//                       CV_FOURCC('M','J','P','G')    = motion-jpeg codec
//                       CV_FOURCC('M', 'P', '4', '2') = MPEG-4.2 codec
//                       CV_FOURCC('D', 'I', 'V', '3') = MPEG-4.3 codec
//                       CV_FOURCC('D', 'I', 'V', 'X') = MPEG-4 codec
//                       CV_FOURCC('U', '2', '6', '3') = H263 codec
//                       CV_FOURCC('I', '2', '6', '3') = H263I codec
//                       CV_FOURCC('F', 'L', 'V', '1') = FLV1 codec
            fps, Size(width2, height2));
    if (!recVid.isOpened()) {
        cout << "Ошибка! Видеофайл не открыт...\n";
        return -1;
    }
    if (!recVid2.isOpened()) {
        cout << "Ошибка! Видеофайл не открыт...\n";
        return -1;
    }
    // Создаем два окна: для исходного и конечного видео
     namedWindow(win1);
     namedWindow(win2);
     namedWindow(win3);
     namedWindow(win4);
     moveWindow(win1, 300, 0);
     moveWindow(win2, 1000, 0);
     moveWindow(win3, 300, 800);
     moveWindow(win4, 1000, 800);
     while (true) {
    // Читаем кадр с камеры (захват и декодирование)
                     inVid >> in_frame;
                     inVid2 >> in_frame2;
    // Преобразуем кадр
    cvtColor(in_frame, out_frame, COLOR_BGR2GRAY);
    cvtColor(in_frame2, out_frame2, COLOR_BGR2HSV);
//    cvtColor(in_frame, out_frame, COLOR_BGR2HSV);
//    cvtColor(in_frame, out_frame, COLOR_BGR2Lab);
//    cvtColor(in_frame, out_frame, COLOR_BGR2HLS);

    // Записываем кадр в видеофайл (кодирование и сохранение)
    recVid << out_frame;  //Пока не пишет
    recVid2 << out_frame2;
//    recVid.write(out_frame);
    imshow(win1, in_frame);  // Показываем кадр в окне
    imshow(win2, out_frame);
    imshow(win3, in_frame2);
    imshow(win4, out_frame2);
    if (waitKey(1000/fps) >= 0)
            break;
    }
    inVid.release(); // Закрываем камеру
    return 0;
    }
