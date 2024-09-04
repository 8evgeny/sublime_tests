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
    patch_to_dataset = reader.Get("main_settings", "patch_to_dataset", "");
    if(patch_to_dataset == "")
    {
        cout << "patch_to_dataset not declared" << endl;
        return 1;
    }
    cout << "patch_to_dataset = " << patch_to_dataset << ";\n";
    patch_to_output = reader.Get("main_settings", "patch_to_output", "");
    if(patch_to_output == "")
    {
        cout << "patch_to_output not declared" << endl;
        return 1;
    }
    cout << "patch_to_output = " << patch_to_output << ";\n";
    output_extention = reader.Get("main_settings", "output_extention", "");
    if(output_extention == "")
    {
        cout << "output_extention not declared" << endl;
        return 1;
    }
    cout << "output_extention = " << output_extention << ";\n";
    name_dir_for_train = reader.Get("main_settings", "name_dir_for_train", "");
    if(name_dir_for_train == "")
    {
        cout << "name_dir_for_train not declared" << endl;
        return 1;
    }
    cout << "name_dir_for_train = " << name_dir_for_train << ";\n";
    name_dir_for_test = reader.Get("main_settings", "name_dir_for_test", "");
    if(name_dir_for_test == "")
    {
        cout << "name_dir_for_test not declared" << endl;
        return 1;
    }
    cout << "name_dir_for_test = " << name_dir_for_test << ";\n";
    num_images_load_train = reader.GetInteger("main_settings", "num_images_load_train", -1);
    if(num_images_load_train == -1)
    {
        cout << "num_images_load_train not declared!!" << endl;
        return 1;
    }
    cout << "num_images_load_train = " << num_images_load_train << ";\n";
    num_images_load_test = reader.GetInteger("main_settings", "num_images_load_test", -1);
    if(num_images_load_test == -1)
    {
        cout << "num_images_load_test not declared!!" << endl;
        return 1;
    }
    cout << "num_images_load_test = " << num_images_load_test << ";\n";

    cout << "get_ini OK" << endl;
    return 0;
} // -- END get_ini_params

bool convert2cifar::labelExists (const std::string& name)
{
    ifstream f(name.c_str());
    return f.good();
}

void convert2cifar::showImage(Mat imageCrop)
{
    namedWindow( "image_window", WINDOW_AUTOSIZE );
    imshow("image_window", imageCrop );
    waitKey(0);
}

int convert2cifar::start()
{
    cout << "start convert...\n\n" ;

    int i = 0;
    int all_num_images = num_images_load_train + num_images_load_test;
    bool images_for_train = true;
    bool images_for_test = false;
    fs::path imagePath;
    string labelName;
    string stringlabelPatch;
    ifstream fin;
    Mat imageOrigin;
    Mat imageCrop;
    int centerX = 0;
    int centerY = 0;
    Point lh;
    Point rd;

    string cmd1 = "mkdir -p " + patch_to_output + "/" + name_dir_for_train;
    system(cmd1.c_str());
    string cmd2 = "mkdir -p " + patch_to_output + "/" + name_dir_for_test;
    system(cmd2.c_str());

    for (auto & p : fs::directory_iterator(patch_to_dataset + "/images"))
    {
        imagePath = p;
        vectorImagesPatch.push_back(imagePath.fs::path::generic_string());
        stringlabelPatch = imagePath.parent_path().parent_path().append("/labels/");
        labelName = imagePath.stem();
        labelName.append(".txt");
        stringlabelPatch.append(labelName);
        if (!labelExists(stringlabelPatch))
        {
          cout << "label not exist: "<< stringlabelPatch << endl;
          return 0;
        }
        vectorLabelssPatch.push_back(stringlabelPatch);

        fin.open(vectorLabelssPatch[i]);
        fin>>numClass>>imgX>>imgY>>imgW>>imgH;
        fin.close();
        centerX = (int)(256 * imgX);
        centerY = (int)(256 * imgY);
        lh = Point((centerX - width_height /2), (centerY - width_height /2));
        rd = Point((centerX + width_height /2), (centerY + width_height /2));
        imageOrigin = imread(vectorImagesPatch[i], IMREAD_UNCHANGED);
        Rect rec(lh, rd);
        imageCrop = imageOrigin(rec);

        if(images_for_train)
        {
            //Сохраняем вырезанную область в новый файл
            string patch = patch_to_output + "/" + name_dir_for_train + "/";
            patch.append(to_string(i));
            patch.append(".");
            patch.append(output_extention);
            imwrite(patch, imageCrop);
//            showImage(imageCrop);
        }
        if(images_for_test)
        {
            string patch = patch_to_output + "/" + name_dir_for_test + "/";
            patch.append(to_string(i));
            patch.append(".");
            patch.append(output_extention);
            imwrite(patch, imageCrop);
//            showImage(imageCrop);
        }
        --all_num_images;
        ++i;
        if (all_num_images == num_images_load_test)
        {
            images_for_train = false;
            images_for_test = true;
        }
        if (all_num_images == 0)
        {
            break;
        }

    }//END for (auto & p : fs::directory_iterator(patch_to_dataset + "/images"))
    return 0;
}// -- END start
