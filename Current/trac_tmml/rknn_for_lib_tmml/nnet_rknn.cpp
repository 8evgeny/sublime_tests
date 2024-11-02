#include "nnet_scan.hpp"

using namespace std;
using namespace cv;
using namespace chrono;

const char * label_txt_path;
int class_num_obj;
float thras_nms;
float thras_box_conf;

bool nnet::get_ini_params4yolo(const string& config_path)
{
    cout << "BEGIN get_ini_params4yolo for TRT" << endl;
    if(!FileIsExist(config_path)){cout << "File '" << config_path << "' not exist!" << endl; return 0;}
    setlocale( LC_ALL, "en-US" );
    INIReader reader(config_path);
    if(reader.ParseError()<0){cout << "Can't load '" << config_path << "'\n"; return 0;}

    // ================================== yolo_block:

    data_way = reader.Get(yolo_block, "data_way", "oops");
    if(data_way == "oops"){cout << "data_way not declared!\n"; return 0;}
    else{cout << "data_way = '" << data_way << "';\n";}

    classes_file = reader.Get(yolo_block, "classes_file", "oops");
    if(classes_file == "oops"){cout << "error classes_file not declared!!!\n"; return 0;}
    else{cout << "classes_file = '" << classes_file << "';\n";}

    obj_class_num = reader.GetInteger(yolo_block, "obj_class_num", -1);
    if(obj_class_num == -1){cout << "error obj_class_num not declared!!!\n"; return 0;}
    else{cout << "obj_class_num = " << obj_class_num << ";\n";}

    nms_thres = reader.GetReal(yolo_block, "nms_thres", -1);
    if(nms_thres == -1){cout << "nms_thres not declared!\n"; return 0;}
    else{cout << "nms_thres = " << nms_thres << ";\n";}

    color_channels = reader.GetInteger(yolo_block, "color_channels", -1);
    if(color_channels == -1){cout << "color_channels not declared!\n"; return 0;}
    else{cout << "color_channels = " << color_channels << ";\n";}

    cfg_w = reader.GetInteger(yolo_block, "cfg_w", -1);
    if(cfg_w == -1){cout << "cfg_w not declared!\n"; return 0;}
    else{cout << "cfg_w = " << cfg_w << ";\n";}

    cfg_h = reader.GetInteger(yolo_block, "cfg_h", -1);
    if(cfg_h == -1){cout << "cfg_h not declared!\n"; return 0;}
    else{cout << "cfg_h = " << cfg_h << ";\n";}

    tresh = reader.GetReal(yolo_block, "tresh", -1);
    if(tresh == -1){cout << "tresh not declared!\n"; return 0;}
    else{cout << "tresh = " << tresh << ";\n";}

    dist_max = reader.GetReal(yolo_block, "dist_max", -1);
    if(dist_max == -1){cout << "dist_max not declared!\n"; return 0;}
    else{cout << "dist_max = " << dist_max << ";\n";}
    dist_max2 = dist_max*dist_max;

    vclass_str = reader.Get(yolo_block, "vclass", "oops");
    if(vclass_str == "oops"){cout << "vclass_str not declared!\n"; return 0;}
    else{cout << "vclass_str = '" << vclass_str << "';\n";}
    int pos0 = 0;
    while(true)
    {
        int pos1 = vclass_str.find(',', pos0);
        if(pos1 == -1){break;}
        string cls_str = vclass_str.substr(pos0, 1 + pos1 - pos0);
        int cls = stoi(cls_str);
        vclass.emplace_back(cls);
        pos0 = pos1 + 1;
    } // -- END while(true)
    string cls_str = vclass_str.substr(pos0, vclass_str.length());
    int cls = stoi(cls_str);
    vclass.emplace_back(cls);
    for(int i=0; i<vclass.size(); i++){cout << i << " cls=" << vclass[i] << endl;}

    pix_cross_min = reader.GetInteger(yolo_block, "pix_cross_min", -1);
    if(pix_cross_min == -1){cout << "pix_cross_min not declared!\n"; return 0;}
    else{cout << "pix_cross_min = " << pix_cross_min << ";\n";}

    min_object_pix = reader.GetInteger(yolo_block, "min_object_pix", -1);
    if(min_object_pix == -1){cout << "min_object_pix not declared!\n"; return 0;}
    else{cout << "min_object_pix = " << min_object_pix << ";\n";}
    min_object_pix2 = min_object_pix*min_object_pix;

    // ================================== yolo_block_track:

    data_way_track = reader.Get(yolo_block_track, "data_way", "oops");
    if(data_way_track == "oops"){cout << "data_way_track not declared!\n"; return 0;}
    else{cout << "data_way_track = '" << data_way_track << "';\n";}

    tresh_track = reader.GetReal(yolo_block_track, "tresh", -1);
    if(tresh_track == -1){cout << "tresh_track not declared!\n"; return 0;}
    else{cout << "tresh_track = " << tresh_track << ";\n";}

    color_channels_track = reader.GetInteger(yolo_block_track, "color_channels", -1);
    if(color_channels_track == -1){cout << "color_channels_track not declared!\n"; return 0;}
    else{cout << "color_channels_track = " << color_channels_track << ";\n";}
    if(color_channels_track != color_channels){cout << "color_channels_track not != color_channels!\n"; return 0;}

    vclass_str_track = reader.Get(yolo_block_track, "vclass", "oops");
    if(vclass_str_track == "oops"){cout << "vclass_str_track not declared!\n"; return 0;}
    else{cout << "vclass_str_track = '" << vclass_str_track << "';\n";}
    int pos0_track = 0;
    while(true)
    {
        int pos1_track = vclass_str_track.find(',', pos0_track);
        if(pos1_track == -1){break;}
        string cls_str_track = vclass_str_track.substr(pos0_track, 1 + pos1_track - pos0_track);
        int cls_track = stoi(cls_str_track);
        vclass_track.emplace_back(cls_track);
        pos0_track = pos1_track + 1;
    } // -- END while(true)
    string cls_str_track = vclass_str_track.substr(pos0_track, vclass_str_track.length());
    int cls_track = stoi(cls_str_track);
    vclass_track.emplace_back(cls_track);
    for(int i=0; i<vclass_track.size(); i++){cout << i << " cls_track=" << vclass_track[i] << endl;}

    cout << "END get_ini_params4yolo for TRT" << endl;
    return 1;
} // -- END get_ini_params4yolo

bool nnet::init_yolo(const char* config_path)
{    
    bool ok = get_ini_params4yolo(config_path);
    if(!ok){cout << "NOT OK for get_ini_params4yolo!" << endl; return 0;}

    model_path = data_way.c_str();
    label_txt_path = classes_file.c_str();
    class_num_obj = obj_class_num;
    thras_nms = nms_thres;
    thras_box_conf = tresh;

    memset(&rknn_app_ctx, 0, sizeof(rknn_app_context_t));
    init_post_process();
    memset(&img_buff, 0, sizeof(image_buffer_t));
    int ret = init_yolov8_model(model_path, &rknn_app_ctx);
    if(ret != 0)
    {
        printf("init_yolov8_model fail! ret=%d model_path=%s\n", ret, model_path);
        release_resources(rknn_app_ctx, img_buff);
    } //END if(ret != 0)
    img_buff.width = cfg_w;
    img_buff.height = cfg_h;
    if (color_channels == 3)
        img_buff.format = IMAGE_FORMAT_RGB888;
    if (color_channels == 1)
        img_buff.format = IMAGE_FORMAT_GRAY8;
    img_buff.size = cfg_w * cfg_h * color_channels;
    cout << "img_buff.size = "<<img_buff.size<<endl;
    cout << "init_yolo OK\n";
    return 1;
} // -- END init_yolo

void nnet::release_resources(rknn_app_context_t & rknn_app_ctx, image_buffer_t & img_buff)
{
    deinit_post_process();
    int ret = release_yolov8_model(&rknn_app_ctx);
    if (ret != 0)
        printf("release_yolov8_model fail! ret=%d\n", ret);
}//END void release_resources

void nnet::yolo_work(const Point& left_top, vector<tr>& vtr)
{
    time_point_first = system_clock::now();
    Mat img4yolo = img_orig(Rect(left_top.x, left_top.y, cfg_w, cfg_h));
    cvtColor(img4yolo, img4yolo, COLOR_GRAY2BGR);
    img_buff.virt_addr = img4yolo.data;
    int ret = inference_yolov8_model(&rknn_app_ctx, &img_buff, &od_results);
//    if(ret != 0)
//    {
//        printf("init_yolov8_model fail! ret=%d\n", ret);
//        release_resources(rknn_app_ctx, img_buff);
//        return;
//    } // END if(ret != 0)
    time_point_new = system_clock::now();
    duration_now = time_point_new - time_point_first;
    ts->yolo_exec_time = duration_now.count();
    vtr.reserve(od_results.count);
    for(int i_obj=0; i_obj < od_results.count; i_obj++)
    {
        const object_detect_result& obj_i = od_results.results[i_obj];
        char cls = vclass[obj_i.cls_id];
        auto& rct = obj_i.box;
        int w = rct.right - rct.left;
        int h = rct.bottom - rct.top;
        //if(cls != class_num_musor && w * h > min_object_pix2)
        {
            Point2f wh_2(0.5 * w, 0.5 * h);
            Point2f xy(wh_2.x + left_top.x + rct.left, wh_2.y + left_top.y + rct.top);
            duration_now = time_point_new - time_begin;
            vtr.emplace_back(tr{xy, wh_2, cls, duration_now.count()});
        } // -- END if(cls != class_num_musor && object_pix2 > min_object_pix2)
    } // -- END for(int i_obj=0; i_obj < od_results.count; i_obj++)
    //cout << "vtr.size=" << vtr.size() << endl;
} // -- END yolo_work

void nnet::yolo_work_track(const Point& left_top, vector<tr>& vtr)
{
    time_point_first = system_clock::now();
    Mat img4yolo = img_orig(Rect(left_top.x, left_top.y, cfg_w, cfg_h));
    cvtColor(img4yolo, img4yolo, COLOR_GRAY2BGR);
    img_buff.virt_addr = img4yolo.data;
    int ret = inference_yolov8_model(&rknn_app_ctx, &img_buff, &od_results);
//    if(ret != 0)
//    {
//        printf("init_yolov8_model fail! ret=%d\n", ret);
//        release_resources(rknn_app_ctx, img_buff);
//        return;
//    } // END if(ret != 0)
    time_point_new = system_clock::now();
    duration_now = time_point_new - time_point_first;
    ts->yolo_exec_time = duration_now.count();
    vtr.reserve(od_results.count);
    for(int i_obj=0; i_obj < od_results.count; i_obj++)
    {
        const object_detect_result& obj_i = od_results.results[i_obj];
        char cls = vclass[obj_i.cls_id];
        auto& rct = obj_i.box;
        int w = rct.right - rct.left;
        int h = rct.bottom - rct.top;
        //if(cls != class_num_musor && w * h > min_object_pix2)
        {
            Point2f wh_2(0.5 * w, 0.5 * h);
            Point2f xy(wh_2.x + left_top.x + rct.left, wh_2.y + left_top.y + rct.top);
            duration_now = time_point_new - time_begin;
            vtr.emplace_back(tr{xy, wh_2, cls, duration_now.count()});
        } // -- END if(cls != class_num_musor && object_pix2 > min_object_pix2)
    } // -- END for(int i_obj=0; i_obj < od_results.count; i_obj++)
    //cout << "vtr.size=" << vtr.size() << endl;
} // -- END yolo_work_track

