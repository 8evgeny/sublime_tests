#pragma once
#include <opencv2/core/utility.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/core/cvdef.h"

#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>
#include <string>
#include <condition_variable>
#include <mutex>
#include <map>
#include <list>
#include <thread>
#include <future>
#include <dirent.h>
#include "INIReader.h"

#include TRAC_API
#include TRT_API

class trac_tmml
{
 public:
   trac_tmml(){}
   trac_tmml(const std::string& config_path, bool& ok); // -- Конструктор
   ~trac_tmml();

   bool init_copter_scan(const char* config_path);
   int work();

   std::list<trac_st> ltrac; // лист траков.
   trac_struct trac_str;
   std::unique_ptr<trac_struct> ts = nullptr; // Структура трекинга.
   std::unique_ptr<std::list<trac_st>> ltrac_ptr = nullptr;

   std::unique_ptr<trt_detector::YOLO_TRT_Detector> yolo_trt = nullptr;
   std::unique_ptr<trt_detector::YOLO_TRT_Detector> yolo_trt_track = nullptr;

   cv::Mat img_orig, img_orig_roi; // Матрицы для оригинального кадра и для ROI из оригинального кадра.
   cv::Rect2f rct_local_orig; // Рект для ROI на оригинальном кадре.

   int fr_w0 = 0, fr_h0 = 0;
   cv::Point scan_left_top{0, 0}; // Координаты левого-верхнего угла рамки при сканировании объекта.
   int img_orig_type = 0;
   int change_color = -1;
   int color_channels = 0, color_channels_track = 0;
   float fr_w0_1, fr_h0_1;

   int scan_x = 8;
   int scan_y = 5;
   int N_point_scan = scan_x * scan_y;
   int N_point_scan_1 = N_point_scan - 1;
   std::vector<cv::Point> v_point_scan;
   int i_point_scan = 0;
   int trt_enable = 1;
   int cfg_w, cfg_h;
   int max_objects = -1;

 private:
   cv::Point2f p00{0, 0}; // Нулевая точка.
   float tresh = 0, tresh_track = 0;
   cv::Point2f copter_point; // Безразмерные координаты коптера.
   string cfg_way, cfg_way_track, weights_way, weights_way_track, weights_rt_batch1_way, weights_rt_batch1_track_way;
   size_t work_number = 0; // Текущий номер обрабатываемого кадра.
   const int find_obj_min = -2; // Минимальное значение признака трекинга объекта (для ограничения параметра find_obj).
   const int find_obj_min1 = find_obj_min + 1;
   const int find_obj_max = 10; // Максимальное значение признака трекинга объекта (для ограничения параметра find_obj).
   int find_obj = find_obj_min; // Признак трекинга объекта.   
   int scan_ok = 0;
   int num_fr_0, num_fr_1;
   int rotate_frame_180 = 1;
   int fr_w0_2, fr_h0_2, fr_h0_22;
   std::vector<int> vclass, vclass_track;
   std::string vclass_str, vclass_str_track;
   char rait_init = 3;
   float deflect_min = 10;
   float deflect_min2 = deflect_min*deflect_min;
   float deflect_max = 30;
   int deflect_max2 = deflect_max*deflect_max;
   cv::Point cfg_wh;
   cv::Point2f cfg_wh_2, obj_wh_2;
   cv::Point2f object_relative = p00; // Безразмерные координаты центра объекта относительно центра фрейма.
   cv::Point2f cent_obj_rel_default{0.5, 0.5};
   cv::Point2f cent_obj_rel = cent_obj_rel_default;
   std::string yolo_block, yolo_block_track;
   int class_num_musor = -1;
   int min_object_pix = 0, min_object_pix2 = 0;
   int object_num = 0;
   int cout_num = 0;

   // --------- Структура для трекинга цели:   
   int trac_predict_min = 5; // Минимальная длина трека с которой включается экстраполяция трека.
   int trac_max = 6; // Максимальная длина трека, после которой из трека удаляется последний элемент.
   float dist_max = 64; // Максимальное расстояние между текущим и предыдущим объектом.
   float dist_max2 = dist_max * dist_max; // Максимальный квадрат расстояния между текущим и предыдущим объектом (для find_object return).
   float diff_area_max = 0.5;

   // -- Для Калмана:
   const float noise_proc = 0.00001; // Шум процесса.
   const float noise_measurement = 0.01; // Шум измерения.
   const float err_renew = 0.01; // Обновление ошибки ковариации.
   const float dt_tr = 1000; // Время запаздывания для сглаживания траекторий (пропорционально качеству сглаживания Калмана).
   const float dt_tr_1 = 1.f/dt_tr;
   cv::Mat est_x, est_y, pred_x, pred_y;
   cv::KalmanFilter KF_tr_x{4, 2, 0};
   cv::KalmanFilter KF_tr_y{4, 2, 0};
   cv::Mat_<float> measurement_tr_x{2, 1};
   cv::Mat_<float> measurement_tr_y{2, 1};
   cv::Point2f kalman = p00;
   cv::Point2f kalman_old = p00;
   cv::Point2f kalman_old_old = p00;
   double tp_kalman = 0, tp_kalman_old = 0, tp_kalman_old_old = 0;
   float time_sum = 0;
   int num_yolo = 0;
   int N_start_count = 300;
   // -- END для Калмана.

   // Остальные параметры:
   bool first_frame = 1;
   int object_ok = 0;
   int yolo_ok = 0;
   int notfirst_big_x = 0;
   int notfirst_small_x = 0;
   int notfirst_left_x = 0;
   int pix_cross_min, crop_num_x, crop_num_y, pix_cross_x, pix_cross_y;
   std::chrono::duration<double> duration1, duration2, duration3, duration_now; // Продолжительность времени в секундах.
   std::chrono::system_clock::time_point time_point_new, time_begin, time_point_first, time_point_now, time_point_old, tp_scan_old, tp_scan_new; // Временные точки для нахождения времени обработки кадра.
   int next_str = 0; // Признак перехода сканирования на следующую строку.
   int last_str = 0; // Признак последней строки.
   string data_way, data_way_track, cfg, cfg_track, weights, weights_track, weights_rt_batch1, weights_rt_batch1_track;
   float y_scan_max, work_h_w, min_deflect, max_deflect, cfg_w_2, cfg_h_2;
   int shift_x, shift_y, fr_w1, fr_h1, fr_h2, x_scan_max2, y_scan_max2, y_scan_max0, y_scan_max1, y_max0, class_num;
   int batchsize = 1, batchsize_track = 1;

   int fr_min = 5;
   int fr_w_max, fr_h_max;
   static const int Polinom_size = 2;
   double Polinom_koef_x[Polinom_size];
   double Polinom_koef_y[Polinom_size];
   char rait_max = 50; // Максимальный рейтинг у объекта.
   std::string switcher_way = "../switcher.txt";

   bool get_cmd_result(const string& get_disk_id, const std::vector<string>& v_disc_id);
   bool get_predict(const std::list<tr>& trac, cv::Point2f& predict);
   bool get_mnk_predict(const std::list<tr>& trac, cv::Point2f& predict);
   bool get_kalman_predict(const std::list<tr>& trac, cv::Point2f& predict);
   void correct_copter_trac(std::list<trac_st>::iterator& obj);
   double power(double x, int pw);
   int get_abc(int K, double* vec_t, double* vec_y, int vec_size, double* B);
   bool get_polinom(const std::list<tr>& lt, double time_now);
   void get_list_objects();
   bool FileIsExist(const string& filePath);
   bool get_ini_params(const string& config);
   void find_candidates();
   bool get_ini_params4yolo(const std::string& config);
   bool init_yolo(const char* config_path);
   void yolo_work(const cv::Point& left_top, std::vector<tr>& vtr);
   void yolo_work_track(const cv::Point& left_top, std::vector<tr>& vtr);
}; // -- END trac_tmml


