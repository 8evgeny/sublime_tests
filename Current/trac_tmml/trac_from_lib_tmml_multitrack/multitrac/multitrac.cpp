#include "multitrac.hpp"

namespace mtrac
{

using namespace std;
using namespace cv;

Multitrac::Multitrac()
{
    std::cout << "Multitrac::Constructor!\n";
} // -- END Multitrac()

Multitrac::Multitrac(const string &config_path, Mat &frame, std::shared_ptr<Device> * device_, bool &ok)
{
    ok = true;
    this->config_path = config_path;
    cout << "Multitrac::Constructor BEGIN!" << endl;
    l_trac_ptr.emplace_back(make_shared<mtrac::TracContainer>(config_path, frame, device_, ok));
    INIReader reader(config_path);
    if (reader.ParseError() < 0)
    {
        cout << "ini reader parse error!\n";
        ok = false;
        return;
    } // END if(reader.ParseError() < 0)
    int roi_mode = 0, handle_flag = 0, get_rect_manual = 0, parallel = 0;
    ok &=  ext_ini::GetInteger(reader, "main_settings", "num_trac_max", num_trac_max);
    cout << "Multitrac::Constructor is " << ok << endl;
    return;
} // -- END Multitrac

void Multitrac::cmdHandler(uchar key) // обработка команд с клавиатуры
{
    if(key == 9) // tab: +1 pos_main
    {
        pos_main++;
        if(pos_main >= l_trac_ptr.size())
        {
            pos_main = 0;
        } // END if(pos_main >= l_trac_ptr.size())
    } // END if(key == 9)
    return;
} // -- END cmdHandler

bool Multitrac::add_trac(Rect2f & rectm, cv::Mat & frame_receive, cv::Mat & frame_show, std::shared_ptr<Device> * device_, int id_)
{
    bool init_trac = true; // проверим, есть ли неинициализированный трек в листе
    bool ok_init = false;
    cout << "dbg:: l_trac_size = " << l_trac_ptr.size() << endl;
    if(l_trac_ptr.size() >= num_trac_max) // если создано максимально допустимое число треков
    {
        for (auto trac: l_trac_ptr) // проверяем есть ли неинициализированные треки вы листе
        {
            init_trac &= trac->tracShats->isInited();
            if(!init_trac)          // если неинициализированный трек есть - инициализируем нужный участок в н1м
            {
                ok_init = trac->init_trac(rectm, frame_show);
                if(ok_init)
                {
                    trac->tracShats->trac_str.trac_id = id_;
                } // END if(ok_init)
                return ok_init;
            } // END if (!init_trac)
        } // END for (auto trac: l_trac_ptr)
        if (init_trac) // если все треки заняты - выозвращаем false
        {
            cout << "Multitrac::add_trac:: Have no !inited tracer in list!" << endl;
            return false;
        } // if (init_trac)
    } // END if(l_trac_ptr.size() > num_trac_max)
    else // если создано не максимальное число треков в листе
    {
        for (auto trac : l_trac_ptr) // проверяем есть ли неинициализированные треки вы листе
        {
            init_trac &= trac->tracShats->isInited();
            if(!init_trac)          // если неинициализированный трек есть - инициализируем нужный участок в н1м
            {
                ok_init = trac->init_trac(rectm, frame_show);
                if(ok_init)
                {
                    trac->tracShats->trac_str.trac_id = id_;
                } // END if(ok_init)
                //                if (ok_init) {iter_now = &trac;}
                cout << "dbg::Multitrack::add_trac::list size = " << l_trac_ptr.size() << endl;
                return ok_init;
            } // END if (!init_trac)
        } // END for (auto trac: l_trac_ptr)
        if(init_trac) // если все созданные треки заняты - добавляем в лист новый трек и инициализируем его
        {
            bool ok_create_trac = false;
            std::shared_ptr<mtrac::TracContainer> trac_new = make_shared<TracContainer>(config_path, frame_receive, device_, ok_create_trac);
            l_trac_ptr.emplace_back(trac_new);
            if (!ok_create_trac)
            {
                cout << "Multitrac::add_trac:: error, can't create new trac!" << endl;
                cout << "dbg::Multitrack::add_trac::list size = " << l_trac_ptr.size() << endl;
                return ok_create_trac;
            } // END if (!ok_create_trac)
            l_trac_ptr.back()->prepareFrameForTracShats(frame_receive);
            ok_init = l_trac_ptr.back()->init_trac(rectm, frame_show);
            if(ok_init)
            {
                l_trac_ptr.back()->tracShats->trac_str.trac_id = id_;
            } // END if(ok_init)
            cout << "dbg::Multitrack::add_trac::list size = " << l_trac_ptr.size() << endl;
            return ok_init;
        } // if (init_trac)
    } // END else
    return false; // функция не должна доходить до этого момента? return добавлен, чтобы убрать предупреждение компилятора
} // -- END add_trac

bool Multitrac::remove_trac() // удаление трекера на позиции pos_main или деинициализация нулевого элемента
{
    list<shared_ptr<TracContainer>>::iterator  iter_main = l_trac_ptr.begin();
    std::advance(iter_main, pos_main);
    if(l_trac_ptr.size() == 1) // Если в листе только один трек и он инициализирован- деинициализируем его
    {
        pos_main = 0;
        if(l_trac_ptr.back()->tracShats->isInited())
        {
            cout << "Deinit " << l_trac_ptr.size() - 1 << " trac(main trac)" << endl;
            l_trac_ptr.front()->tracShats->deinit();
        } // END if(l_trac_ptr.back()->tracShats->isInited())
    } // END if(l_trac_ptr.size() == 1)
    if(l_trac_ptr.size() > 1) // Если в листе больше одного трека - деинициализируем (если инициализирован) и удаляем последний в списке
    {
        if(iter_main.operator*()->tracShats->isInited())
        {
            iter_main.operator*()->tracShats->deinit();
            l_trac_ptr.erase(iter_main);
            cout << "Deinit and erase " << l_trac_ptr.size() - 1 << " trac(main trac)" << endl;
        } // END if(l_trac_ptr.back()->tracShats->isInited())
        else
        {
            l_trac_ptr.erase(iter_main);
            cout << "Erase " << l_trac_ptr.size() - 1 << " trac(main trac)" << endl;
        } // END else
        if(l_trac_ptr.size() == pos_main) {pos_main--;}
    } // END if(l_trac_ptr.size() > 1)
    return 1;
} // -- END remove_trac

void Multitrac::prepare_v_trac(cv::Mat & frame_receive)
{
    for(auto trac : l_trac_ptr)
    {
        trac->prepareFrameForTracShats(frame_receive);
    } // END for(auto trac : l_trac_ptr)
    return;
} // -- END prepare_v_trac

void Multitrac::set_new_frame(bool flag)
{
    for (auto trac : l_trac_ptr)
    {
        trac->tracShats->trac_str.new_frame = flag;
    } // END for (auto trac : l_trac_ptr)
} // -- END set_new_frame



void Multitrac::update(cv::Mat & frame_receive, cv::Mat & frame_show)
{
    int pos = 0;
    for(auto trac : l_trac_ptr)
    {
        trac->workflowShats(frame_receive, frame_show, pos, pos_main);
        pos++;
    } // END for(auto trac : l_trac_ptr)

    if(l_trac_ptr.size() > 1) // если размер листа больше 1 проверяем, инициализированны треки, если нет - удаляем "лишние"
    {
        pos = 0;
        std::vector<int> v_positions;
        for(auto trac : l_trac_ptr) // заполняем вектор номерами неинициализированных треков
        {
            if(!trac->tracShats->isInited())
            {
                v_positions.emplace_back(pos);
            } // END if(!trac->tracShats->isInited() && (l_trac_ptr.size() > 1))
            pos++;
        } // END for(auto trac : l_trac_ptr)
        if(v_positions.size()) {cout << "dbg::Multitrac::update: deinited l_trac_size = " << v_positions.size() << endl;}
        for(int i = v_positions.size() - 1; i >= 0; i--) // удаляем лишние элементы list, если размер листа больше 1
        {
            if(l_trac_ptr.size() > 1)
            {
                list<shared_ptr<TracContainer>>::iterator  iter_p = l_trac_ptr.begin();
                std::advance(iter_p, v_positions[i]);
                l_trac_ptr.erase(iter_p);
                if((v_positions[i] == pos_main) && (pos_main > 0)) {pos_main--;}
            } // END if(l_trac_ptr.size() > 1)
        } // END int i = v_positions.size() - 1; i >= 0; i--
    } // END if(l_trac_ptr.size > 1)
    return;
} // -- END update

}; // -- END namespace mtrac
