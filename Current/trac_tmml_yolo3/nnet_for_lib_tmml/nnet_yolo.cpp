#pragma once
#include "copter_scan.hpp"
#include YOLO_API

using namespace std;
using namespace cv;
using namespace chrono;

std::unique_ptr<Detector> yolo = nullptr;
std::unique_ptr<Detector> yolo_track = nullptr;


bool trac_tmml::get_ini_params4yolo(const string& config_path)
{
    cout << "BEGIN get_ini_params4yolo for YOLO" << endl;
    if(!FileIsExist(config_path)){cout << "File '" << config_path << "' not exist!" << endl; return 0;}
    setlocale( LC_ALL, "en-US" );
    INIReader reader(config_path);
    if(reader.ParseError()<0){cout << "Can't load '" << config_path << "'\n"; return 0;}

    // ------------------------------------ yolo_block:

    data_way = reader.Get(yolo_block, "data_way", "oops");
    if(data_way == "oops"){cout << "data_way not declared!\n"; return 0;}
    else{cout << "data_way = '" << data_way << "';\n";}

    cfg = reader.Get(yolo_block, "cfg", "oops");
    if(cfg == "oops"){cout << "cfg not declared!\n"; return 0;}
    else{cout << "cfg = '" << cfg << "';\n";}
    cfg_way = data_way + "/" + cfg;

    weights = reader.Get(yolo_block, "weights", "oops");
    if(weights == "oops"){cout << "weights not declared!\n"; return 0;}
    else{cout << "weights = '" << weights << "';\n";}
    weights_way = data_way + "/" + weights;

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
        string cls_str = vclass_str.substr(pos0, 1+pos1-pos0);
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

    weights_track = reader.Get(yolo_block_track, "weights", "oops");
    if(weights_track == "oops"){cout << "weights_track not declared!\n"; return 0;}
    else{cout << "weights_track = '" << weights_track << "';\n";}
    weights_way_track = data_way_track + "/" + weights_track;

    color_channels_track = reader.GetInteger(yolo_block_track, "color_channels", -1);
    if(color_channels_track == -1){cout << "color_channels_track not declared!\n"; return 0;}
    else{cout << "color_channels_track = " << color_channels_track << ";\n";}
    if(color_channels_track != color_channels){cout << "color_channels_track not != color_channels!\n"; return 0;}

    cfg_track = reader.Get(yolo_block_track, "cfg", "oops");
    if(cfg_track == "oops"){cout << "cfg_track not declared!\n"; return 0;}
    else{cout << "cfg_track = '" << cfg_track << "';\n";}
    cfg_way_track = data_way_track + "/" + cfg_track;

    tresh_track = reader.GetReal(yolo_block_track, "tresh", -1);
    if(tresh_track == -1){cout << "tresh_track not declared!\n"; return 0;}
    else{cout << "tresh_track = " << tresh_track << ";\n";}

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

    cout << "END get_ini_params4yolo for YOLO" << endl;
    return 1;
} // -- END get_ini_params4yolo


bool trac_tmml::init_yolo(const char* config_path)
{
   cout << "----------------------------- DEFINE YOLO_ENABLE" << endl;

   bool ok = get_ini_params4yolo(config_path);
   if(!ok){cout << "NOT OK for get_ini_params4yolo!" << endl; return 0;}

   #ifdef YOLO_v4
      cout << "----------------------------- DEFINE YOLO_V4" << endl;
   #endif
   #ifdef YOLO_v3
      cout << "----------------------------- DEFINE YOLO_V3" << endl;
   #endif
   if(!FileIsExist(weights_way))
   {
      cout << "============================== FILE weights_way=" << weights_way << " NOT FOUND!" << endl;
      return 0;
   }
   if(!FileIsExist(cfg_way))
   {
      cout << "============================== FILE cfg_way=" << cfg_way << " NOT FOUND!" << endl;
      return 0;
   }
   yolo = make_unique<Detector>(cfg_way, weights_way);

   if(!FileIsExist(weights_way_track))
   {
      cout << "============================== FILE weights_way_track=" << weights_way_track << " NOT FOUND!" << endl;
      return 0;
   }
   if(!FileIsExist(cfg_way_track))
   {
      cout << "============================== FILE cfg_way_track=" << cfg_way_track << " NOT FOUND!" << endl;
      return 0;
   }
   yolo_track = make_unique<Detector>(cfg_way_track, weights_way_track);
   return 1;
} // -- END init_yolo


void trac_tmml::yolo_work(const Point& left_top, vector<tr>& vtr)
{
    time_point_first = system_clock::now();
    Mat img4yolo = img_orig(Rect(left_top.x, left_top.y, cfg_w, cfg_h));
    if(change_color){cvtColor(img4yolo, img4yolo, change_color);}
    const vector<bbox_t>& vbb = yolo->detect(img4yolo, tresh);
    time_point_new = system_clock::now();
    duration_now = time_point_new - time_point_first;
    yolo_exec_time = duration_now.count();
    vtr.reserve(vbb.size());
    for(int i_bb=0; i_bb < vbb.size(); i_bb++)
    {
        const bbox_t& bb_i = vbb[i_bb];
        int cls = vclass[bb_i.obj_id];
        int object_pix2 = bb_i.w*bb_i.h;
        if(cls != class_num_musor && object_pix2 > min_object_pix2)
        {
           Point2f wh_2(0.5*bb_i.w, 0.5*bb_i.h);
           Point2f xy = wh_2 + Point2f(left_top.x + bb_i.x, left_top.y + bb_i.y);
           duration_now = time_point_new - time_begin;
           vtr.emplace_back(tr{xy, wh_2, cls, duration_now.count()});
        } // -- END if(cls != class_num_musor && object_pix2 > min_object_pix2)
    } // -- END for(int i_bb=0; i_bb < vbb.size(); i_bb++)
} // -- END yolo_work


void trac_tmml::yolo_work_track(const Point& left_top, vector<tr>& vtr)
{
    time_point_first = system_clock::now();
    Mat img4yolo = img_orig(Rect(left_top.x, left_top.y, cfg_w, cfg_h));
    if(change_color){cvtColor(img4yolo, img4yolo, change_color);}
    const vector<bbox_t>& vbb = yolo_track->detect(img4yolo, tresh);
    time_point_new = system_clock::now();
    duration_now = time_point_new - time_point_first;
    yolo_exec_time = duration_now.count();
    vtr.reserve(vbb.size());
    for(int i_bb=0; i_bb < vbb.size(); i_bb++)
    {
        const bbox_t& bb_i = vbb[i_bb];
        int cls = vclass_track[bb_i.obj_id];
        int object_pix2 = bb_i.w*bb_i.h;
        if(cls != class_num_musor && object_pix2 > min_object_pix2)
        {
           Point2f wh_2(0.5*bb_i.w, 0.5*bb_i.h);
           Point2f xy = wh_2 + Point2f(left_top.x + bb_i.x, left_top.y + bb_i.y);
           duration_now = time_point_new - time_begin;
           vtr.emplace_back(tr{xy, wh_2, cls, duration_now.count()});
        } // -- END if(cls != class_num_musor && object_pix2 > min_object_pix2)
    } // -- END for(int i_bb=0; i_bb < vbb.size(); i_bb++)
} // -- END yolo_work_track
