#include "convert2cifar.hpp"
using namespace std;
using namespace cv;
using namespace chrono;

convert2cifar::~convert2cifar(){cout << "Деструктор convert2cifar" << endl;}

convert2cifar::convert2cifar(const string & pathToConfig, bool &ok)
    : config_path(pathToConfig)
{
    cout << "config_path=" << config_path << endl;
    ok = get_ini_params(config_path);
    if(ok){cout << "get_ini_params ERROR!!!" << endl; return;}
}

bool convert2cifar::FileIsExist(const string& filePath)
{
    bool isExist = false;
    ifstream fin(filePath.c_str());
    if(fin.is_open()){isExist = true;}
    fin.close();
    return isExist;
} // -- END FileIsExist

bool convert2cifar::get_ini_params(const string &config)
{
    cout << "get_ini begin" << endl;
    setlocale(LC_NUMERIC, "en_US.UTF-8");

    bool configFileExists = FileIsExist(config);
    if(!configFileExists)
    {
        cout << "Config file '" << config << "' not exist!" << endl;
        return 1;
    }
    INIReader reader(config);
    if(reader.ParseError() < 0)
    {
        cout << "Can't load '" << config << "'\n";
        return 1;
    }
    width = reader.GetInteger("main_settings", "width", -1);
    if(width == 1)
    {
        cout << "width not declared!!" << endl;
        return 1;
    }
    cout << "width = " << width << ";\n";
    height = reader.GetInteger("main_settings", "height", -1);
    if(height == -1)
    {
        cout << "height not declared!!" << endl;
        return 1;
    }
    cout << "height = " << width << ";\n";
    patch_to_dataset = reader.Get("main_settings", "path_to_dataset", "");
    if(patch_to_dataset == "")
    {
        cout << "patch_to_dataset not declared" << endl;
        return 1;
    }
    cout << "patch_to_dataset = " << patch_to_dataset << ";\n";



    cout << "get_ini OK" << endl;
    return 0;
} // -- END get_ini_params
