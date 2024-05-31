#pragma once
#include <cstdint>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <condition_variable>

#include <opencv2/core/utility.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"


struct tr
{
    cv::Point2f xy = cv::Point2f(-1.f, -1.f); // Координаты центра объекта.
    cv::Point2f wh_2 = cv::Point2f(0, 0); // Координаты центра объекта.
    int class_num = -1; // Номер класса
    double tp; // Точка времени.
};

struct trac_st
{
    int trac_ok = 1; // Признак найденного трака.
    int rait = -10; // Рейтинг трака -- для признака удаления.
    std::list<tr> ltr; // Лист структур для траков (сам трак).
    cv::Point2f predict = cv::Point2f(0,0); // Прогноз точки трака на текущем кадре.
    cv::Point2f wh_2 = cv::Point2f(0,0); // Полу-ширина-высота объекта.
    int cls = -1; // Номер класса трака.
};

struct copter_struct
{
   uint8_t * img_orig_data = nullptr; // Указатель на ptr-данные оригинального cv::Mat изображения.
   int rct_x = 0; // Координата-x левой стороны рамки.
   int rct_y = 0; // Координата-y верхней стороны рамки.
   int new_frame = 1; // Признак нового кадра.
   float scan_exec_time = 0; // Частота сканирования кадра.
   float yolo_exec_time = 0; // Средняя частота yolo.
   int work_in_round = 0;
   int switcher = 0;
};
