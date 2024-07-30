#pragma once
#ifndef trac_tmml_H
#define trac_tmml_H

#include <opencv2/core/utility.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/video/tracking.hpp"

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <cmath>
#include <memory>
#include <stdio.h>
#include <fstream>
#include <chrono>
#include <cmath>
#include <string>
#include <condition_variable>
#include <mutex>
#include <map>
#include <list>
#include <deque>
#include <thread>
#include <future>
#include <dirent.h>
#include "INIReader.h"

#if defined OPEN_CL
   #include "tmml_cl.hpp"
#endif // END #if defined OPEN_CL
#if defined USE_CUDA || defined NO_GPU
   #include "tmml.hpp"
#endif // END defined USE_CUDA

#include TRACK_API

class trac_tmml
{
  public:
    trac_tmml(const std::string& config_path, bool& ok);
    ~trac_tmml();

    int work();
    void deinit();

    std::unique_ptr<trac_struct> ts = nullptr; // Структура трекинга.

 #if defined OPEN_CL
    std::unique_ptr<tmml_cl> tm = nullptr;
 #endif // END #if defined OPEN_CL
 #if !defined OPEN_CL
    std::unique_ptr<tmml> tm = nullptr;
 #endif // END !defined OPEN_CL

    int fr_w0, fr_h0; // Ширина и высота оригинального кадра.
    cv::Mat img_orig, img_orig_roi; // Матрицы для оригинального кадра и для ROI из оригинального кадра.
    cv::Rect2f rct_local_orig; // Рект для ROI на оригинальном кадре.
    double maxVal = 0;

 private:    
    int camera_on = 0; // (0) -- работа из папки с изображениями, (1) -- работа от LAN-камеры, (2) -- видеофайл, или веб-камера.
    int gray = 1; // Оттенки серого (1), BRG (0).
    int work_number_rel = 0;
    const float not_ok_match_count_max = 3.f; // Максимальное время после потери захвата в секундах, после которого захват сбрасывается (deinit()).
    bool not_ok_match = 0;
    bool first_img = 1;
    int img_orig_type = CV_8UC1;
    std::list<cv::Mat> list_et;

    int validate_ext = -50; // Значение валидации, ниже которой происходит расширение рамки поиска.
    const float object_relative_max = 0.49; // Максимальное значение безразмерной координаты объекта при захвате.
    bool renew = 0;
    bool shift_ok = 0;
    int num_frame_ok = 0;
    int rotate_frame_180 = 1;
    cv::Mat img_et, et, img_local_work;
    int scaling = 0; // Включить, или нет масштабирование.
    int list_et_sz = 16; // Максимальное число сохраняемых эталонов.
    int k_renew_ok = 5; // Число кадров, пропускаемых перед сохранением эталона.
    int k_renew = k_renew_ok;

    const float w_2_et = 24; // Полуширина стороны квадрата для эталона на рабочем фрейме.
    const float w_et = 2.f*w_2_et; // Ширина стороны квадрата для эталона на рабочем фрейме.
    cv::Point2f wh_2_0 = cv::Point2f(w_2_et, w_2_et);
    cv::Point2f wh_et_2 = wh_2_0;
    cv::Size wh_et = cv::Size(2*wh_et_2.x, 2*wh_et_2.y);

    float orig_work, work_orig, work_orig_2, min_max_Val, min_max_Val2, fr_w0_1, fr_h0_1;
    int fr_h_work, num_fr_0, num_fr_1, fr_w_work;
    cv::Point2f aim_center, aim_center_prev;
    cv::Point2f p__  = cv::Point2f(-1000, -1000);
    cv::Point2f center = p__, center_prev = p__, wh_sm_2, center_sm, local_center_tmp, center_kalman;

    const float ext_wh0 = 10; // Расширение рамки локального захвата по умолчанию.
    //float ext_wh = ext_wh0; // Расширение рамки локального захвата.
    const int d_ext_wh = 20; // Максимальное количество увеличений синей рамки, при превышении которого вызывается deinit().
    const int ext_wh1 = ext_wh0 + d_ext_wh; // Максимальное коэффициент увеличения синей рамки, при превышении которого вызывается deinit().
    cv::Rect2f rct_result, rct_result_orig, rct_result_sm;
    cv::Rect rct_local_result;
    string way2init_rect;
    float d02, d020;
    int left_padd, i_fr;
    cv::Size sz_et = cv::Size(48, 48);
    cv::Mat et_prev, result, et_gray, et_prev_gray, flow, img_et_sm, result_sm;

    const float koef_f_midl = 0.1; // Переменная для оптического потока (пока не используется)
    const int wh_sm__2_min = 6; // Размер внутреннего шаблона (маленького)
    const float koef_wh_sm = 0.1; // Для вычисления размеров внутреннего шаблона (маленького) из размеров внешнего шаблона.
    const float min_max_Val_sm = 0.77; // Трешхолд для матчинга шаблона по умолчанию.
    cv::Size wh_local0 = cv::Size(round(ext_wh0*wh_2_0.x) -1, round(ext_wh0*wh_2_0.y) -1);
    int wh_sm__2 = wh_sm__2_min;
    //Point2f wh_local = wh_local0;
    const int win_x = 10; // Отступ окна слева
    const int win_y = 10; // Отступ окна сверху
    cv::Point2f center_orig, wh_et_2_orig, wh_local_orig, lt_local_work;

    // -- Для Калмана:
    const float noise_proc = 1e-4; // Шум процесса.
    const float noise_measurement = 0.1; // Шум измерения.
    const float err_renew = 0.1; // Обновление ошибки ковариации.
    const float dt_tr = 1.f; // Время запаздывания для сглаживания траекторий (пропорционально качеству сглаживания Калмана).
    const float dt_tr_1 = 1.f/dt_tr;
    cv::KalmanFilter KF_tr = cv::KalmanFilter(4, 2, 0);
    cv::Mat_<float> measurement_tr = cv::Mat_<float>(2, 1);
    cv::Mat est, pred;

    double minVal, minVal_sm, maxVal_sm;
    cv::Point minLoc, maxLoc, minLoc_sm, maxLoc_sm;
    cv::Point2f matchLoc, matchLoc_sm;

    float shift2 = 0.004; // Максимальный относительный квадрат смещения текущей рамки от предыдущей

    // Для LK-алгоритма:
    float koef_LK = 1.f; // Отладочный коэффициэнт эффекта масштабирования.
    bool first_match = 1; // Признак первого кадра для LK.
    int N_LK_2 = 32; // Число точек на окружности.
    int N_LK = 2*N_LK_2; // Полное число точек на обеих окружностях.
    std::vector<cv::Point2f> v_angl, v_LK_points; // Вектор косинусов-синусов и вектор точек для LK.
    float rad1 = 0.8; // Относительный радиус первой окружности.
    float rad2 = 0.6; // Относительный радиус второй окружности.
    cv::Point a_2_now; // Полуширина квадрата для текущего кадра.
    int a_2_now_min = 20; // Минимальная полуширина квадрата.
    cv::Mat img4LK_now, img4LK_prev, img_now, img_prev; // Матрицы для LK и для подготовки матриц для LK.
    const cv::Size wsz = cv::Size(7, 7); // Окно сглаживания оптического потока (обратно-пропорционально скорости работы).
    const float dt1_LK = 11.f; // Тёмный параметр, прямо-пропорционален скорости работы.
    const float dt2_LK = 0.001; // Тёмный параметр, обратно-пропорционален скорости работы.

    int smooth_on = 0; // Включение сглаживания.
    struct smoth_trac{float x = 0.5; float y = 0.5; size_t work_number = 0;};
    std::deque<smoth_trac> deq_st;
    int deq_sz_min = 10; // Минимальное число точек на траектории (не меньше 2).
    int Polinom_size  = 2; // Степень полинома интерполяции.
    cv::Mat A, A_inv;

    std::chrono::duration<double> duration1, duration_delay, not_ok_match_duration; // Продолжительность времени между кадрами.
    std::chrono::system_clock::time_point time_point1_old, time_point0, time_point1, not_ok_match_start, not_ok_match_stop; // Временные точки для нахождения времени обработки кадра.
    float duration_delay_fps = 0, max_fps = 0;    

    bool match_img();
    bool get_cmd_result(const string& get_disk_id, const std::vector<string>& v_disc_id);
    bool FileIsExist(const string& filePath);
    bool shift_verify(cv::Point2f& p);
    bool verify_pnt(const cv::Rect2f& rct, const cv::Point2f& p);
    bool verify_rect(const cv::Size& sz, const cv::Rect2f& r);
    void init_work();
    bool get_ini_params(const string& config);
    float get_scale();
    void get_vec_angl();
    void get_vec_LK_points(float a_2);
    bool get_obj_xy_smooth(float obj_xy_x, float obj_xy_y);
    bool get_abc(const std::vector<cv::Point2d>& vec, std::vector<float>& B);
    bool get_smooth_xy(cv::Point2f& extr_xy);
}; // END -- trac_tmml
#endif
