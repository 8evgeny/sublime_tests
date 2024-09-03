#include "convert2cifar.hpp"
using namespace std;
using namespace cv;
using namespace chrono;
namespace fs = experimental::filesystem;

convert2cifar::~convert2cifar(){cout << "\ndtor convert2cifar" << endl;}

convert2cifar::convert2cifar(const string & pathToConfig, bool &ok)
    : config_path(pathToConfig)
{
    cout << "ctor convert2cifar\n" << endl;
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
    width_height = reader.GetInteger("main_settings", "width_height", -1);
    if(width_height == 1)
    {
        cout << "width_height not declared!!" << endl;
        return 1;
    }
    cout << "width_height = " << width_height << ";\n";
    patch_to_dataset = reader.Get("main_settings", "path_to_dataset", "");
    if(patch_to_dataset == "")
    {
        cout << "patch_to_dataset not declared" << endl;
        return 1;
    }
    cout << "patch_to_dataset = " << patch_to_dataset << ";\n";
    num_images_load = reader.GetInteger("main_settings", "num_images_load", -1);
    if(num_images_load == -1)
    {
        cout << "num_images_load not declared!!" << endl;
        return 1;
    }
    cout << "num_images_load = " << num_images_load << ";\n";


    cout << "get_ini OK" << endl;
    return 0;
} // -- END get_ini_params

inline bool exists (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

int convert2cifar::start()
{
    cout << "start convert...\n\n" ;

    int i = 0;
    fs::path imagePath;
    string labelName;
    string stringlabelPatch;
    ifstream fin;
    Mat image;
    int centerX = 0;
    int centerY = 0;
    Point lh;
    Point rd;
    namedWindow( "image_window", WINDOW_AUTOSIZE );

    for (auto & p : fs::directory_iterator(patch_to_dataset + "/images"))
    {

        imagePath = p;
        vectorImagesPatch.push_back(imagePath.fs::path::generic_string());
        stringlabelPatch = imagePath.parent_path().parent_path().append("/labels/");
        labelName = imagePath.stem();
        labelName.append(".txt");
        stringlabelPatch.append(labelName);
        if (!exists(stringlabelPatch))
        {
          cout << "label not exist: "<< stringlabelPatch << endl;
          return 0;
        }
        vectorLabelssPatch.push_back(stringlabelPatch);

        fin.open(vectorLabelssPatch[i]);
        fin>>numClass>>imgX>>imgY>>imgW>>imgH;
        fin.close();

        cout <<numClass<<" "<<imgX<<" "<<imgY<<" "<<imgW<<" "<<imgH<<endl;

        centerX = (int)(256 * imgX);
        centerY = (int)(256 * imgY);
        lh = Point((centerX - width_height /2), (centerY - width_height /2));
        rd = Point((centerX + width_height /2), (centerY + width_height /2));
        image = imread(vectorImagesPatch[i], IMREAD_UNCHANGED);
        rectangle(image, lh, rd, Scalar(0,0,255), 3);
        imshow("image_window", image );
        waitKey(0);

        --num_images_load;
        ++i;
        if (num_images_load == 0) break;
    }

    cout<< "Images:" << endl;
    for (auto &i:vectorImagesPatch)
        cout<< i << endl;

    cout<< "\nLabels:" << endl;
    for (auto &i:vectorLabelssPatch)
        cout<< i << endl;




    return 0;
}// -- END start
