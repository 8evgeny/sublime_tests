#pragma once
#include "INIReader.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>
#include <experimental/filesystem>

class convert2cifar
{
  public:
    convert2cifar(const std::string & pathToConfig, bool &ok);
    ~convert2cifar();
    bool get_ini_params(const std::string& config);
    bool FileIsExist(const std::string& filePath);
    int start();
    bool labelExists (const std::string& name);
    void showImage(cv::Mat imageCrop);

  private:
    std::string config_path{""};
    std::string patch_to_dataset{""};
    std::string patch_to_output{""};
    std::string output_extention{""};
    std::string name_dir_for_train{""};
    std::string name_dir_for_test{""};
    int width_height = 0;
    int num_images_load_train = 0;
    int num_images_load_test = 0;
    std::vector<std::string> vectorImagesPatch;
    std::vector<std::string> vectorLabelssPatch;

    int numClass;
    float imgX;
    float imgY;
    float imgW;
    float imgH;

}; // END convert2cifar



