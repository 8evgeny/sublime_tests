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

  private:
    std::string config_path{""};
    std::string patch_to_dataset{""};
    int height = 0;
    int width = 0;
    int num_images_load = 0;
    std::vector<std::string> vectorImagesPatch;
    std::vector<std::string> vectorLabelssPatch;


}; // END convert2cifar



