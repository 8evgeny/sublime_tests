#pragma once
#include "INIReader.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>


class convert2cifar
{
  public:
    convert2cifar(const std::string & pathToConfig, bool &ok);
    ~convert2cifar();
    bool get_ini_params(const std::string& config);
    bool FileIsExist(const std::string& filePath);


  private:
    std::string config_path{""};
    std::string patch_to_dataset{""};
    int height = 0;
    int width = 0;

}; // END convert2cifar



