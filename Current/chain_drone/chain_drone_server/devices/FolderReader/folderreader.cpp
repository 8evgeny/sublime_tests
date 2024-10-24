#include "folderreader.h"

using namespace std;
using namespace cv;
using namespace chrono;

FolderReader::FolderReader()
{
    
}

FolderReader::FolderReader(const std::string& path_to_ini, bool& ok)
{
    ok = getSettings(path_to_ini);
    if(!ok){return;}

    if(num_fr_0 >= 0 && num_fr_0 < fileList.size())
    {
        firstFrameNum = num_fr_0;
        frame_id = firstFrameNum;
    }
    else
    {
        firstFrameNum = 0;
        frame_id = 0;
    }
    if(num_fr_1 > firstFrameNum && num_fr_1 <= fileList.size())
    {
        lastFrameNum = num_fr_1;
    }
    else
    {
        lastFrameNum = fileList.size();
    }

    cout << "firstFrameNum=" << firstFrameNum << "; lastFrameNum=" << lastFrameNum << endl;
    cout << "frame_id=" << frame_id << "/" << fileList.size() << endl;


    tp_get_fr = std::chrono::high_resolution_clock::now();
} // -- END FolderReader


void FolderReader::keyHandler(uchar &key)
{
    switch (key)
    {
    case 32:
        _pause = !_pause;
        break;
    default:
        break;
    }
} // -- END keyHandler

void FolderReader::start()
{
    if(parallel)
    {
        std::thread execution(&FolderReader::exec, this);
        execution.detach();
    }
} // -- END FolderReader

void FolderReader::workflow()
{
}


uint8_t *FolderReader::receiveFrame(int &w, int &h, int &id, int &num)
{
    if(frame_ready.load())
    {
        frame_mutex.lock();
        w = frame.cols;
        h = frame.rows;
        return frame.data;
        frame_mutex.unlock();
        frame_ready.store(false);
    }
    return nullptr;
} // -- END receiveFrame


void FolderReader::getFrame(cv::Mat& frame)
{
    tp_get_fr_cur = std::chrono::high_resolution_clock::now();
    delay_get_fr_ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp_get_fr_cur - tp_get_fr).count();
    if(delay_get_fr_ms < sourceFrameDelay_ms)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(sourceFrameDelay_ms - delay_get_fr_ms));
    }
    tp_get_fr = std::chrono::high_resolution_clock::now();
    getNextFrame(frame);
} // -- END getFrame

bool FolderReader::getFirstFrame(cv::Mat &frame)
{
    frame_id = firstFrameNum;
    bool success = getNextFrame(frame);
    frame_id = firstFrameNum;
    return success;
} // -- END getFirstFrame

int FolderReader::getFrameCounter()
{
    return frameCnt;
} // -- END getFrameCounter


int FolderReader::getColorChannels()
{
#if defined(CCM_8UC1)
    return 1;
#elif defined(CCM_8UC3)
    return 3;
#else
    return 0;
#endif
} // -- END getColorChannels


bool FolderReader::isBayerColorChannel()
{
    return false;
} // -- END isBayerColorChannel

#include "opencv2/highgui.hpp"

void FolderReader::getFormatedImage(uint8_t *f, int w, int h, int id, cv::Mat &image)
{

    cv::Mat img_buf = cv::Mat(Size(w,h), image.type());
#if defined(CCM_8UC1)
    memcpy(img_buf.data, f, img_buf.total());
#elif defined(CCM_8UC3)
    memcpy(img_buf.data, f, 3*img_buf.total());
#else
    throw std::runtime_error("Not supported color space for output format");
#endif

    Rect rct = Rect(round(0.5 * (w - h)), 0, h, h);
    image = img_buf(rct).clone();
    cv::resize(image, image, cv::Size(frame_w, frame_h));

}

void FolderReader::quit()
{
    if(parallel)
    {
        _execute.store(false, std::memory_order_release);
        std::this_thread::sleep_for(std::chrono::milliseconds(sourceFrameDelay_ms * 2));
    }
} // -- END getFormatedImage

int FolderReader::getId()
{
return frame_id;
} // END -- getId


void FolderReader::exec()
{
    _execute.store(true, memory_order_release);
    handle_frame_execute.store(true, memory_order_release);
    thread frameHandler(&FolderReader::runHandleFrame, this);
    WatchDog timer(1000);
    while(_execute.load(memory_order_acquire))
    {
        chrono::system_clock::time_point timePoint = chrono::system_clock::now() + chrono::milliseconds(sourceFrameDelay_ms);
        getNextFrame(frame);
        this_thread::sleep_until(timePoint);
        // std::this_thread::sleep_for(std::chrono::milliseconds(sourceFrameDelay_ms));
    } // -- END while(_execute.load(std::memory_order_acquire))
    handle_frame_execute.store(false, std::memory_order_release);
    frameCV.notify_one();
    frameHandler.join();
} // -- END exec

bool FolderReader::getSettings(const string& path_to_ini)
{
    cout << "Begin FolderReader::getSettings\n";

    INIReader reader(path_to_ini);
    if(reader.ParseError() < 0)
    {
        cout << "ini reader parse error!\n";
        return 0;
    }

    parallel = reader.GetInteger("main_settings", "parallel", -1);
    if(parallel == -1)
    {
        cout << "parallel not declared!!" << endl;
        return 0;
    }
    else
    {
        cout << "parallel = " << parallel << ";\n";
    }

    repeat = reader.GetInteger("folder", "repeat", -1);
    if(repeat == -1)
    {
        cout << "ini reader parse error: repeat not found!\n";
        return 0;
    }
    else
    {
        cout << "repeat=" << repeat << "\n";
    }

    num_fr_0 = reader.GetInteger("folder", "num_fr_0", -1);
    if (num_fr_0 == -1)
    {
        cout << "ini reader: Parse source num_fr_0 name error\n";
        return 0;
    }
    else
    {
        cout << "num_fr_0=" << num_fr_0 << endl;
    }

    num_fr_1 = reader.GetInteger("folder", "num_fr_1", -1);
    if (num_fr_1 == -1)
    {
        cout << "ini reader: Parse source num_fr_1 name error\n";
        return 0;
    } // END if (num_fr_1 == -1)
    else
    {
        cout << "num_fr_1=" << num_fr_1 << endl;
    } // END else

    frame_w = reader.GetInteger("folder", "frame_w", -1);
    if (frame_w == -1)
    {
        cout << "ini reader: Parse source frame_w name error\n";
        return 0;
    } // END if (frame_w == -1)
    else
    {
        cout << "frame_w=" << frame_w << endl;
    } // END else

    frame_h = reader.GetInteger("folder", "frame_h", -1);
    if (frame_h == -1)
    {
        cout << "ini reader: Parse source frame_h name error\n";
        return 0;
    } // END if (frame_h == -1)
    else
    {
        cout << "frame_h=" << frame_h << endl;
    } // END else


    int fps = reader.GetInteger("folder", "fps", -1);
    if(fps == -1)
    {
        cout << "ini reader: Parse source fps name error\n";
        return 0;
    } // END if(fps == -1)
    else
    {
        if(fps != 0)
        {
            sourceFrameDelay_ms = 1000 / fps;
        } // END if(fps != 0)
        else
        {
            sourceFrameDelay_ms = 0;
        } // END else
        cout << "fps=" << fps << endl;
    } // END else

#ifdef USE_ESRT
    path2esrt = reader.Get("folder", "path2esrt", "oops");
    if(path2esrt == "oops"){std::cout << "folder path2esrt not declared!\n"; return 0;}
    else{cout << "path2esrt = " << path2esrt << ";\n";}
#endif // USE_ESRT

#ifdef USE_TELETXT
    path2teletxt = reader.Get("folder", "path2teletxt", "oops");
    if(path2teletxt == "oops"){std::cout << "folder path2teletxt not declared!\n"; return 0;}
    else{cout << "path2teletxt = " << path2teletxt << ";\n";}
#endif // USE_TELETXT

    path = reader.Get("folder", "path", "oops");
    if(path == "oops"){std::cout << "folder path not declared!\n"; return 0;}
    else{cout << "folder_path = " << path << ";\n";}

    bool folder_path_ok = getFileList(path, fileList);
    if(!folder_path_ok)
    {
        cout << "WRONG folder_path OR folder is EMPTY !\n";
        return 0;
    } // -- END if(!folder_path_ok)


    // colorChannelsNum = reader.GetInteger(yolo_block, "color_channels", -1);
    // if(colorChannelsNum == -1)
    // {
    //     cout << "ini reader parse warning: color_channels not found!\n";
    //     return 0;
    // }
    // else
    // {
    //     cout << "colorChannelsNum=" << colorChannelsNum << endl;
    // }
    cout << "END FolderReader::getSettings\n";
    return 1;
} // -- END getSettings


bool FolderReader::getFileList(std::string& path, std::vector<std::string>& fileList)
{
    fileList.clear();
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path.c_str())) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            string filename = string(ent->d_name);
            // -- typ = 4 (folder), typ = 8 (file).
            if (ent->d_type == 8 && filename != "." && filename != "..")
            {
                fileList.emplace_back(filename);
            }
        } // -- END while((ent = readdir (dir)) != NULL)
        closedir(dir);
        std::sort(fileList.begin(), fileList.end());
        if(fileList.size())
        {
            return true;
        }
    } // -- END if((dir = opendir(way)) != NULL)
    cout << "Dir " << path << " can't open or empty!" << endl;
    return false;
} // -- END getFileList



bool FolderReader::FileIsExist(const string& filePath)
{
    bool isExist = false;
    std::ifstream fin(filePath.c_str());
    if(fin.is_open()){isExist = true;}
    fin.close();
    return isExist;
} // -- END FileIsExist


bool FolderReader::getNextFrame(cv::Mat& frame)
{
    if(frame_id < lastFrameNum)
    {
        string filename = path + "/" + fileList[frame_id];
        //cout << "filename=" << filename << endl;
        if(!FileIsExist(filename))
        {
            cout << "filename=" << filename << " DON't Exist!" << endl;
            return 0;
        } // -- END if(!FileIsExist(filename))

        // cout << "frame_id=" << frame_id << "/" << lastFrameNum << "; name=" << fileList[frame_id] << std::endl;
        frame_id++;
        //            std::scoped_lock guard(frame_mutex);
#if defined(CCM_8UC1)
        frame = imread(filename, cv::ImreadModes::IMREAD_GRAYSCALE);
#elif defined(CCM_8UC3)
        frame = imread(filename, cv::ImreadModes::IMREAD_COLOR);
#else
        throw std::runtime_error("Not supported color space for output format");
#endif
        if(!frame.data)
        {
            cout << "NOT data for filename=" << filename << endl;
        }
        frame_ready.store(true, memory_order_release);
        frameCV.notify_one();
        return 1;
        // -------------- END if(frame_id < lastFrameNum)
    } // END if(frame_id < lastFrameNum)
    else
    {
        if(repeat == 0)
        {
            END_FileList = 1;
            std::cout << "END FileList!" << std::endl;
            exit(0);
            return 0;
        } // -- END if(repeat == 0)

        if(firstFrameNum >= 0 && firstFrameNum < fileList.size())
        {
            frame_id = firstFrameNum;
        }
        else
        {
            frame_id = 0;
        }
        return 1;
    } // -- END if(frame_id >= lastFrameNum)
    return 0;
} // -- END getNextFrame

bool FolderReader::getState()
{
    return 1;
} // END getState

void FolderReader::runHandleFrame()
{
    while(handle_frame_execute.load(std::memory_order_acquire))
    {
        std::unique_lock<std::mutex> lk(frame_mutex);
        frameCV.wait(lk);
        if(!handle_frame_execute.load(std::memory_order_acquire))
        {
            break;
        }
        for(auto handler : frame_handlers)
        {
            handler->handle(frame.data, frame.cols, frame.rows, 0, 0);
        } // -- END for(auto handler : frame_handlers)
        lk.unlock();
        frame_ready.store(false, std::memory_order_release);
    } // -- END while
} // -- END runHandleFrame

bool FolderReader::loadFirstLastFrameNum(std::string path)
{
    std::ifstream f_in(path);
    if(!f_in.is_open())
    {
        std::cout << "File " << path << " NOT open!" << std::endl;
        return false;
    } // -- END if(!f_in.is_open())
    std::string item0, item1, item2, item3, item4, item5;

    f_in >> item0; // Безразмерная x-координата центра объекта в единицах ширины фрейма,
    f_in >> item1; // Безразмерная y-координата центра объекта в единицах высоты фрейма,
    f_in >> item2; // Безразмерная полуширина прямоугольника цели в единицах ширины фрейма,
    f_in >> item3; // Безразмерная полувысота прямоугольника цели в единицах высоты фрейма,
    f_in >> item4; // Номер первого фрейма,
    f_in >> item5; // Номер последнего фрейма.
    f_in.close();
    firstFrameNum = std::stoi(item4);
    lastFrameNum = std::stoi(item5);
    frameCnt = firstFrameNum;
    return true;
} // -- END loadFirstLastFrameNum
