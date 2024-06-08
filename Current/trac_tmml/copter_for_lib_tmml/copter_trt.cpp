#include "copter_scan.hpp"

using namespace std;
using namespace cv;
using namespace chrono;

bool trac_tmml::get_ini_params4yolo(const string& config_path)
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

    weights_rt_batch1 = reader.Get(yolo_block, "weights_rt_batch1", "oops");
    if(weights_rt_batch1 == "oops"){cout << "weights_rt_batch1 not declared!\n"; return 0;}
    else{cout << "weights_rt_batch1 = '" << weights_rt_batch1 << "';\n";}
    weights_rt_batch1_way = data_way + "/" + weights_rt_batch1;

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

    weights_rt_batch1_track = reader.Get(yolo_block_track, "weights_rt_batch1", "oops");
    if(weights_rt_batch1_track == "oops"){cout << "weights_rt_batch1 not declared!\n"; return 0;}
    else{cout << "weights_rt_batch1_track = '" << weights_rt_batch1_track << "';\n";}
    weights_rt_batch1_track_way = data_way_track + "/" + weights_rt_batch1_track;

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


bool trac_tmml::init_yolo(const char* config_path)
{    
   cout << "----------------------------- DEFINE TRT_ENABLE" << endl;

   bool ok = get_ini_params4yolo(config_path);
   if(!ok){cout << "NOT OK for get_ini_params4yolo!" << endl; return 0;}

   if(!FileIsExist(weights_rt_batch1_way))
   {
      cout << "============================== FILE weights_rt_batch1_way=" << weights_rt_batch1_way << " NOT FOUND!" << endl;
      return 0;
   }
   yolo_trt = make_unique<trt_detector::YOLO_TRT_Detector>(weights_rt_batch1_way, tresh, vclass.size());
   batchsize = yolo_trt->getMaxBatchSize();
   if(batchsize != 1)
   {
       cout << "============================== Некорректное значение batchsize=" << batchsize << ", должно быть batchsize=1" << endl;
       return 0;
   }

   if(!FileIsExist(weights_rt_batch1_track_way))
   {
      cout << "============================== FILE weights_rt_batch1_track_way=" << weights_rt_batch1_track_way << " NOT FOUND!" << endl;
      return 0;
   }
   yolo_trt_track = make_unique<trt_detector::YOLO_TRT_Detector>(weights_rt_batch1_track_way, tresh_track, vclass_track.size());
   batchsize_track = yolo_trt_track->getMaxBatchSize();
   if(batchsize_track != 1)
   {
       cout << "============================== Некорректное значение batchsize_track=" << batchsize_track << ", должно быть batchsize=1" << endl;
       return 0;
   }
   return 1;
} // -- END init_yolo


void trac_tmml::yolo_work(const Point& left_top, vector<tr>& vtr)
{
    time_point_first = system_clock::now();
    Mat img4yolo = img_orig(Rect(left_top.x, left_top.y, cfg_w, cfg_h));
    if(change_color){cvtColor(img4yolo, img4yolo, change_color);}
    const vector<tk::dnn::box>& vtrt = yolo_trt->detect(img4yolo);
    time_point_new = system_clock::now();
    duration_now = time_point_new - time_point_first;
    yolo_exec_time = duration_now.count();
    vtr.reserve(vtrt.size());
    for(int i_trt=0; i_trt < vtrt.size(); i_trt++)
    {
        const tk::dnn::box& trt_i = vtrt[i_trt];
        int cls = vclass[trt_i.cl];
        int object_pix2 = trt_i.w*trt_i.h;
        if(cls != class_num_musor && trt_i.w*trt_i.h > min_object_pix2)
        {
           Point2f wh_2(0.5*trt_i.w, 0.5*trt_i.h);           
           Point2f xy = wh_2 + Point2f(left_top.x + trt_i.x, left_top.y + trt_i.y);
           duration_now = time_point_new - time_begin;
           vtr.emplace_back(tr{xy, wh_2, cls, duration_now.count()});
        } // -- END if(cls != class_num_musor && object_pix2 > min_object_pix2)
    } // -- END for(int i_trt=0; i_trt < vtrt.size(); i_trt++)
} // -- END yolo_work


void trac_tmml::yolo_work_track(const Point& left_top, vector<tr>& vtr)
{
    time_point_first = system_clock::now();
    Mat img4yolo = img_orig(Rect(left_top.x, left_top.y, cfg_w, cfg_h));
    if(change_color){cvtColor(img4yolo, img4yolo, change_color);}
    const vector<tk::dnn::box>& vtrt = yolo_trt_track->detect(img4yolo);
    time_point_new = system_clock::now();
    duration_now = time_point_new - time_point_first;
    yolo_exec_time = duration_now.count();
    vtr.reserve(vtrt.size());
    for(int i_trt=0; i_trt < vtrt.size(); i_trt++)
    {
        const tk::dnn::box& trt_i = vtrt[i_trt];
        int cls = vclass_track[trt_i.cl];
        int object_pix2 = trt_i.w*trt_i.h;
        if(cls != class_num_musor && object_pix2 > min_object_pix2)
        {
           Point2f wh_2(0.5*trt_i.w, 0.5*trt_i.h);
           Point2f xy = wh_2 + Point2f(left_top.x + trt_i.x, left_top.y + trt_i.y);
           duration_now = time_point_new - time_begin;
           vtr.emplace_back(tr{xy, wh_2, cls, duration_now.count()});
        } // -- END if(cls != class_num_musor && object_pix2 > min_object_pix2)
    } // -- END for(int i_trt=0; i_trt < vtrt.size(); i_trt++)
} // -- END yolo_work_track
