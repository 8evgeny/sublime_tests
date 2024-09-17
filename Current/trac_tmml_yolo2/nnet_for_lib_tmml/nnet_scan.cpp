#include "nnet_scan.hpp"

using namespace std;
using namespace cv;
using namespace chrono;

// Конструктор класса nnet.
nnet::nnet(const string& config_path, bool& ok)
{
   cout << "Constructor nnet" << endl;
   // -------------------------- FIND DISC_ID -----------------------------------------------
   #ifdef FIND_DISC_ID
     vector<string> v_disc_id = {
         "114A4G5FS",
         "BTHH83700P5L512D",
         "ZN1BFQHB",
         "Z524F25F",
         "2104A9474309",
         "2J4120178746",
         "WD-WCC6Y6JDRY7P",
         "S4BENG0KC32655V",
         "2L1529A64EGX",
         "2L1529ABGJNP",
         "S3PRD9NP",
         "S649NL0TB45870W",
         "S6F5NJ0RB46088"
     };
     string cmd_result1 = "udevadm info --query=all --name=/dev/sda | grep ID_SERIAL_SHORT";
     string cmd_result2 = "udevadm info --query=all --name=nvme0n1 | grep ID_SERIAL_SHORT";
     string cmd_result3 = "udevadm info --query=all --name=/dev/sdb | grep ID_SERIAL_SHORT";
     string cmd_result4 = "udevadm info --query=all --name=/dev/sdc | grep ID_SERIAL_SHORT";
     ok = get_cmd_result(cmd_result1, v_disc_id);
     if(!ok){ok = get_cmd_result(cmd_result2, v_disc_id);}
     if(!ok){ok = get_cmd_result(cmd_result3, v_disc_id);}
     if(!ok){ok = get_cmd_result(cmd_result4, v_disc_id);}
     if(!ok){cout << "=============== Wrong HARDWARE !" << endl; return;}
   #endif // -------------------------- END FIND DISC_ID -----------------------------------------------
   ok = get_ini_params(config_path);
   if(!ok){cout << "Not get_ini_params!" << endl;}

} // -- END nnet

nnet::~nnet()
{
  cout << "Destructor nnet" << endl;
#ifdef TRT_ENABLE
  yolo_trt.release();
  yolo_trt_track.release();
#endif
  ltrac_ptr.release();
  ts.release();
} // END ~nnet()

bool nnet::get_cmd_result(const string& get_disk_id, const vector<string>& v_disc_id)
{
    array<char, 128> buffer;
    string cmd_result = "";
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(get_disk_id.c_str(), "r"), pclose);
    if(!pipe){throw std::runtime_error("popen() failed!");}
    while(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr){cmd_result += buffer.data();}
    int num_pos = cmd_result.find("=") + 1;
    int len = cmd_result.length() - num_pos - 1;
    string disc_id = cmd_result.substr(num_pos, len);
    bool ok = 0;
    for(int i=0; i<v_disc_id.size(); i++)
    {
        if(v_disc_id[i] == disc_id){ok = 1; break;}
    } // -- END for(int i=0; i<v_disc_id.size(); i++)
    return ok;
} // -- END get_cmd_result

shared_ptr<nnet> create_nnet(const char* config_path, bool& ok, trac_struct& trac_str0)
{
    cout<<"_______create_nnet"<<endl;
    shared_ptr<nnet> nnet0 = make_shared<nnet>(config_path, ok);
    if(!ok){cout << "NOT shared_ptr<nnet>!!!\n"; return nnet0;}

    nnet0->img_orig_type = trac_str0.img_orig_type;
    nnet0->fr_w0 = trac_str0.fr_w0;
    nnet0->fr_h0 = trac_str0.fr_h0;
    nnet0->fr_w0_1 = 1.f/nnet0->fr_w0;
    nnet0->fr_h0_1 = 1.f/nnet0->fr_h0;
    nnet0->ltrac_ptr = make_unique<list<trac_st>>(nnet0->ltrac);
    nnet0->ts = make_unique<trac_struct>(nnet0->trac_str);

    cout << "copt->trac_str.work_in_round=" << nnet0->trac_str.work_in_round << endl;
    bool init_copter_scan_ok = nnet0->init_copter_scan(config_path);
    if(!init_copter_scan_ok){ok = 0; cout << "NOT init_copter_scan!\n"; return nnet0;}

    if(nnet0->img_orig_type == CV_8UC1 && nnet0->color_channels == 1){nnet0->change_color = 0;}
    else if(nnet0->img_orig_type == CV_8UC3 && nnet0->color_channels == 3){nnet0->change_color = 0;}
    else if(nnet0->img_orig_type == CV_8UC1 && nnet0->color_channels == 3){nnet0->change_color = COLOR_GRAY2BGR;}
    else if(nnet0->img_orig_type == CV_8UC3 && nnet0->color_channels == 1){nnet0->change_color = COLOR_BGR2GRAY;}

    if(nnet0->change_color == -1)
    {
        cout << "img_orig_type=" << nnet0->img_orig_type << "; color_channels=" << nnet0->color_channels << endl;
        cout << "change_color = -1!" << endl;
        ok = 0;
        return nnet0;
    } // -- END if(nnet0->change_color == -1)
    nnet0->ts = unique_ptr<trac_struct>(&trac_str0);
    nnet0->ts->roi_w = nnet0->cfg_w;
    nnet0->ts->roi_h = nnet0->cfg_h;
 #ifdef WORK_IN_ROUND
    nnet0->ts->work_in_round = 1;
 #endif
 #ifdef WORK_IN_RECT
    nnet0->ts->work_in_round = 0;
 #endif
    nnet0->ts->vtrac_data.reserve(nnet0->max_objects);
    nnet0->ts->zahvat = 1;
    nnet0->ts->ok_match = 1; // Признак успешного захвата на текущем кадре.
    nnet0->ts->validate = nnet0->ts->validate_min; // Степень валидации захвата на текущем кадре.
    return nnet0;
} // -- END create_nnet



int get_trac(shared_ptr<nnet>& copt)
{
    return copt->work();
} // -- END get_trac


bool nnet::init_copter_scan(const char* config_path)
{
    cout<<"__________init_copter_scan\n";
#ifndef RKNN_ENABLE
    bool init_yolo_ok = init_yolo(config_path);
    if(!init_yolo_ok){return 0;}
#endif
#ifdef RKNN_ENABLE
   init_RKNN();
#endif
    fr_w0_1 = 1.f/fr_w0;
    fr_h0_1 = 1.f/fr_h0;
    int num_x = fr_w0/cfg_w;
    int delta_x = cfg_w - (fr_w0 - cfg_w)/num_x;
    while(delta_x < pix_cross_min)
    {
        num_x++;
        delta_x = cfg_w - (fr_w0 - cfg_w)/num_x;
    }
    shift_x = round((float)(fr_w0 - cfg_w)/num_x);
    crop_num_x = num_x + 1;
 #ifdef WORK_IN_ROUND
    y_scan_max0 = fr_h0;
 #endif
 #ifdef WORK_IN_RECT
    y_scan_max0 = round(y_scan_max * fr_h0);
 #endif
    int num_y = y_scan_max0/cfg_h;
    int delta_y = cfg_h - (y_scan_max0 - cfg_h)/num_y;
    while(delta_y < pix_cross_min)
    {
        num_y++;
        delta_y = cfg_h - (y_scan_max0 - cfg_h)/num_y;
    }
    shift_y = round((float)(y_scan_max0 - cfg_h)/num_y);
    crop_num_y = num_y + 1;
    fr_w1 = fr_w0 - 1;
    y_scan_max1 = y_scan_max0 - 1;
    cfg_wh = Point2f(cfg_w, cfg_h);
    cfg_wh_2 = 0.5 * cfg_wh;
    y_scan_max2 = y_scan_max1 - cfg_h;
    fr_h1 = fr_h0 * y_scan_max;
    fr_h2 = fr_h0 - cfg_h - 1;
    fr_w_max = fr_w0 - fr_min;
    fr_h_max = fr_h1 - fr_min;
    x_scan_max2 = fr_w0 - cfg_w - 1;
    cfg_w_2 = 0.5 * cfg_w;
    cfg_h_2 = 0.5 * cfg_h;
    fr_w0_2 = 0.5 * fr_w0;
    fr_h0_2 = 0.5 * fr_h0;
    min_deflect = 0.2 * cfg_w;
    max_deflect = cfg_w_2 + min_deflect;
    KF_tr_x.transitionMatrix = (Mat_<float>(4, 4) << 1, 0, dt_tr_1, 0,      0, 1, 0, dt_tr_1,       0, 0, 1, 0,       0, 0, 0, 1);
    KF_tr_y.transitionMatrix = (Mat_<float>(4, 4) << 1, 0, dt_tr_1, 0,      0, 1, 0, dt_tr_1,       0, 0, 1, 0,       0, 0, 0, 1);
    measurement_tr_x.setTo(Scalar(0));
    measurement_tr_y.setTo(Scalar(0));
    setIdentity(KF_tr_x.measurementMatrix); // Инициализация матрицы измерений
    setIdentity(KF_tr_y.measurementMatrix); // Инициализация матрицы измерений
    setIdentity(KF_tr_x.processNoiseCov, Scalar::all(noise_proc)); // Значение ковариации шума процесса
    setIdentity(KF_tr_y.processNoiseCov, Scalar::all(noise_proc)); // Значение ковариации шума процесса
    setIdentity(KF_tr_x.measurementNoiseCov, Scalar::all(noise_measurement)); // Значение ковариации шума измерения
    setIdentity(KF_tr_y.measurementNoiseCov, Scalar::all(noise_measurement)); // Значение ковариации шума измерения
    setIdentity(KF_tr_x.errorCovPost, Scalar::all(err_renew)); // обновление ошибки ковариации
    setIdentity(KF_tr_y.errorCovPost, Scalar::all(err_renew)); // обновление ошибки ковариации
    setlocale(LC_ALL, "en-US");
    i_point_scan = 0;    
 #ifdef WORK_IN_ROUND    
    scan_y = fr_h0/shift_y;
    scan_x = scan_y;
    shift_x = shift_y;
    crop_num_x = crop_num_y;
    v_point_scan.reserve(scan_x * scan_y);
    fr_h0_22 = fr_h0_2 * fr_h0_2;
    int x0 = fr_w0_2 - fr_h0_2;
    int x1 = fr_w0_2 + fr_h0_2 - cfg_h;
    for(int i_y = 0; i_y < scan_y; i_y++)
    {
        int y = i_y * shift_y;
        if(y > fr_h2){y = fr_h2;}
        for(int i_x = 0; i_x < scan_x; i_x++)
        {
            int x = x0 + i_x * shift_x;
            if(x > x1){x = x1;}
            Point cent_crop_cent_frame(x + cfg_w_2 - 0.5 * fr_w0, y + cfg_h_2 - 0.5 * fr_h0);
            int rad2 = cent_crop_cent_frame.x * cent_crop_cent_frame.x + cent_crop_cent_frame.y * cent_crop_cent_frame.y;
            if(rad2 < fr_h0_22){v_point_scan.emplace_back(Point(x, y));}
        } // -- END for(int i_x = 0; i_x < scan_y; i_x++)
    } // -- END for(int i_y = 0; i_y < scan_y; i_y++)
 #endif
 #ifdef WORK_IN_RECT
    scan_x = fr_w0/shift_x;
    scan_y = y_scan_max0/shift_y;
    v_point_scan.reserve(scan_x * scan_y);
    for(int i_y = 0; i_y < scan_y; i_y++)
    {
        int y = i_y * shift_y;
        if(y > y_scan_max2){y = y_scan_max2;}
        for(int i_x = 0; i_x < scan_x; i_x++)
        {
            int x = i_x * shift_x;
            if(x > x_scan_max2){x = x_scan_max2;}
            v_point_scan.emplace_back(Point(x, y));
        } // -- END for(int i_x = 0; i_x < scan_x; i_x++)
    } // -- END for(int i_y = 0; i_y < scan_y; i_y++)
 #endif
    pix_cross_x = cfg_w - shift_x;
    pix_cross_y = cfg_h - shift_y;
    N_point_scan = v_point_scan.size();
    N_point_scan_1 = N_point_scan - 1;
    cout << "N_point_scan = " << N_point_scan << "; shift_x = " << shift_x << "; shift_y = " << shift_y;
    cout << "; crop_num_x=" << crop_num_x << "; crop_num_y=" << crop_num_y;
    cout << "; pix_cross_x=" << pix_cross_x << "; pix_cross_y=" << pix_cross_y << endl;
    scan_left_top = v_point_scan[0];
    time_point_old = system_clock::now();
    tp_scan_new = time_point_old;
    time_begin = time_point_old;
    cout << "END init_copter_scan\n";
    return 1;
} // -- END init_copter_scan


bool nnet::FileIsExist(const string& filePath)
{
    bool isExist = false;
    ifstream fin(filePath.c_str());
    if(fin.is_open()){isExist = true;}
    fin.close();
    return isExist;
} // -- END FileIsExist


bool nnet::get_ini_params(const string& config)
{
    cout << "BEGIN get_ini_params in nnet" << endl;
    if(!FileIsExist(config)){cout << "File '" << config << "' not exist!" << endl; return 0;}
    setlocale( LC_ALL, "en-US" );
    INIReader reader(config);
    if(reader.ParseError()<0){cout << "Can't load '" << config << "'\n"; return 0;}    

 #ifdef WORK_IN_ROUND
    yolo_block = "yolo_round";
    yolo_block_track = "yolo_round_trac";
 #endif
 #ifdef WORK_IN_RECT
    yolo_block = "yolo_rect";
    yolo_block_track = "yolo_round_trac";
 #endif

    // --------------------------------------------------- main_settings

    rotate_frame_180 = reader.GetInteger("main_settings", "rotate_frame_180", -1);
    if(rotate_frame_180 == -1){cout << "rotate_frame_180 not declared!\n"; return 0;}
    else{cout << "rotate_frame_180 = " << rotate_frame_180 << ";\n";}

    // --------------------------------------------------- copter1

    y_scan_max = reader.GetReal("copter1", "y_scan_max", -1);
    if(y_scan_max == -1){cout << "y_scan_max not declared!\n"; return 0;}
    else{cout << "y_scan_max = " << y_scan_max << ";\n";}

    trac_predict_min = reader.GetInteger("copter1", "trac_predict_min", -1);
    if(trac_predict_min == -1){cout << "trac_predict_min not declared!\n"; return 0;}
    else{cout << "trac_predict_min = " << trac_predict_min << ";\n";}

    trac_max = reader.GetInteger("copter1", "trac_max", -1);
    if(trac_max == -1){cout << "trac_max not declared!\n"; return 0;}
    else{cout << "trac_max = " << trac_max << ";\n";}
    if(trac_max <= trac_predict_min){trac_max = trac_predict_min + 1;}

    rait_max = reader.GetInteger("copter1", "rait_max", -1);
    if(rait_max == -1){cout << "rait_max not declared!\n"; return 0;}
    else{cout << "rait_max = " << rait_max << ";\n";}

    deflect_max = reader.GetReal("copter1", "deflect_max", -1);
    if(deflect_max == -1){cout << "deflect_max not declared!\n"; return 0;}
    else{cout << "deflect_max = " << deflect_max << ";\n";}
    deflect_max2 = deflect_max * deflect_max;

    deflect_min = reader.GetReal("copter1", "deflect_min", -1);
    if(deflect_min == -1){cout << "deflect_min not declared!\n"; return 0;}
    else{cout << "deflect_min = " << deflect_min << ";\n";}
    deflect_min2 = deflect_min * deflect_min;

    max_objects = reader.GetInteger("copter1", "max_objects", -1);
    if(max_objects == -1){cout << "max_objects not declared!\n"; return 0;}
    else{cout << "max_objects = " << max_objects << ";\n";}

    // --------------------------------------------------- switcher

    int switcher_ok = reader.GetInteger("switcher", "switcher_ok", -1);
    if(switcher_ok == -1){cout << "switcher_ok not declared!\n"; return 0;}
    else{cout << "switcher_ok = " << switcher_ok << ";\n";}

    if(switcher_ok)
    {        
        if(FileIsExist(switcher_way))
        {
           ifstream fin(switcher_way);
           string item;
           fin >> item;
           fin.close();
           char n = item[0];
           int switch_num = 0;
           if(isdigit(n) && item.length() == 1)
           {
              switch_num = stoi(item);
           }
           else{cout << "Символ в switcher не является цифрой!\n"; return 0;}

           cout << "Switcher работает в режиме: " << switch_num << endl;

           if(switch_num)
           {
              yolo_block = reader.Get("switcher", "yolo_block1", "oops");
              if(yolo_block == "oops"){cout << "yolo_block1 not declared!\n"; return 0;}
              else{cout << "yolo_block = '" << yolo_block << "';\n";}

              yolo_block_track = reader.Get("switcher", "yolo_block_track1", "oops");
              if(yolo_block_track == "oops"){cout << "yolo_block_track1 not declared!\n"; return 0;}
              else{cout << "yolo_block_track = '" << yolo_block_track << "';\n";}
           }
           else
           {
              yolo_block = reader.Get("switcher", "yolo_block0", "oops");
              if(yolo_block == "oops"){cout << "yolo_block0 not declared!\n"; return 0;}
              else{cout << "yolo_block = '" << yolo_block << "';\n";}

              yolo_block_track = reader.Get("switcher", "yolo_block_track0", "oops");
              if(yolo_block_track == "oops"){cout << "yolo_block_track0 not declared!\n"; return 0;}
              else{cout << "yolo_block_track = '" << yolo_block_track << "';\n";}
           } // -- END if(switch_num)
        } // -- END if(FileIsExist(switcer_way))
        else{cout << "Файл " << switcher_way << " не найден, режим Switcher не работает!" << endl;}
    } // -- END if(switcher_ok)

    cout << "END get_ini_params nnet" << endl;
    return 1;
} // -- END get_ini_params


double nnet::power(double x, int pw)
{
    double res = 1.f;
    for(int i=0; i<pw; ++i){res *= x;}
    return res;
} // END power


int nnet::get_abc(int K, double* vec_t, double* vec_y, int vec_size, double* B)
{
    if(vec_size < K){cout << "vec_size < K! \n"; return 0;}
    Mat A(Size(K, K), CV_64F);
    double C[K];
    for(int y = 0; y<K; y++)
    {
        for(int x = 0; x<K; x++)
        {
            double SA = 0; int pw = x+y;
            for(int i=0; i<vec_size; ++i){SA += power(vec_t[i], pw);}
            A.at<double>(y, x) = SA;
        } // -- END for(int x = 0; x<K; x++)
        double SC = 0;
        for(int i=0; i<vec_size; ++i){SC += vec_y[i]*power(vec_t[i], y);}
        C[y] = SC;
    } // -- END for(int y = 0; y<K; y++)
    Mat A_inv(Size(K, K), CV_64F);
    invert(A, A_inv);
    //invert_mat(A, A_inv);
    for(int y = 0; y<K; y++)
    {
        double SB = 0;
        for(int x = 0; x<K; x++){SB += C[x]*A_inv.at<double>(y, x);}
        B[y] = SB;
    } // -- END for(int y = 0; y<K; y++)
    return 1;
} // -- END get_abc


bool nnet::get_polinom(const list<tr>& lt, double time_now)
{
    double vec_t[lt.size()];
    double vec_x[lt.size()];
    double vec_y[lt.size()];
    double max_x=fr_w0, max_y=fr_h0;
    double max_t = time_now - lt.back().tp;
    int i = 0;
    for(auto it = lt.end(); it != lt.begin();)
    {
        it--;
        vec_t[i] = (it->tp - lt.back().tp)/max_t;
        vec_x[i] = it->xy.x/max_x;
        vec_y[i] = it->xy.y/max_y;
        i++;
    } // -- END for(auto it = lt.end(); it != lt.begin();)
    bool ok_x = get_abc(Polinom_size, vec_t, vec_x, lt.size(), Polinom_koef_x);
    if(!ok_x){return 0;}
    bool ok_y = get_abc(Polinom_size, vec_t, vec_y, lt.size(), Polinom_koef_y);
    if(!ok_y){return 0;}
    return 1;
} // -- END get_polinom


void nnet::correct_copter_trac(list<trac_st>::iterator& obj)
{
    Point lt(round(obj->predict.x - cfg_w_2), round(obj->predict.y - cfg_h_2));
    if(lt.x < 0){lt.x = 0;}
    if(lt.y < 0){lt.y = 0;}
#ifdef WORK_IN_ROUND
    if(lt.x > x_scan_max2){lt.x = x_scan_max2;}
    if(lt.y > fr_h2){lt.y = fr_h2;}
#endif
#ifdef WORK_IN_RECT
   if(lt.x > x_scan_max2){lt.x = x_scan_max2;}
   if(lt.y > y_scan_max2){lt.y = y_scan_max2;}
#endif
    vector<tr> vtr;
    yolo_work_track(lt, vtr);
    float deflect_best2 = 10000000;
    Point2f xy_cent_best, wh_2_best;
    for(int i_tr = 0; i_tr < vtr.size(); i_tr++)
    {
         const tr& tr_i = vtr[i_tr];
         if(obj->cls != tr_i.class_num){continue;}
         Point2f deflect = obj->predict - tr_i.xy;
         float deflect2 = deflect.x * deflect.x + deflect.y * deflect.y;
         if(deflect2 < deflect_best2)
         {
             deflect_best2 = deflect2;
             xy_cent_best = tr_i.xy;
             wh_2_best = tr_i.wh_2;
         } // -- END if(deflect2 < deflect_best2)
    } // -- END for(int i_tr = 0; i_tr < vtr.size(); i_tr++)
    if(deflect_best2 < deflect_max2)
    {
        duration_now = system_clock::now() - time_begin;
        obj->ltr.push_front(tr{xy_cent_best, wh_2_best, obj->cls, duration_now.count()});
        if(obj->ltr.size() > trac_max)
        {
           obj->ltr.pop_back();
           obj->trac_ok = 2;
        } // -- END if(obj.ltr.size() > trac_max)
        if(obj->rait < rait_max){obj->rait++;}
        obj->wh_2 = wh_2_best;
        obj->predict = xy_cent_best;
    } // -- END if(deflect_best2 < deflect_max2)
    else
    {
        obj->trac_ok = 0;
        obj->rait--;
    } // -- END if(deflect_best2 >= deflect_max2)
} // -- END correct_copter_trac


bool nnet::get_predict(const list<tr>& trac, Point2f& predict)
{
    Point2f vec = trac.begin()->xy - trac.back().xy;
    double time_trac = trac.begin()->tp - trac.back().tp;
    duration_now = system_clock::now() - time_begin;
    double diff_tp_now = duration_now.count() - trac.begin()->tp;
    float koef = diff_tp_now/time_trac;
    predict = trac.begin()->xy + koef * vec;
    return 1;
} // -- END get_mnk_predict


bool nnet::get_mnk_predict(const list<tr>& trac, Point2f& predict)
{
    duration_now = system_clock::now() - time_begin;
    bool ok = get_polinom(trac, duration_now.count());
    if(ok)
    {
        Point2f vec(0, 0);
        for(int i=0; i < Polinom_size; i++){vec += Point2f(Polinom_koef_x[i], Polinom_koef_y[i]);}
        predict.x = vec.x * fr_w0;
        predict.y = vec.y * fr_h0;
        return 1;
    } // -- END if(ok)
    return 0;
} // -- END get_mnk_predict


bool nnet::get_kalman_predict(const list<tr>& trac, Point2f& predict)
{
    auto it = trac.end();
    it--;
    measurement_tr_x(0) = it->xy.x;
    measurement_tr_x(1) = it->tp;
    measurement_tr_y(0) = it->xy.y;
    measurement_tr_y(1) = it->tp;
    KF_tr_x.statePre.at<float>(0) = it->xy.x; // Инициализация первых
    KF_tr_y.statePre.at<float>(0) = it->xy.y;
    KF_tr_x.statePre.at<float>(1) = it->tp;
    KF_tr_y.statePre.at<float>(1) = it->tp;
    KF_tr_x.statePre.at<float>(2) = 0;
    KF_tr_x.statePre.at<float>(2) = 0;
    KF_tr_y.statePre.at<float>(2) = 0;
    KF_tr_x.statePre.at<float>(3) = 0;
    KF_tr_y.statePre.at<float>(3) = 0; // предсказанных значений
    float trac_mid_wh = 0;
    while(true)
    {
        it--;
        trac_mid_wh += it->wh_2.x * it->wh_2.y;
        measurement_tr_x(0) = it->xy.x;
        measurement_tr_y(0) = it->xy.y;
        measurement_tr_x(1) = it->tp;
        measurement_tr_y(1) = it->tp;
        est_x = KF_tr_x.correct(measurement_tr_x);
        est_y = KF_tr_y.correct(measurement_tr_y);
        pred_x = KF_tr_x.predict();
        pred_y = KF_tr_y.predict();

        kalman_old_old = kalman_old;
        kalman_old = kalman;
        kalman = Point2f(est_x.at<float>(0), est_y.at<float>(0)); // -- Калман

        tp_kalman_old_old = tp_kalman_old;
        tp_kalman_old = tp_kalman;
        tp_kalman = it->tp;
        if(it == trac.begin()){break;}
    } // -- END while(true)
    trac_mid_wh /= trac.size();
    float area = obj_wh_2.x * obj_wh_2.y;
    if(abs(area - trac_mid_wh)/(area + trac_mid_wh) > diff_area_max)
    {
        return 0;
    }
    Point2f diff_kalman_vec = kalman - kalman_old_old;
    double diff_tp_kalman = tp_kalman - tp_kalman_old_old;
    duration_now = system_clock::now() - time_begin;
    double diff_tp_now = duration_now.count() - tp_kalman_old_old;
    float koef = diff_tp_now/diff_tp_kalman;
    //predict = Point2f(pred_x.at<float>(0), pred_y.at<float>(0));
    predict = trac.begin()->xy + koef * diff_kalman_vec;
    return 1;
} // -- END get_kalman_predict


void nnet::find_candidates()
{
    vector<tr> vtr;
    yolo_work(scan_left_top, vtr);
    if(!vtr.size()){return;}
    for(int i_tr = 0; i_tr < vtr.size(); i_tr++)
    {
        const tr& tr_i = vtr[i_tr];
        char cls_cand = tr_i.class_num;
        duration_now = system_clock::now() - time_begin;
        tr cand{tr_i.xy, tr_i.wh_2, cls_cand, duration_now.count()};
        ltrac.push_back(trac_st{1, rait_init, {cand}, tr_i.xy, tr_i.wh_2, cls_cand});
    } // -- END for(int i_tr = 0; i_tr < vtr.size(); i_tr++)
} // -- END find_candidates


void nnet::get_list_objects()
{
    object_num = 0;
    for(list<trac_st>::iterator obj = ltrac.begin(); obj != ltrac.end(); obj++)
    {
        Point2f predict = obj->predict;
        if(obj->trac_ok == 2)
        {
           list<tr>& ltr = obj->ltr;
   #ifdef Polinom0 // ----------------------------------------------------- по крайним точкам
           bool ok = get_predict(ltr, predict);
   #endif // END ifdef Polinom0
   #ifdef Polinom1 // --------------------------------------------------------------- МНК
           bool ok = get_mnk_predict(ltr, predict);
   #endif // END ifdef Polinom1
   #ifdef Polinom2 // -------------------------------------------------------- Калман
           bool ok = get_kalman_predict(ltr, predict);
   #endif // END ifdef Polinom2
           obj->predict = predict;
        } // -- END if(obj->trac_ok == 2)

 #ifdef WORK_IN_ROUND
        Point predict_cent_frame(predict.x - fr_w0_2, predict.y - fr_h0_2);
        int rad2 = predict_cent_frame.x * predict_cent_frame.x + predict_cent_frame.y * predict_cent_frame.y;
        if(rad2 > fr_h0_22)
        {
 #else
        if(predict.x < fr_min || predict.y < fr_min || predict.x > fr_w_max || predict.y > fr_h_max)
        {
 #endif
            obj->rait = 0; // Текущий трак вышел за границы поиска
        } // -- END if(predict.x < fr_min || predict.y < fr_min || predict.x > fr_w_max || predict.y > fr_h_max)
        else
        {
           correct_copter_trac(obj);
        }

        if(obj->rait < 1)
        {
            obj = ltrac.erase(obj); // Удаляем плохой трак.
        } // -- END if(it->rait < 1)
        else // if(obj->rait > 0)
        {
           for(list<trac_st>::iterator obj_next = obj; obj_next != ltrac.end();)
           {
               obj_next++;
               if(obj_next->cls == obj->cls)
               {
                   Point2f deflect = obj->predict - obj_next->predict;
                   float deflect2 = deflect.x * deflect.x + deflect.y * deflect.y;
                   if(deflect2 < deflect_min2)
                   {
                       obj_next = ltrac.erase(obj_next); // Удаляем дублированный трак.
                   } // -- END if(deflect2 < deflect_min2)
               } // -- END if(obj_next->cls == obj->cls)
           } // END for(list<trac_st>::iterator obj_next = obj; obj_next != ltrac.end();)
           if(obj->trac_ok == 2){object_num++;}
        } // END if(obj->rait > 0)
    } // -- END for(list<trac_st>::iterator obj = ltrac.begin(); obj != ltrac.end(); obj++)
} // -- END get_list_objects

int nnet::work()
{
    if(ts->new_frame)
    {
        //if(!ts->img_orig_data){cout << "NOT data for img_orig!!!" << endl; return 0;}
        img_orig = Mat(ts->fr_h0, ts->fr_w0, ts->img_orig_type, ts->img_orig_data);
    } // -- END if(t_st->new_frame)
    // ==========================================================
    get_list_objects();
    find_candidates();    
    i_point_scan++;
    if(i_point_scan > N_point_scan_1)
    {
        i_point_scan = 0;
        tp_scan_old = tp_scan_new;
        tp_scan_new = system_clock::now();
        duration_now = tp_scan_new - tp_scan_old;
        ts->scan_exec_time = duration_now.count();
        //cout_num++;
        //if(cout_num > 10)
        //{
        //   cout_num = 0;
        //   cout << "ltrac.size=" << ltrac.size() << endl;
        //} // -- END if(cout_num > 10)
    } // -- END if(i_point_scan > N_point_scan_1)
    scan_left_top = v_point_scan[i_point_scan];
    // =======================
    ts->vtrac_data.resize(0);
    if(ltrac.size())
    {
        //cout << "=============== ltrac.size()=" << copt->ltrac.size() << endl;
        ltrac.sort([](const trac_st& l1, const trac_st& l2)
        {
          return l1.rait > l2.rait;
        }); // END -- sort
        while(ltrac.size() > max_objects){ltrac.pop_back();}
        for(list<trac_st>::iterator obj = ltrac.begin(); obj != ltrac.end(); obj++)
        {
           ts->vtrac_data.emplace_back(trac_data{fr_w0_1 * obj->predict.x,
                                                 fr_h0_1 * obj->predict.y,
                                                 fr_w0_1 * obj->wh_2.x,
                                                 fr_h0_1 * obj->wh_2.y,
                                                 obj->rait});
        } // END for(list<trac_st>::iterator obj = copt->ltrac.begin(); obj != copt->ltrac.end(); obj++)
    } // END if(copt->ltrac.size())
    return object_num;
} // -- END work
