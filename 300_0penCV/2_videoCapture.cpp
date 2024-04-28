#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char **argv)
{
    Mat in_frame, out_frame;
    const char win1[]="Захват...", win2[]="Запись...";
    double fps=30; // Число кадров в секунду
    char file_out[]="../recorded.avi";
    VideoCapture inVid(0); // Открыть камеру по умолчанию
    if (!inVid.isOpened()) { // Проверка ошибок
        cout << "Ошибка! Камера не готова...\n";
        return -1;
    }
    // Получаем ширину и высоту входного видео
    int width = (int)inVid.get(CV_CAP_PROP_FRAME_WIDTH);
    int height = (int)inVid.get(CV_CAP_PROP_FRAME_HEIGHT);
    VideoWriter recVid(file_out,
           CV_FOURCC('D', 'I', 'V', 'X'),
//                       CV_FOURCC('P','I','M','1')    = MPEG-1 codec
//                       CV_FOURCC('M','J','P','G')    = motion-jpeg codec
//                       CV_FOURCC('M', 'P', '4', '2') = MPEG-4.2 codec
//                       CV_FOURCC('D', 'I', 'V', '3') = MPEG-4.3 codec
//                       CV_FOURCC('D', 'I', 'V', 'X') = MPEG-4 codec
//                       CV_FOURCC('U', '2', '6', '3') = H263 codec
//                       CV_FOURCC('I', '2', '6', '3') = H263I codec
//                       CV_FOURCC('F', 'L', 'V', '1') = FLV1 codec
            fps, Size(width, height));
    if (!recVid.isOpened()) {
        cout << "Ошибка! Видеофайл не открыт...\n";
        return -1;
    }
    // Создаем два окна: для исходного и конечного видео
     namedWindow(win1);
     namedWindow(win2);
     moveWindow(win1, 300, 200);
     moveWindow(win2, 1000, 200);
     while (true) {
    // Читаем кадр с камеры (захват и декодирование)
                     inVid >> in_frame;
    // Преобразуем кадр в полутоновый формат
    cvtColor(in_frame, out_frame, COLOR_BGR2GRAY);
    // Записываем кадр в видеофайл (кодирование и сохранение)
    recVid << out_frame;
    imshow(win1, in_frame);  // Показываем кадр в окне
    imshow(win2, out_frame); // Показываем кадр в окне
    if (waitKey(1000/fps) >= 0)
            break;
    }
    inVid.release(); // Закрываем камеру
    return 0;
    }
