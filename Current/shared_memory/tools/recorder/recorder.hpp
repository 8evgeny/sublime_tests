#ifndef RECORDER_HPP
#define RECORDER_HPP

#include <string>
#include <fstream>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "tools/INIReader.h"

class Recorder
{
public:
    Recorder(const std::string path, const std::string keyWord, bool &ok);
    bool init(int id = 0);
    void deinit();
    bool isInited();
    bool writeDescription(const cv::Rect2f rect);
    bool writeImage(const cv::Mat &image);
    void setFrameCounter(const int cnt);
    int getID();
    void deleteFiles();

private:
    bool getSettings(const std::string path_to_ini);
    inline bool checkDirectoryExist(const std::string path);
    bool writeDescription();
    cv::Rect2f descriptionRect;
    bool _isInited = false;
    int startFrameNum = 0;
    int lastFrameNUm = 1000000;
    int frameCnt = 0;
    std::string _keyWord = "";
    std::string pathImages;
    std::string pathDescriptor;
    std::string fullPathImages;
    std::string fullPathDescriptor;
    int _id = 0;

    const int startImageIndex = 1000000;
};

#endif // RECORDER_HPP
