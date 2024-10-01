#ifndef RECORDER_BASE_HPP
#define RECORDER_BASE_HPP

#include <string>
#include <opencv2/opencv.hpp>

namespace recorder
{

enum ImageFormats : int
{
    IMG_FORMAT_PNG = 0,
    IMG_FORMAT_JPEG = 1,
    IMG_FORMAT_BMP = 2,
    /* ################ */
    LATEST_ELEMENT = 3
};

inline bool imgFormat2extension(ImageFormats f_format, std::string &ext)
{
    std::string default_ext = "error";
    switch(f_format)
    {
        case IMG_FORMAT_PNG:
            ext = "png";
            break;
        case IMG_FORMAT_JPEG:
            ext = "jpeg";
            break;
        case IMG_FORMAT_BMP:
            ext = "bmp";
            break;
        default:
            ext = default_ext;
    };
    if(ext == default_ext)
    {
        return false;
    }
    return true;
} // -- imgFormat2extension

struct PngSettings
{
    int compress_value = 1; // Более высокое значение означает меньший размер и большее время сжатия.
};

struct JpegSettings
{
    int quality = 95;
};

struct RecorderBaseSettings
{
    std::string     dir_path        = "~/test_recorder/";       
    long            base_value      = 1e7; // if base_val=1e3, frame_num=15, format=jpeg -> frame name = 1015.jpg
    bool            force_replace   = false;
    bool            make_path       = true; // create dir if not exist

    ImageFormats    format          = IMG_FORMAT_PNG;

    PngSettings     png;
    JpegSettings    jpeg;
    std::vector<int> get_imwrite_params()
    {
        std::vector<int> params = {};
        if(format == IMG_FORMAT_PNG)
        {
            params = {cv::IMWRITE_PNG_COMPRESSION, png.compress_value};
        }
        else if(format == IMG_FORMAT_JPEG)
        {
            params = {cv::IMWRITE_JPEG_QUALITY, jpeg.quality};
        }
        return params;
    }
};

class RecorderBase
{
public:
    RecorderBase() {};
    virtual ~RecorderBase() {};
    virtual bool setup() {recorder_error("setup"); return false;}
    virtual bool save(const cv::Mat &frame, const std::string &path) {recorder_error("save(Mat,string)"); return false;}
    virtual bool save(const cv::Mat &frame, long frame_num) {recorder_error("save(Mat,long)"); return false;}
    virtual void log() {recorder_error("log"); return;}
    virtual bool quit() {recorder_error("quit"); return false;}
    virtual long getDiff() {return 0;};

protected:
    bool                is_configure    = false;
    std::vector<int>    vec_params;
    std::string         extension;
private:
    void recorder_error(const std::string &msg)
    {
        throw std::runtime_error("No command \"" + msg + "\" for this recorder");
    }
}; // -- class RecorderBase

} // -- namespace recorder

#endif //RECORDER_BASE_HPP
