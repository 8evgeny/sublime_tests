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


struct trac_struct
{
   char key = 0; // Код нажатой клавиши на активном окне при показе изображения.
   uint8_t * tot_show_img_data = nullptr; // Указатель на ptr-данные cv::Mat изображения для показа.
   int tot_show_img_w = 0; // Ширина изображения для показа.
   int tot_show_img_h = 0; // Высота изображения для показа.
   int zahvat = 0; // Признак успешного захвата.
   int rect_ok = 0; // Признак успешного выделения цели мышкой.
   size_t work_number = 0; // Текущий номер рабочего кадра.
   int ok_match = 0; // Признак успешного захвата на текущем кадре.
   int validate = 0; // Степень валидации захвата на текущем кадре.
   int validate_min = 15; // Минимальное значение валидации непрерывного повторения нахождения рамки, после которого поиск считается успешным.
   float obj_xy_x = 0; // Безразмерная x-координата центра цели на текущем кадре (в единицах ширины фрейма).
   float obj_xy_y = 0; // Безразмерная y-координата центра цели на текущем кадре (в единицах высоты фрейма).
   float obj_wh_2_w = 0; // Безразмерная полуширина цели на текущем кадре (в единицах ширины фрейма).
   float obj_wh_2_h = 0; // Безразмерная полувысота цели на текущем кадре (в единицах высоты фрейма).

   int roi = 1; // Признак работы в ROI.
   int roi_l = 0; // Координата левого края roi.
   int roi_t = 0; // Координата верхнего края roi.
   int roi_w = 0; // Ширина roi.
   int roi_h = 0; // Высота roi.

   uint8_t * img_orig_data = nullptr; // Указатель на ptr-данные оригинального cv::Mat изображения.
   int img_orig_type = 0; // Тип cv::Mat оригинального изображения.
   int fr_w0 = 0; // Ширина оригинального кадра.
   int fr_h0 = 0; // Высота оригинального кадра.
   int id = 0; // Номер цели выполняемого алгоритма.
   int new_frame = 1; // Признак формирования нового кадра.
   float scan_exec_time = 0; // Частота сканирования кадра.
   float yolo_exec_time = 0; // Средняя частота yolo.
   int work_in_round = 0; // Признак работы в круге (1), или в прямоугольнике (0).
}; // END trac_struct
