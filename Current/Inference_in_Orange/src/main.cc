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
int num_iterations = 100;

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


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("error image_path\n");
        return -1;
    }

    Mat img_orig = imread(argv[1], IMREAD_UNCHANGED);
//    imshow("image", img_orig);
//    waitKey(0);



    const char *image_path = argv[1];
    cout<<"num iterations = "<<num_iterations<<endl;

    high_resolution_clock::time_point time_start, time_end;

    int ret;
    rknn_app_context_t rknn_app_ctx;
    memset(&rknn_app_ctx, 0, sizeof(rknn_app_context_t));

    init_post_process();

    ret = init_yolov8_model(model_path, &rknn_app_ctx);
    if (ret != 0)
    {
        printf("init_yolov8_model fail! ret=%d model_path=%s\n", ret, model_path);
        goto out;
    }

    image_buffer_t src_image;
    memset(&src_image, 0, sizeof(image_buffer_t));

    //    ret = read_image(image_path, &src_image);
    // Replace function read_image -  data from Mat

    src_image.width = 256;
    src_image.height = 256;
    src_image.format = IMAGE_FORMAT_RGB888;
    src_image.virt_addr = img_orig.data;
    src_image.size=196608;


//    printf("width=%d\n"
//           "height=%d\n"
//           "width_stride=%d\n"
//           "height_stride=%d\n"
//           "format=%d\n"
//           "virt_addr=%p\n"
//           "size=%d\n"
//           "fd=%d\n"
//           ,
//           src_image.width,
//           src_image.height,
//           src_image.width_stride,
//           src_image.height_stride,
//           src_image.format,
//           src_image.virt_addr,
//           src_image.size,
//           src_image.fd
//           );


    if (ret != 0)
    {
        printf("read image fail! ret=%d image_path=%s\n", ret, image_path);
        goto out;
    }

    object_detect_result_list od_results;

    time_start = high_resolution_clock::now();

    for (int i = 0; i < num_iterations; ++i)
    {
        ret = inference_yolov8_model(&rknn_app_ctx, &src_image, &od_results);
        if (ret != 0)
        {
            printf("init_yolov8_model fail! ret=%d\n", ret);
            goto out;
        }
    }
    time_end = high_resolution_clock::now();


    // Фреймы и вероятности
    char text[256];
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

        sprintf(text, "%s %.1f%%", class_to_name(det_result->cls_id), det_result->prop * 100);
        draw_text(&src_image, text, x1, y1 - 20, COLOR_RED, 10);
    }

    write_image("out.png", &src_image); //@@@###

out:
    auto time_inference = duration_cast<microseconds>(time_end - time_start);
    printf("time_inference = %.2f ms \n", (float)time_inference.count()/(1000 * num_iterations) );

    deinit_post_process();

    ret = release_yolov8_model(&rknn_app_ctx);
    if (ret != 0)
    {
        printf("release_yolov8_model fail! ret=%d\n", ret);
    }

    if (src_image.virt_addr != NULL)
    {
        free(src_image.virt_addr);
    }

    return 0;
}
