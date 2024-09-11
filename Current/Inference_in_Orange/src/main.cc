#include "copter_struct.hpp"


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "yolov8.h"
#include "image_utils.h"
#include "file_utils.h"
#include "image_drawing.h"
#include <chrono>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace chrono;
using namespace cv;

const char *model_path = "model/best.rknn";
int num_iterations = 1;
bool write_result_inference_in_file = false;
bool input_data_from_mat_or_image = true; //true - from mat  false - from image
Mat img_orig;

void yolo_work(const Point& left_top, vector<tr>& vtr)
{

//    Mat img4yolo = img_orig(Rect(left_top.x, left_top.y, 256, 256));
//    if(change_color){cvtColor(img4yolo, img4yolo, change_color);}
//    const vector<tk::dnn::box>& vtrt = yolo_trt->detect(img4yolo);
//    time_point_new = system_clock::now();
//    duration_now = time_point_new - time_point_first;
//    yolo_exec_time = duration_now.count();
//    vtr.reserve(vtrt.size());
//    for(int i_trt=0; i_trt < vtrt.size(); i_trt++)
//    {
//        const tk::dnn::box& trt_i = vtrt[i_trt];
//        int cls = vclass[trt_i.cl];
//        int object_pix2 = trt_i.w*trt_i.h;
//        if(cls != class_num_musor && trt_i.w*trt_i.h > min_object_pix2)
//        {
//           Point2f wh_2(0.5*trt_i.w, 0.5*trt_i.h);
//           Point2f xy = wh_2 + Point2f(left_top.x + trt_i.x, left_top.y + trt_i.y);
//           duration_now = time_point_new - time_begin;
//           vtr.emplace_back(tr{xy, wh_2, cls, duration_now.count()});
//        } // -- END if(cls != class_num_musor && object_pix2 > min_object_pix2)
//    } // -- END for(int i_trt=0; i_trt < vtrt.size(); i_trt++)
} // -- END yolo_work

void print_results(object_detect_result_list & od_results, image_buffer_t & src_image)
{
    char text[256];
    vector<tr> vtr;
//    cv::Point2f xy = cv::Point2f(-1.f, -1.f); // Координаты центра объекта.
//    cv::Point2f wh_2 = cv::Point2f(0, 0); // Координаты центра объекта.
//    int class_num = -1; // Номер класса
//    double tp; // Точка времени.
    for (int i = 0; i < od_results.count; i++)
    {
        tr tr;
        object_detect_result *det_result = &(od_results.results[i]);
        printf("%s %d (%d %d %d %d) %.3f\n",
               class_to_name(det_result->cls_id),
               (i + 1),
               det_result->box.left, det_result->box.top,
               det_result->box.right, det_result->box.bottom,
               det_result->prop);
        int x1 = det_result->box.left;
        int y1 = det_result->box.top;
        int x2 = det_result->box.right;
        int y2 = det_result->box.bottom;

        tr.class_num = det_result->cls_id;
        tr.xy = Point2f(x1 + (x2 - x1)/2, y1 + (y2 - y1)/2);
//        tr.wh_2 =

        draw_rectangle(&src_image, x1, y1, x2 - x1, y2 - y1, COLOR_BLUE, 3);

        sprintf(text, "%s %.1f%%", class_to_name(det_result->cls_id), det_result->prop * 100);
        draw_text(&src_image, text, x1, y1 - 20, COLOR_RED, 10);
    }

    printf("\n");
    if (write_result_inference_in_file)
        write_image("out.png", &src_image); //@@@###
}

void release_resources(rknn_app_context_t & rknn_app_ctx, image_buffer_t & src_image)
{

    deinit_post_process();

    int ret = release_yolov8_model(&rknn_app_ctx);
    if (ret != 0)
    {
        printf("release_yolov8_model fail! ret=%d\n", ret);
    }

    if (!input_data_from_mat_or_image)
    {
        if (src_image.virt_addr != NULL)
        {
            free(src_image.virt_addr);
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("error image_path\n");
        return -1;
    }
    const char *image_path = argv[1];

    if(input_data_from_mat_or_image)
    {
        img_orig = imread(image_path, IMREAD_UNCHANGED);
//        imshow("image", img_orig);
//        waitKey(0);
    }

    high_resolution_clock::time_point time_start, time_end;
    int ret;
    rknn_app_context_t rknn_app_ctx;
    memset(&rknn_app_ctx, 0, sizeof(rknn_app_context_t));

    init_post_process();
    image_buffer_t src_image;

    memset(&src_image, 0, sizeof(image_buffer_t));

    ret = init_yolov8_model(model_path, &rknn_app_ctx);
    if (ret != 0)
    {
        printf("init_yolov8_model fail! ret=%d model_path=%s\n", ret, model_path);
        release_resources(rknn_app_ctx, src_image);
    }

    // Replace function read_image -  data from Mat
    if (input_data_from_mat_or_image)
    {
        src_image.width = 256;
        src_image.height = 256;
        src_image.format = IMAGE_FORMAT_RGB888;
        src_image.virt_addr = img_orig.data;
        src_image.size=196608;
    }
    else
    {
        ret = read_image(image_path, &src_image);
        if (ret != 0)
        {
            printf("read image fail! ret=%d image_path=%s\n", ret, image_path);
            release_resources(rknn_app_ctx, src_image);
            return -1;
        }
    }

    object_detect_result_list od_results;
    time_start = high_resolution_clock::now();

    for (int i = 0; i < num_iterations; ++i)
    {
        ret = inference_yolov8_model(&rknn_app_ctx, &src_image, &od_results);
        if (ret != 0)
        {
            printf("init_yolov8_model fail! ret=%d\n", ret);
            release_resources(rknn_app_ctx, src_image);
            return -1;
        }
    }
    time_end = high_resolution_clock::now();
    auto time_inference = duration_cast<microseconds>(time_end - time_start);
    printf("\nnum_iterations = %d\ntime_inference = %.2f ms \n\n", num_iterations, (float)time_inference.count()/(1000 * num_iterations) );

    print_results(od_results, src_image);
    release_resources(rknn_app_ctx, src_image);

    return 0;
}
