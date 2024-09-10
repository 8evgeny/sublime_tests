// Copyright (c) 2023 by Rockchip Electronics Co., Ltd. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*-------------------------------------------
                Includes
-------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "yolov8.h"
#include "image_utils.h"
#include "file_utils.h"
#include "image_drawing.h"
#include <chrono>

//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/opencv.hpp"

using namespace std;
using namespace chrono;

//#if defined(RV1106_1103)
//    #include "dma_alloc.hpp"
//#endif

/*-------------------------------------------
                  Main Function
-------------------------------------------*/
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("%s <model_path> <image_path>\n", argv[0]);
        return -1;
    }
    high_resolution_clock::time_point time_start, time_end;

    int num_iterations = 1000;

    const char *model_path = argv[1];
    const char *image_path = argv[2];

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

    ret = read_image(image_path, &src_image);

    printf("width=%d\n"
           "height=%d\n"
           "width_stride=%d\n"
           "height_stride=%d\n"
           "format=%d\n"
           "virt_addr=%p\n"
           "size=%d\n"
           "fd=%d\n"
           ,
           src_image.width,
           src_image.height,
           src_image.width_stride,
           src_image.height_stride,
           src_image.format,
           src_image.virt_addr,
           src_image.size,
           src_image.fd

           );


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
    }
    time_end = high_resolution_clock::now();



    if (ret != 0)
    {
        printf("init_yolov8_model fail! ret=%d\n", ret);
        goto out;
    }



    // 画框和概率
    char text[256];
    for (int i = 0; i < od_results.count; i++)
    {
        object_detect_result *det_result = &(od_results.results[i]);
        printf("%s @ (%d %d %d %d) %.3f\n", coco_cls_to_name(det_result->cls_id),
               det_result->box.left, det_result->box.top,
               det_result->box.right, det_result->box.bottom,
               det_result->prop);
        int x1 = det_result->box.left;
        int y1 = det_result->box.top;
        int x2 = det_result->box.right;
        int y2 = det_result->box.bottom;

        draw_rectangle(&src_image, x1, y1, x2 - x1, y2 - y1, COLOR_BLUE, 3);

        sprintf(text, "%s %.1f%%", coco_cls_to_name(det_result->cls_id), det_result->prop * 100);
        draw_text(&src_image, text, x1, y1 - 20, COLOR_RED, 10);
    }

//    write_image("out.png", &src_image); //@@@###

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
