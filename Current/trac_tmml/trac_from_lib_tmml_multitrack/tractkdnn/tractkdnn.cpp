#include "tractkdnn.hpp"

using namespace std;
using namespace cv;
using namespace chrono;

TracTKDNN::TracTKDNN(const string& config_path, Mat& frame_process_0, bool& ok)
{
    cout << "Constructor TracTKDNN" << endl;
    setOriginalFrameSize(frame_process_0);
    ok = get_ini_params(config_path);
    if(!ok){return;}
    cout <<"BEGIN create_nnet" << endl;
    const char * config_path_char = config_path.c_str();
    trac = create_nnet(config_path.c_str(), ok, ltrac_data_ptr, trac_str);
    cout << "OK create" << endl;
    list<trac_data>::iterator it = ltrac_data_ptr->begin();
    for(int i = 0; i < ltrac_data_ptr->size(); i++)
    {
        cout << "trac_data after create[" << i << "]: " << Rect2f(it->x,
                                                       it->x,
                                                       it->x,
                                                       it->x) << ": rait = " <<
                                                       (int)it->rait << endl << endl;
        it++;
    } // END for(int i = 0; i < ltrac_data_ptr->size(); i++)

    cout << "trac_str.work_in_round=" << trac_str.work_in_round  << endl;
} // END TracTKDNN

TracTKDNN::~TracTKDNN()
{
    cout << "Destructor TracTKDNN" << endl;
} // END ~TracTKDNN()

bool TracTKDNN::update(Mat& img, Rect2f& target)
{
    //cout << "Work num: " << trac_str.work_number << endl;
    if(first_frame)
    {
        float work_h_w = fr_w0_1 * fr_h0;
        fr_h_show = round(work_h_w*fr_w_show);
        sz_show = Size(fr_w_show, fr_h_show);
        show_orig = fr_w0_1 * fr_w_show;
        // if(get_rect_manual == 1)
        // {
        //     trac_str.zahvat = 0;
        //     num_fr_0 = 0;
        //     num_fr_1 = img_names.size() - 1;
        // }
        // else
        // {
        trac_str.zahvat = 1;
        trac_str.rect_ok = 2;
        trac_str.img_orig_type = img.type();
        trac_str.key = 0;
        w_et_orig = round(ext_wh_2*(trac_str.obj_wh_2_w * fr_w0 + trac_str.obj_wh_2_h * fr_h0));
        // } // -- END if(get_rect_manual != 1)
        first_frame = false;
    } // -- END if(first_frame)
    img_orig = img;
    bool ok = process();
    if(ok)
    {
        if(roi)
        {
            ok = calc_roi_size();
            if(!ok){return 0;}
        }
        if(trac_str.zahvat && trac_str.ok_match)
        {
            return 1;
        } // -- END if(trac_str.zahvat and trac_str.ok_match)
    } // -- END if(ok)
    return 0;
} // -- END update


Rect2f TracTKDNN::getROI()
{
    return Rect2f(fr_w0_1 * trac_str.roi_l, fr_h0_1 * trac_str.roi_t,
                  fr_w0_1 * trac_str.roi_w, fr_h0_1 * trac_str.roi_h);
} // -- END geyROI

void TracTKDNN::getSearchRect(Rect2f& rct)
{
#ifdef USE_TKDNN
    rct = Rect2f(fr_w0_1 * trac_str.roi_l, fr_h0_1 * trac_str.roi_t,
                 fr_w0_1 * trac_str.roi_w, fr_h0_1 * trac_str.roi_h);
#endif // END  #ifdef USE_TKDNN

} // -- END getSearchRect

Point2f TracTKDNN::getTargetCenter()
{
    return Point2f(trac_str.obj_xy_x, trac_str.obj_xy_y);
} // -- END getTargetCenter


bool TracTKDNN::FileIsExist(const string& filePath)
{
    bool isExist = false;
    ifstream fin(filePath.c_str());
    if(fin.is_open()){isExist = true;}
    fin.close();
    return isExist;
} // -- END FileIsExist


bool TracTKDNN::get_ini_params(const string& config)
{
    cout << "BEGIN get_ini_params TracTKDNN" << endl;
    setlocale(LC_NUMERIC, "en_US.UTF-8");
    if(!FileIsExist(config))
    {
        cout << "File '" << config << "' not exist!" << endl;
        return 0;
    } // -- END if(!FileIsExist(config))

    INIReader reader(config);
    if(reader.ParseError()<0)
    {
        cout << "Can't load '" << config << "'\n";
        return 0;
    } // -- END if(reader.ParseError()<0)

    // gray = reader.GetInteger("main_settings", "gray", -1);
    // if(gray == -1){cout << "gray not declared!\n"; return 0;}
    // else{cout << "gray = " << gray << ";\n";}
#if defined(CCM_8UC1)
    gray = 1;
#elif defined(CCM_8UC3)
    gray = 0;
#else
    throw runtime_error("Error: not recognize/supported color channel mode");
#endif

    roi = reader.GetInteger("main_settings", "roi_mode", -1);
    if(roi == -1){cout << "roi not declared!\n"; return 0;}
    else{cout << "roi = " << roi << ";\n";}
    trac_str.roi = roi;

    scaling = reader.GetInteger("tracking", "scaling", -1);
    if(scaling == -1){cout << "scaling not declared!\n"; return 0;}
    else{cout << "scaling = " << scaling << ";\n";}

    cout <<"FINISH get_ini_params TracTKDNN" << endl;
    return 1;
} // -- END get_ini_params


bool TracTKDNN::dirContent(const string& fold, vector<string>& img_names, int typ)
{
    img_names.clear();
    DIR *dir;
    struct dirent *ent;
    if((dir = opendir(fold.c_str())) != NULL)
    {
        while((ent = readdir(dir)) != NULL)
        {
            string fname = string(ent -> d_name);
            // -- typ = 4 (folder), typ = 8 (file).
            if(ent -> d_type == typ && fname != "." && fname != "..")
            {
                img_names.emplace_back(fname);
            }
        } // -- END while((ent = readdir (dir)) != NULL)
        closedir(dir);
        return 1;
    } // -- END if((dir = opendir(way)) != NULL)
    return 0;
} // -- END dirContent


bool TracTKDNN::init(const Rect2f& rct_in)
{
    Point2f xy = 0.5*(rct_in.br() + rct_in.tl());
    trac_str.obj_xy_x = xy.x;
    trac_str.obj_xy_y = xy.y;

    Point2f wh_2 = 0.5*(rct_in.br() - rct_in.tl());
    trac_str.obj_wh_2_w = wh_2.x;
    trac_str.obj_wh_2_h = wh_2.y;

    trac_str.img_orig_type = img_orig.type();
    trac_str.zahvat = 1;
    trac_str.key = 0;
    trac_str.rect_ok = 2;
    w_et_orig = round(ext_wh_2*(trac_str.obj_wh_2_w * fr_w0 + trac_str.obj_wh_2_h * fr_h0));
    return 1;
} // -- END init


bool TracTKDNN::init(const Rect2f& rct_in, Rect2f& roi_)
{    
    bool ok = init(rct_in);
    ok = calc_roi_size();
    if(!ok)
    {
        trac_str.zahvat = 0;
        return 0;
    } // -- END if(!ok)
    roi_ = Rect2f(fr_w0_1 * trac_str.roi_l, fr_h0_1 * trac_str.roi_t,
                  fr_w0_1 * trac_str.roi_w, fr_h0_1 * trac_str.roi_h);
    return 1;
} // -- END init


void TracTKDNN::deinit()
{
    trac_str.key = 27;
} // -- END deinit


void TracTKDNN::setOriginalFrameSize(Mat& frame_process_0)
{
    fr_w0 = frame_process_0.cols;
    fr_h0 = frame_process_0.rows;
    fr_w0_1 = 1.f/fr_w0;
    fr_h0_1 = 1.f/fr_h0;
    img_orig_type = frame_process_0.type();
    trac_str.fr_w0 = fr_w0;
    trac_str.fr_h0 = fr_h0;
    trac_str.img_orig_type = img_orig_type;
} // -- END setOriginalFrameSize

bool TracTKDNN::isInited()
{
    return trac_str.zahvat;
}

void TracTKDNN::setTrackerId(int id)
{
    trac_str.id = id;
}

void TracTKDNN::setWorkNumber(int cnt)
{
    trac_str.work_number = cnt;
} // -- END setWorkNumber


bool TracTKDNN::calc_roi_size()
{
    if(scaling > 1)
    {
        w_et_orig = round(ext_wh_2*(trac_str.obj_wh_2_w * fr_w0 + trac_str.obj_wh_2_h * fr_h0));
    } // -- END if(scaling > 1)
    Point2f center_orig = Point2f(trac_str.obj_xy_x * fr_w0, trac_str.obj_xy_y * fr_h0);
    Point2f wh_local_orig(w_et_orig, w_et_orig);
    Point2f wh_local_2_orig = 0.5*wh_local_orig;
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
    trac_str.roi_l = round(rct_local_orig.x);
    trac_str.roi_t = round(rct_local_orig.y);
#ifdef USE_TKDNN
    trac_str.roi_w = 256;
    trac_str.roi_h = 256;
#endif // END  #ifdef USE_TKDNN

    return 1;
} // -- END calc_roi_size


bool TracTKDNN::img_orig_roi_prepare()
{
#ifdef USE_TKDNN
    trac_str.roi_w = 256;
    trac_str.roi_h = 256;
#endif // END   #ifdef USE_TKDNN

    trac_str.img_orig_data = img_orig.data;
    return 1;
} // -- END img_orig_roi_prepare


bool TracTKDNN::img_orig_prepare()
{
    //cout << "img_orig_prepare\n";
    if(scaling > 1)
    {
        w_et_orig = round(ext_wh_2*(trac_str.obj_wh_2_w * fr_w0 + trac_str.obj_wh_2_h * fr_h0));
    } // -- END if(scaling > 1)
    Point2f center_orig = Point2f(trac_str.obj_xy_x * fr_w0, trac_str.obj_xy_y * fr_h0);
    Point2f wh_local_orig(w_et_orig, w_et_orig);
    Point2f wh_local_2_orig = 0.5*wh_local_orig;
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
    trac_str.roi_l = round(rct_local_orig.x);
    trac_str.roi_t = round(rct_local_orig.y);

#ifdef USE_TKDNN
    trac_str.roi_w = 256;
    trac_str.roi_h = 256;
#endif // END #if  #ifdef USE_TKDNN

    trac_str.img_orig_data = img_orig.data;
    return 1;
} // -- END img_orig_prepare


bool TracTKDNN::process()
{    
    trac_str.work_number++;
    if(!trac_str.zahvat){return 0;}
    if(roi)
    {
        bool ok = img_orig_roi_prepare();
        if(!ok)
        {
            trac_str.zahvat = 0;
            cout << "Don't img_orig_roi_prepare!\n";
            return 0;
        } // -- END if(!ok)
    }
    else
    {
        bool ok = img_orig_prepare();
        cout << "ok = " << ok << endl;
        if(!ok)
        {
            trac_str.zahvat = 0;
            cout << "Don't img_orig_prepare!\n";
            return 0;
        } // -- END if(!ok)
    } // -- END if(!roi)
    find_ = get_nnet(trac);
    if(find_ == -1)
    {
        cout << "Escape" << endl;
        return 0;
    } // -- END if(find_ == -1)
    return 1;
} // -- END process


int TracTKDNN::work()
{   // ======================== Эта функция только для нейросетевой библиотеки.
    return get_nnet(trac);
} // -- END work
