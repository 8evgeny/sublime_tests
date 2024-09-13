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
int num_iterations = 10;
bool write_result_inference_in_file = true;
bool input_data_from_mat_or_image = true; //true - from mat  false - from image
Mat img_orig;
high_resolution_clock::time_point time_start_inference, time_end_inference, time_start_iterations, time_end_iterations;
vector<tr> vtr;
rknn_app_context_t rknn_app_ctx;
image_buffer_t src_image;
object_detect_result_list od_results;

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

void results_print_and_save(object_detect_result_list & od_results, image_buffer_t & src_image)
{
    for (int i = 0; i < od_results.count; i++)
    {
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
        draw_rectangle(&src_image, x1, y1, x2 - x1, y2 - y1, COLOR_BLUE, 3);
        char text[256];
        sprintf(text, "%s %.1f%%", class_to_name(det_result->cls_id), det_result->prop * 100);
        draw_text(&src_image, text, x1, y1 - 20, COLOR_RED, 10);
    }//END for (int i = 0; i < od_results.count; i++)

    printf("\n");
    if (write_result_inference_in_file)
        write_image("out.png", &src_image);
}//END void results_print_and_save

void results_save_to_vector(object_detect_result_list & od_results, image_buffer_t & src_image, vector<tr>& vtr)
{
    for (int i = 0; i < od_results.count; i++)
    {
        auto time_inference = duration_cast<microseconds>(time_end_inference - time_start_inference);
        tr tr;
        object_detect_result *det_result = &(od_results.results[i]);
        int x1 = det_result->box.left;
        int y1 = det_result->box.top;
        int x2 = det_result->box.right;
        int y2 = det_result->box.bottom;
        tr.xy = Point2f(x1 + (x2 - x1)/2, y1 + (y2 - y1)/2);
        tr.wh_2 = Point2f((x2 - x1)/2, (y2 - y1)/2);
        tr.class_num = det_result->cls_id;
        tr.tp = time_inference.count();
        vtr.push_back(tr);

    }//END for (int i = 0; i < od_results.count; i++)

} // END void results_save_to_vector

void release_resources(rknn_app_context_t & rknn_app_ctx, image_buffer_t & src_image)
{
    deinit_post_process();
    int ret = release_yolov8_model(&rknn_app_ctx);
    if (ret != 0)
        printf("release_yolov8_model fail! ret=%d\n", ret);

    if (!input_data_from_mat_or_image)
    {
        if (src_image.virt_addr != NULL)
        {
            free(src_image.virt_addr);
        }
    }//END if (!input_data_from_mat_or_image)
}//END void release_resources

int load_data(const char * image_path)
{
    int ret = 0;
    if(input_data_from_mat_or_image)
    {
        img_orig = imread(image_path, IMREAD_UNCHANGED);
//        imshow("image", img_orig);
//        waitKey(0);
    }


    if (!input_data_from_mat_or_image)// Input Image file
    {
        ret = read_image(image_path, &src_image);
        if (ret != 0)
        {
            printf("read image fail! ret=%d image_path=%s\n", ret, image_path);
            release_resources(rknn_app_ctx, src_image);
            return -1;
        }//END if (ret != 0)
    }//END if (!input_data_from_mat_or_image)
    return ret;
}

void init_RKNN()
{
    memset(&rknn_app_ctx, 0, sizeof(rknn_app_context_t));
    init_post_process();
    memset(&src_image, 0, sizeof(image_buffer_t));
    int ret = init_yolov8_model(model_path, &rknn_app_ctx);
    if (ret != 0)
    {
        printf("init_yolov8_model fail! ret=%d model_path=%s\n", ret, model_path);
        release_resources(rknn_app_ctx, src_image);
    }//END if (ret != 0)
    if (input_data_from_mat_or_image)// Input Mat
    {
        src_image.width = 256;
        src_image.height = 256;
        src_image.format = IMAGE_FORMAT_RGB888;
        src_image.virt_addr = img_orig.data;
        src_image.size=196608;
    }//END if (input_data_from_mat_or_image)
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("error image_path\n");
        return -1;
    }

    load_data(argv[1]);

    init_RKNN();

    int ret = 0;
    time_start_iterations = high_resolution_clock::now();
    for (int i = 0; i < num_iterations; ++i)
    {
        time_start_inference = high_resolution_clock::now();
        ret = inference_yolov8_model(&rknn_app_ctx, &src_image, &od_results);  if (ret != 0) {printf("init_yolov8_model fail! ret=%d\n", ret); release_resources(rknn_app_ctx, src_image);  return -1; }
        time_end_inference = high_resolution_clock::now();
        results_save_to_vector(od_results, src_image, vtr);
    }//END for (int i = 0; i < num_iterations; ++i)
    time_end_iterations = high_resolution_clock::now();
    auto time_iterations = duration_cast<microseconds>(time_end_iterations - time_start_iterations);

    printf("\nnum_iterations = %d\ntime_inference = %.2f ms \n\n", num_iterations, (float)time_iterations.count()/(1000 * num_iterations) );
    results_print_and_save(od_results, src_image);
    release_resources(rknn_app_ctx, src_image);

    return 0;
}
