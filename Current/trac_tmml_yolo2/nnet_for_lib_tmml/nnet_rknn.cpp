#include "nnet_scan.hpp"
#include "yolov8.h"

using namespace std;
using namespace cv;
using namespace chrono;

void nnet::init_RKNN()
{
    memset(&rknn_app_ctx, 0, sizeof(rknn_app_context_t));
    init_post_process();
    memset(&img_buff, 0, sizeof(image_buffer_t));
    int ret = init_yolov8_model(model_path, &rknn_app_ctx);
    if (ret != 0)
    {
        printf("init_yolov8_model fail! ret=%d model_path=%s\n", ret, model_path);
        release_resources(rknn_app_ctx, img_buff);
    }//END if (ret != 0)
    img_buff.width = 256;
    img_buff.height = 256;
    img_buff.format = IMAGE_FORMAT_RGB888;
//    img_buff.virt_addr = img_orig.data;
    img_buff.size=196608;
    cout<<"____________init_RKNN OK\n";
}

void nnet::yolo_work(const Point& left_top, vector<tr>& vtr)
{
    cout<<"____________yolo_work\n";
    Mat img4yolo = img_orig(Rect(left_top.x, left_top.y, 256, 256));
    img_buff.virt_addr = img4yolo.data;


    int ret = inference_yolov8_model(&rknn_app_ctx, &img_buff, &od_results);
    if (ret != 0)
    {
     printf("init_yolov8_model fail! ret=%d\n", ret);
     release_resources(rknn_app_ctx, img_buff);
    }
    time_point_new = system_clock::now();
    results_save_to_vector(od_results, img_buff, vtr);

} // -- END yolo_work

void nnet::yolo_work_track(const Point& left_top, vector<tr>& vtr)
{
    cout<<"____________yolo_work_track\n";
    time_point_first = system_clock::now();
    Mat img4yolo = img_orig(Rect(left_top.x, left_top.y, cfg_w, cfg_h));



    if(change_color){cvtColor(img4yolo, img4yolo, change_color);}
//    const vector<tk::dnn::box>& vtrt = yolo_trt_track->detect(img4yolo);
//    time_point_new = system_clock::now();
//    duration_now = time_point_new - time_point_first;
//    ts->yolo_exec_time = duration_now.count();
//    vtr.reserve(vtrt.size());
//    for(int i_trt=0; i_trt < vtrt.size(); i_trt++)
//    {
//        const tk::dnn::box& trt_i = vtrt[i_trt];
//        char cls = vclass_track[trt_i.cl];
//        int object_pix2 = trt_i.w*trt_i.h;
//        if(cls != class_num_musor && object_pix2 > min_object_pix2)
//        {
//           Point2f wh_2(0.5*trt_i.w, 0.5*trt_i.h);
//           Point2f xy = wh_2 + Point2f(left_top.x + trt_i.x, left_top.y + trt_i.y);
//           duration_now = time_point_new - time_begin;
//           vtr.emplace_back(tr{xy, wh_2, cls, duration_now.count()});
//        } // -- END if(cls != class_num_musor && object_pix2 > min_object_pix2)
//    } // -- END for(int i_trt=0; i_trt < vtrt.size(); i_trt++)
} // -- END yolo_work_track



void nnet::results_save_to_vector(object_detect_result_list & od_results, image_buffer_t & img_buff, vector<tr>& vtr)
{
    for (int i = 0; i < od_results.count; i++)
    {
        duration_now = time_point_new - time_point_first;
        tr tr;
        object_detect_result *det_result = &(od_results.results[i]);
        int x1 = det_result->box.left;
        int y1 = det_result->box.top;
        int x2 = det_result->box.right;
        int y2 = det_result->box.bottom;
        tr.xy = Point2f(x1 + (x2 - x1)/2, y1 + (y2 - y1)/2);
        tr.wh_2 = Point2f((x2 - x1)/2, (y2 - y1)/2);
        tr.class_num = det_result->cls_id;
        tr.tp = duration_now.count();
        vtr.push_back(tr);

    }//END for (int i = 0; i < od_results.count; i++)

} // END void results_save_to_vector

void nnet::release_resources(rknn_app_context_t & rknn_app_ctx, image_buffer_t & img_buff)
{
    deinit_post_process();
    int ret = release_yolov8_model(&rknn_app_ctx);
    if (ret != 0)
        printf("release_yolov8_model fail! ret=%d\n", ret);
}//END void release_resources
