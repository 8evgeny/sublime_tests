#include "trac_scale.hpp"

using namespace std;
using namespace cv;
using namespace chrono;


bool trac_tmml::get_cmd_result(const string& get_disk_id, const vector<string>& v_disc_id)
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


trac_tmml::trac_tmml(const std::string& config_path, bool& ok)
{
   ok = get_ini_params(config_path);
   if(!ok){return;}

   tm = make_unique<tmml>(ok, min_max_Val);
   tm->max_pix = tm->max_pix0;

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
       "S649NL0TB45870W"
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

   KF_tr.transitionMatrix = (Mat_<float>(4, 4) << 1, 0, dt_tr_1, 0,      0, 1, 0, dt_tr_1,       0, 0, 1, 0,       0, 0, 0, 1);
   measurement_tr.setTo(Scalar(0));
   setIdentity(KF_tr.measurementMatrix); // Инициализация матрицы измерений
   setIdentity(KF_tr.processNoiseCov, Scalar::all(noise_proc)); // Значение ковариации шума процесса
   setIdentity(KF_tr.measurementNoiseCov, Scalar::all(noise_measurement)); // Значение ковариации шума измерения
   setIdentity(KF_tr.errorCovPost, Scalar::all(err_renew)); // обновление ошибки ковариации 
   A = Mat(Size(Polinom_size, Polinom_size), CV_64F);
   A_inv = Mat(Size(Polinom_size, Polinom_size), CV_64F);
   get_vec_angl();
   time_point0 = system_clock::now();
   time_point1 = system_clock::now();
} // -- END trac_tmml

trac_tmml::~trac_tmml()
{
    tm->~tmml();
    cout << "Деструктор trac_tmml" << endl;
    ts.release();
} // END ~trac_tmml()


shared_ptr<trac_tmml> create_track(const char* config_path,
                       bool& ok,
                       trac_struct& trac_st)
{
    shared_ptr<trac_tmml> trac = make_shared<trac_tmml>(config_path, ok);
    trac->ts = unique_ptr<trac_struct>(&trac_st);
    return trac;
} // -- END create_trac


int get_trac(shared_ptr<trac_tmml>& trac)
{
    trac_struct& t_st = *trac->ts;

    if(t_st.key == '`'){return -1;}
    else if(t_st.key == 27)
    {
 #ifdef COUT_OK
        cout << "--------------------------------------------------- deinit5" << endl;
 #endif // END COUT_OK
        trac->deinit();
        return 1;
    } // -- END if((*trac->ts).key == 27)

    if(t_st.roi)
    {
        trac->img_orig_roi = Mat(t_st.roi_h, t_st.roi_w, t_st.img_orig_type, t_st.img_orig_data);
        trac->rct_local_orig = Rect2f(t_st.roi_l, t_st.roi_t, t_st.roi_w, t_st.roi_h);
    }
    else{trac->img_orig = Mat(t_st.fr_h0, t_st.fr_w0, t_st.img_orig_type, t_st.img_orig_data);}

    if(t_st.rect_ok == 2){t_st.zahvat = 1;}

    int _find = trac->work(); // Запуск
    return _find;
} // -- END get_trac


void trac_tmml::get_vec_angl()
{
   v_angl.resize(N_LK_2);
   v_LK_points.resize(N_LK);
   float dfi = 2.f*M_PI/N_LK_2;
   float fi0 = -M_PI + 0.5*dfi;
   for(int i=0; i<N_LK_2; i++)
   {
       float fi = fi0 + i*dfi;
       v_angl[i] = Point2f(cos(fi), sin(fi));
   } // -- END for(int i=0; i<N_LK_2; i++)
} // -- END get_vec_angl


void trac_tmml::deinit()
{
    (*ts).zahvat = 0;
    list_et.clear();
    first_img = 1;
    k_renew = k_renew_ok;
    (*ts).ok_match = 0;
    //ext_wh = ext_wh0;
    //wh_local = wh_local0;
    d02 = d020;
    (*ts).validate = (*ts).validate_min;
    (*ts).rect_ok = 0;
    img_orig.data = nullptr;
    img_orig_roi.data = nullptr;
    measurement_tr.setTo(Scalar(0));
    deq_st.resize(0);
    first_match = 1;
} // -- END deinit


bool trac_tmml::get_ini_params(const string& config)
{
   cout << endl << "BEGIN get_ini_params trac" << endl;
   if(!FileIsExist(config)){cout << "File '" << config << "' not exist!" << endl; return 0;}
   INIReader reader(config);
   if(reader.ParseError()<0){cout << "Can't load '" << config << "'\n"; return 0;}
   setlocale(LC_NUMERIC, "en_US.UTF-8");

   // --------------------------------------------------- tracking

   scaling = reader.GetInteger("tracking", "scaling", -1);
   if(scaling == -1){cout << "scaling not declared!\n"; return 0;}
   else{cout << "scaling = " << scaling << ";\n";}

   k_renew_ok = reader.GetInteger("tracking", "k_renew_ok", -1);
   if(k_renew_ok == -1){cout << "k_renew_ok not declared!\n"; return 0;}
   else{k_renew = k_renew_ok; cout << "k_renew_ok = " << k_renew_ok << ";\n";}

   list_et_sz = reader.GetInteger("tracking", "list_et_sz", -1);
   if(list_et_sz == -1){cout << "list_et_sz not declared!\n"; return 0;}
   else{cout << "list_et_sz = " << list_et_sz << ";\n";}

   min_max_Val = reader.GetReal("tracking", "min_max_Val", -1);
   if(min_max_Val == -1){cout << "min_max_Val not declared!\n"; return 0;}
   else{cout << "min_max_Val = " << min_max_Val << ";\n";}
   min_max_Val2 = min_max_Val * min_max_Val;

   shift2 = reader.GetReal("tracking", "shift2", -1);
   if(shift2 == -1){cout << "shift2 not declared!\n"; return 0;}
   else{cout << "shift2 = " << shift2 << ";\n";}

   Polinom_size = reader.GetInteger("tracking", "Polinom_size", -1);
   if(Polinom_size == -1){cout << "Polinom_size not declared!\n"; return 0;}
   else{cout << "Polinom_size = " << Polinom_size << ";\n";}

   smooth_on = reader.GetInteger("tracking", "smooth_on", -1);
   if(smooth_on == -1){cout << "smooth_on not declared!\n"; return 0;}
   else{cout << "smooth_on = " << smooth_on << ";\n";}

   deq_sz_min = reader.GetInteger("tracking", "deq_sz_min", -1);
   if(deq_sz_min == -1){cout << "deq_sz_min not declared!\n"; return 0;}
   else{cout << "deq_sz_min = " << deq_sz_min << ";\n";}

   validate_ext = reader.GetInteger("tracking", "validate_ext", -1);
   if(validate_ext == -1){cout << "validate_ext not declared!\n"; return 0;}
   else{cout << "validate_ext = " << validate_ext << ";\n";}

   max_fps = reader.GetInteger("tracking", "max_fps", -1);
   if(max_fps == -1){cout << "max_fps not declared!\n"; return 0;}
   else{cout << "max_fps = " << max_fps << ";\n";}
   duration_delay_fps = 1.f/max_fps;

   cout << "END get_ini_params trac" << endl << endl;
   return 1;
} // -- END get_ini_params


bool trac_tmml::FileIsExist(const string& filePath)
{
    bool isExist = false;
    ifstream fin(filePath.c_str());
    if(fin.is_open()){isExist = true;}
    fin.close();
    return isExist;
} // -- END FileIsExist


void trac_tmml::get_vec_LK_points(float a_2)
{
    float a_r1 = a_2*rad1;
    float a_r2 = a_2*rad2;
    for(int i=0; i<N_LK_2; i++)
    {
        v_LK_points[i] = Point2f(a_2 + a_r1*v_angl[i].x, a_2 + a_r1*v_angl[i].y);
        v_LK_points[N_LK_2 + i] = Point2f(a_2 + a_r2*v_angl[i].x, a_2 + a_r2*v_angl[i].y);
    } // -- END for(int i=0; i<N_LK_2; i++)
} // -- END get_vec_LK_points


float trac_tmml::get_scale()
{
   Point obj_loc_orig(round((*ts).obj_xy_x*fr_w0 - rct_local_orig.tl().x), round((*ts).obj_xy_y*fr_h0 - rct_local_orig.tl().y));
   float a_2_x = MIN(obj_loc_orig.x, rct_local_orig.width - obj_loc_orig.x);
   float a_2_y = MIN(obj_loc_orig.y, rct_local_orig.height - obj_loc_orig.y);
   int a_2_xy = MIN(a_2_x, a_2_y);
   if(a_2_xy < a_2_now_min){return 0;}
   a_2_now = Point(a_2_xy, a_2_xy);

   if(first_match)
   {

      first_match = 0;
      img_now = img_orig_roi(Rect(obj_loc_orig - a_2_now, obj_loc_orig + a_2_now)).clone();
      if(img_now.channels() == 3){cvtColor(img_now, img_now, COLOR_BGR2GRAY);}
      return 0;
   } // -- END if(first_match)

   img_prev = img_now.clone();
   img_now = img_orig_roi(Rect(obj_loc_orig - a_2_now, obj_loc_orig + a_2_now)).clone();
   if(img_now.channels() == 3){cvtColor(img_now, img_now, COLOR_BGR2GRAY);}

   if(img_prev.cols < img_now.cols)
   {
       float a_2_p = 0.5*img_prev.cols;
       float a_2_n = 0.5*img_now.cols;
       img4LK_now = img_now(Rect(Point2f(a_2_n, a_2_n) - Point2f(a_2_p, a_2_p), Point2f(a_2_n, a_2_n) + Point2f(a_2_p, a_2_p))).clone();
       img4LK_prev = img_prev;
   }
   else if(img_prev.cols > img_now.cols)
   {
       float a_2_p = 0.5*img_prev.cols;
       float a_2_n = 0.5*img_now.cols;
       img4LK_prev = img_prev(Rect(Point2f(a_2_p, a_2_p) - Point2f(a_2_n, a_2_n), Point2f(a_2_p, a_2_p) + Point2f(a_2_n, a_2_n))).clone();
       img4LK_now = img_now;
   }
   else
   {
       img4LK_now = img_now;
       img4LK_prev = img_prev;
   } // -- END if(img_prev.cols == img_now.cols)

   get_vec_LK_points(0.5*img4LK_now.cols);

   vector<uchar> status_LK;
   vector<float> err_LK;
   vector<Point2f> predict_LK;
   calcOpticalFlowPyrLK(img4LK_prev, img4LK_now, v_LK_points, predict_LK, status_LK, err_LK, wsz, 1, TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 5, 0.01), dt1_LK, dt2_LK);

   float k_ext1 = 0, k_ext2 = 0;
   float koef = koef_LK/(img4LK_now.cols*N_LK_2);
   for(int i1 = 0; i1 < N_LK_2; i1++)
   {
        Point2f flow1 = predict_LK[i1] - v_LK_points[i1];
        int i2 = N_LK_2 + i1;
        Point2f flow2 = predict_LK[i2] - v_LK_points[i2];
        k_ext1 += flow1.x*v_angl[i1].x + flow1.y*v_angl[i1].y;
        k_ext2 += flow2.x*v_angl[i1].x + flow2.y*v_angl[i1].y;
   } // -- END for(int i1 = 0; i1 < N_LK_2; i1++)
   float scale = 1.f + koef*(k_ext1/rad1 + k_ext2/rad2);
   return scale;
} // -- END get_scale


bool trac_tmml::verify_pnt(const Rect2f& r, const Point2f& p)
{
    if(p.x < r.tl().x || p.y < r.tl().y || p.x >= r.br().x || p.y >= r.br().y){return 0;}
    return 1;
} // -- END verify_pnt


bool trac_tmml::verify_rect(const Size& sz, const Rect2f& r)
{
    if(r.x < 0 || r.y < 0 || r.br().x >= sz.width || r.br().y >= sz.height ){return 0;}
    return 1;
} // -- END verify_rect


bool trac_tmml::shift_verify(Point2f& pnt)
{    
    Point2f dp = pnt - center_prev;
    float d2 = dp.x*dp.x + dp.y*dp.y;    
    work_number_rel = (*ts).work_number - num_frame_ok;
    if(d2 < d02*work_number_rel*work_number_rel){return 1;}
    return 0;
} // -- END shift_verify


bool trac_tmml::match_img()
{
   if((*ts).roi)
   {
       resize(img_orig_roi, img_local_work, wh_local0);
       lt_local_work = work_orig*rct_local_orig.tl();
   }
   else
   {
      Point2f wh_local_orig = orig_work*Point2f(wh_local0.width, wh_local0.height);
      Point2f wh_local_2_orig = 0.5*wh_local_orig;
      center_orig = Point2f((*ts).obj_xy_x*fr_w0, (*ts).obj_xy_y*fr_h0);
      Point2f lt = center_orig - wh_local_2_orig;
      if(lt.x < 0){lt.x = 0;}
      if(lt.y < 0){lt.y = 0;}
      Point2f br = lt + wh_local_orig;
      if(br.x >= fr_w0){br.x = fr_w0 - 1;}
      if(br.y >= fr_h0){br.y = fr_h0 - 1;}
      Point2f br_wh1 = br - wh_local_orig;
      if(br_wh1.x < lt.x){lt.x = br_wh1.x;}
      if(br_wh1.y < lt.y){lt.y = br_wh1.y;}
      if(lt.x < 0 || lt.y < 0){return 0;}
      rct_local_orig = Rect2f(lt, br);
      lt_local_work = work_orig*rct_local_orig.tl();
      img_orig_roi = img_orig(rct_local_orig);
      resize(img_orig_roi, img_local_work, wh_local0);
   } // -- END if(!(*ts).roi)

   int k = 0;
   for(auto it = list_et.begin(); it != list_et.end();)
   {
      // ------------------------------ Нахождение et на изображении img_work_local
      et = (*it).clone();
      it++;

      tm->work_tmml(img_local_work, et, tm->max_pix);
      //cout << "maxVal=" << maxVal << "; k=" << k << "/" << list_et.size() << endl;  
  #ifdef NO_GPU
      if(tm->maxVal > min_max_Val)
      {
  #else
      if(tm->max_pix.bright > min_max_Val2)
      {
  #endif
          //cout << " Match ok" << endl;
          local_center_tmp = Point2f(tm->max_pix.x + 0.5*et.cols, tm->max_pix.y + 0.5*et.rows);
          rct_local_result = Rect(local_center_tmp - wh_et_2, local_center_tmp + wh_et_2);
          //cout << "rct_local_result.tl=" << rct_local_result.tl() << "; br=" << rct_local_result.br() << "; img_local_work.size()=" << img_local_work.size() << endl;
          if(!verify_rect(img_local_work.size(), rct_local_result)){k++; continue;}
          Mat img_et_tmp = img_local_work(rct_local_result);
          // ------------------------------ Нахождение img_et_sm на изображении img_et
          img_et_sm = et(rct_result_sm);
          /// Do the Matching and Normalize
          matchTemplate(img_et_tmp, img_et_sm, result_sm, TM_CCOEFF_NORMED);
          /// Localizing the best match with minMaxLoc
          minMaxLoc(result_sm, &minVal_sm, &maxVal_sm, &minLoc_sm, &maxLoc_sm, Mat());
          //cout << "maxVal_sm=" << maxVal_sm << endl;
          if(maxVal_sm < min_max_Val){k++; continue;}

          local_center_tmp = Point2f(rct_local_result.x + maxLoc_sm.x + wh_sm__2, rct_local_result.y + maxLoc_sm.y + wh_sm__2);
          rct_local_result = Rect(local_center_tmp - wh_et_2, local_center_tmp + wh_et_2);

          const Point2f& lt1 = rct_local_result.tl();
          const Point2f& rd1 = rct_local_result.br();
          if(lt1.x < 0 || lt1.y < 0 || rd1.x >= fr_w_work || rd1.y >= fr_h_work){k++; continue;}

          Point2f center_tmp = lt_local_work + local_center_tmp;
          center_prev = center;
          center = center_tmp;
          measurement_tr(0) = center.x; // измеренное значение
          measurement_tr(1) = center.y; // измеренное значение          

          if(first_img){shift_ok = 1;}
          else
          {
             shift_ok = shift_verify(center_tmp);
             if(!shift_ok){k++; continue;}
          } // -- END if(!first_img)

          rct_result = Rect2f(center - wh_et_2, center + wh_et_2);
          rct_result_orig = Rect2f(orig_work*rct_result.tl(), orig_work*rct_result.br());

          est = KF_tr.correct(measurement_tr); // Обновление
          pred = KF_tr.predict();
          Point2f pk(est.at<float>(0), est.at<float>(1)); // -- Калман.
          //Point2f pk(pred.at<float>(0), pred.at<float>(1)); // -- Калман.
          center_kalman = pk; // -- Калман.

          if(scaling)
          {
             float scale = get_scale();
             if(scale)
             {
                 (*ts).obj_wh_2_w *= scale;
                 (*ts).obj_wh_2_h *= scale;
             } // -- END if(scale)
          } // -- END if(scaling)
          num_frame_ok = (*ts).work_number;
          d02 = d020;
          return 1;
      } // -- END if(tm->maxVal > min_max_Val)
      //cout << " NO match" << endl;
      k++;
   } // -- END for(auto it = list_et.begin(); it != list_et.end(); it++)

   measurement_tr(0) = center_kalman.x; // измеренное значение
   measurement_tr(1) = center_kalman.y; // измеренное значение
   est = KF_tr.correct(measurement_tr); // Обновление
   pred = KF_tr.predict();
   Point2f pk(est.at<float>(0), est.at<float>(1)); // -- Калман.
   //Point2f pk(pred.at<float>(0), pred.at<float>(1)); // -- Калман.
   center_prev = center;
   center_kalman = pk; // -- Калман.
   center = center_kalman;
   rct_result = Rect2f(center - wh_et_2, center + wh_et_2);
   rct_result_orig = Rect2f(orig_work*rct_result.tl(), orig_work*rct_result.br());
   //shift_ok = shift_verify(center);

   if((*ts).validate < validate_ext)
   {
     d02 *= 2.f;
 #ifdef COUT_OK
     cout << "--------------------------------------------------- deinit8" << endl;
 #endif // END COUT_OK
     deinit();
   } // -- END if(validate < validate_ext)

  return 0;
} // END match_img


void trac_tmml::init_work()
{
    //cout << "---------- init()" << endl;
    k_renew++;
    if(k_renew > k_renew_ok)
    {
        k_renew = 0;
        renew = 1;
        if(!first_img && verify_rect(img_local_work.size(), rct_local_result)){img_et = img_local_work(rct_local_result).clone();}
        list_et.push_back(img_et);
        if(list_et.size() > list_et_sz){list_et.pop_front();}
    //cout << "------------------------------------------------ img_et.size()=" << img_et.size() << endl;
    } // -- END if(k_renew > k_renew_ok)
} // -- END init_work


bool trac_tmml::get_abc(const vector<Point2d>& vec, vector<float>& B)
{
    auto p = [](double x, int pw)
    {
        double res = 1.f;
        for(int i=0; i<pw; ++i){res *= x;}
        return res;
    };
    vector<double> C(Polinom_size);
    for(int y = 0; y<Polinom_size; y++)
    {
       for(int x = 0; x<Polinom_size; x++)
       {
           double SA = 0; int pw = x+y;
           for(int i=0; i<vec.size(); ++i){SA += p(vec[i].x, pw);}
           A.at<double>(y, x) = SA;
       } // -- END for(int x = 0; x<Polinom_size; x++)
       double SC = 0;
       for(int i=0; i<vec.size(); ++i){SC += vec[i].y*p(vec[i].x, y);}
       C[y] = SC;
    } // -- END for(int y = 0; y<Polinom_size; y++)
    invert(A, A_inv);
    for(int y = 0; y<Polinom_size; y++)
    {
       double SB = 0;
       for(int x = 0; x<Polinom_size; x++){SB += C[x]*A_inv.at<double>(y, x);}
       B[y] = SB;
    } // -- END for(int y = 0; y<K; y++)
    return 1;
} // -- END get_abc


bool trac_tmml::get_smooth_xy(Point2f& extr_xy)
{
    vector<Point2d> x_out(deq_st.size()), y_out(deq_st.size());
    size_t ts_0 = deq_st[0].work_number;
    size_t ts_01 = deq_st[deq_st.size()-1].work_number - ts_0;
    for(int i=0; i<deq_st.size(); ++i)
    {
        smoth_trac& st = deq_st[i];
        double ts_i = (double)(st.work_number - ts_0)/ts_01;
        x_out[i] = Point2d(ts_i, st.x);
        y_out[i] = Point2d(ts_i, st.y);
    } // -- END for(int i=0; i<deq_st.size(); ++i)

    vector<float> B_x(Polinom_size), B_y(Polinom_size);
    bool ok_x = get_abc(x_out, B_x);
    if(!ok_x){return 0;}
    bool ok_y = get_abc(y_out, B_y);
    if(!ok_y){return 0;}
    for(int j=0; j<Polinom_size; ++j){extr_xy += Point2f(B_x[j], B_y[j]);}
    return 1;
} // -- END get_smooth_xy


bool trac_tmml::get_obj_xy_smooth(float obj_xy_x, float obj_xy_y)
{
    deq_st.push_back(smoth_trac{obj_xy_x, obj_xy_y, (*ts).work_number});
    if(deq_st.size() < deq_sz_min)
    {
        (*ts).obj_xy_x = obj_xy_x;
        (*ts).obj_xy_y = obj_xy_y;
        return 0;
    }

    Point2f extr_xy(0, 0);
    bool ok = get_smooth_xy(extr_xy);
    if(ok)
    {
        (*ts).obj_xy_x = extr_xy.x;
        (*ts).obj_xy_y = extr_xy.y;
    }
    else
    {
        (*ts).obj_xy_x = obj_xy_x;
        (*ts).obj_xy_y = obj_xy_y;
        return 0;
    } // -- END if(!ok)
    deq_st.pop_front();
    return 1;
} // -- END get_obj_xy_smooth


int trac_tmml::work()
{
    //(*ts).work_number++;
#ifdef COUT_OK
    time_point0 = system_clock::now();
#endif // END COUT_OK
    //cout << "trac_st.zahvat2=" << (*ts).zahvat << "; list_et.size=" << list_et.size() << endl;
    if((*ts).zahvat)
    {
       //cout << "------------------------------------------------  zahvat; list_et.size=" << list_et.size() << endl;
       if(first_img)
       {
           //cout << "------------------------------------------------  first_img=" << first_img << endl;
           //cout << "obj_xy=" << (*ts).obj_xy_x << ", " << (*ts).obj_xy_y << "; obj_wh_2=" << (*ts).obj_wh_2_w << ", " << (*ts).obj_wh_2_h << endl;
           fr_w0 = (*ts).fr_w0;
           fr_h0 = (*ts).fr_h0;
           fr_w0_1 = 1.f/fr_w0;
           fr_h0_1 = 1.f/fr_h0;

           num_frame_ok = (*ts).work_number;
           orig_work = (float)(*ts).roi_w/wh_local0.width;
           work_orig = 1.f/orig_work;
           fr_w_work = round(work_orig*fr_w0);
           fr_h_work = round(work_orig*fr_h0);
           wh_et_2 = Point2f((*ts).obj_wh_2_w*fr_w_work, (*ts).obj_wh_2_h*fr_h_work);
           wh_et = cv::Size(2*wh_et_2.x, 2*wh_et_2.y);
           d020 = shift2*(wh_et.width*wh_et.width + wh_et.height*wh_et.height);
           d02 = d020;
           //cout << "first_img: num_fr_0=" << num_fr_0 << "; obj_xy=[" << (*ts).obj_xy_x << ", " << (*ts).obj_xy_y << "]; obj_wh_2=[" << (*ts).obj_wh_2_w << ", " << (*ts).obj_wh_2_h << "]; fr_w_work=" << fr_w_work << "; fr_h_work=" << fr_h_work << endl;
           //cout << "wh_et_2=" << wh_et_2 << "; work_orig=" << work_orig << "; fr_w0=" << fr_w0 << "; (*ts).roi_w=" << (*ts).roi_w << endl;
           center = Point2f((*ts).obj_xy_x*fr_w_work, (*ts).obj_xy_y*fr_h_work);
           center_prev = center;

           //cout << "work_orig=" << work_orig << "; wh_et=" << wh_et << "; fr_w_work=" << fr_w_work << endl;
           rct_result_orig = Rect2f(((*ts).obj_xy_x - (*ts).obj_wh_2_w)*fr_w0, ((*ts).obj_xy_y - (*ts).obj_wh_2_h)*fr_h0, 2.f*(*ts).obj_wh_2_w*fr_w0, 2.f*(*ts).obj_wh_2_h*fr_h0);
           //cout << "rct_result_orig.lt=" << rct_result_orig.tl() << "; wh=" << rct_result_orig.size() << "; rect_ok=" << (*ts).rect_ok << endl;
           if((*ts).rect_ok == 2)
           {
               (*ts).rect_ok = 0;
               if((*ts).roi)
               {
                   Rect2f rct_result_orig_roi(rct_result_orig.x - (*ts).roi_l, rct_result_orig.y - (*ts).roi_t, rct_result_orig.width, rct_result_orig.height);
                   //cout << "img_orig_roi_sz=" << img_orig_roi.size() << "; rct=" << rct_result_orig_roi.tl() << " -> " << rct_result_orig_roi.br() << endl;
                   resize(img_orig_roi(rct_result_orig_roi), img_et, wh_et);
                   //cout << "img_orig_roi_sz=" << img_orig_roi.size() << "; rct=" << rct_result_orig_roi.tl() << " -> " << rct_result_orig_roi.br() << endl;
               }
               else
               {
                  resize(img_orig(rct_result_orig), img_et, wh_et);
               } // -- END if(!(*ts).roi)
           } // -- END if(rect_ok == 2)

           result.create(Size(wh_local0.width - wh_et.width + 1, wh_local0.height - wh_et.height + 1), CV_32FC1);
           wh_sm__2 = MAX(wh_sm__2_min, round(koef_wh_sm*wh_et_2.x));
           result_sm.create(Size(wh_et.width - wh_sm__2 + 1, wh_et.height - wh_sm__2 + 1), CV_32FC1);
           wh_sm_2 = Point2f(wh_sm__2, wh_sm__2);
           rct_result_sm = Rect2f(wh_et_2 - wh_sm_2, wh_et_2 + wh_sm_2);
           if(!verify_rect(img_et.size(), rct_result_sm)){deinit(); return 1;}

           init_work();
           (*ts).validate = (*ts).validate_min;
           KF_tr.statePre.at<float>(0) = center.x; /////////////////
           KF_tr.statePre.at<float>(1) = center.y; // Инициализация первых
           KF_tr.statePre.at<float>(2) = 0; // предсказанных значений
           KF_tr.statePre.at<float>(3) = 0; /////////////////
           measurement_tr(0) = center.x;
           measurement_tr(1) = center.y;
           // -- END if(first_img)
       }
       else if(scaling > 1)
       {
           orig_work = (float)(*ts).roi_w/wh_local0.width;
           work_orig = 1.f/orig_work;
           fr_w_work = round(work_orig*fr_w0);
           fr_h_work = round(work_orig*fr_h0);
           wh_et_2 = Point2f((*ts).obj_wh_2_w*fr_w_work, (*ts).obj_wh_2_h*fr_h_work);
           wh_et = cv::Size(2*wh_et_2.x, 2*wh_et_2.y);
           center = Point2f((*ts).obj_xy_x*fr_w_work, (*ts).obj_xy_y*fr_h_work);
       } // -- END if(!first_img && scaling)

       (*ts).ok_match = match_img();

       if(first_img)
       {
           if(!(*ts).ok_match)
           {
 #ifdef COUT_OK
               cout << "--------------------------------------------------- deinit4" << endl;
 #endif // END COUT_OK
               deinit();
               return 1;
           } // -- END if(!(*ts).ok_match)
           first_img = 0;
       } // -- END if(first_img)
       //cout << "------------------------------------------------ ok_match=" << (*ts).ok_match << "; list_et.size=" << list_et.size() << "; first_img=" << first_img << endl;
       float obj_xy_x = center.x/fr_w_work;
       float obj_xy_y = center.y/fr_h_work;
       if(smooth_on == 2)
       {
           bool ok_smooth = get_obj_xy_smooth(obj_xy_x, obj_xy_y);
       }
       else
       {
           (*ts).obj_xy_x = obj_xy_x;
           (*ts).obj_xy_y = obj_xy_y;
       }

       if((*ts).ok_match)
       {
           if(shift_ok)
           {
               (*ts).validate++;
               if((*ts).validate > (*ts).validate_min){(*ts).validate = (*ts).validate_min;}
           }
           else
           {
               (*ts).validate--;
               k_renew = k_renew_ok - 1;
           } // -- END if(!shift_ok)

           if((*ts).validate == (*ts).validate_min)
           {
              init_work();
              //if(!list_et.size()){deinit(); return 1;}
           } // -- END if(validate == (*ts).validate_min)
           not_ok_match_start = system_clock::now();
       }
       else
       {
           (*ts).validate--;
           k_renew = k_renew_ok - 1;
           not_ok_match_stop = system_clock::now();
           not_ok_match_duration = not_ok_match_stop - not_ok_match_start;
           if(not_ok_match_duration.count() > not_ok_match_count_max)
           {
 #ifdef COUT_OK
               cout << "--------------------------------------------------- deinit2" << endl;
 #endif // END COUT_OK
               deinit();
               return 1;
           } // -- END if(not_ok_match_duration.count() > not_ok_match_count_max)
       } // -- END if(!trac_s.ok_match)
    } // -- END if(trac_s.zahvat)

#ifdef MAX_FPS_OK
    time_point1_old = time_point1;
    time_point1 = system_clock::now();
#endif // END MAX_FPS_OK
#ifdef COUT_OK
    time_point1 = system_clock::now();    
#endif // END COUT_OK
#ifdef MAX_FPS_OK
    duration_delay = time_point1 - time_point1_old;
    float duration_delay_diff = duration_delay_fps - duration_delay.count();
    if(duration_delay_diff > 0){usleep(1000000 * duration_delay_diff);}
#endif // END MAX_FPS_OK

 #ifdef COUT_OK
    duration1 = time_point1 - time_point0;
    cout << (*ts).id << "->" << (*ts).work_number << "; shift_ok=" << shift_ok << "; dt1=" << duration1.count() << "; validate=" << (*ts).validate << "; ok_match=" << (*ts).ok_match << endl;
 #endif // END COUT_OK
    if((*ts).ok_match && (abs((*ts).obj_xy_x - 0.5) > object_relative_max || abs((*ts).obj_xy_y - 0.5) > object_relative_max))
    {
 #ifdef COUT_OK
        cout << "--------------------------------------------------- deinit3" << endl;
 #endif // END COUT_OK
        deinit();
    } // -- END if((*ts).ok_match && (abs((*ts).obj_xy_x - 0.5) > object_relative_max || abs((*ts).obj_xy_y - 0.5) > object_relative_max))
    return 1;
} // -- END work
