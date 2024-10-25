#include "gst_rtp_factory.hpp"

using namespace devices;
using namespace devices::gst_rtp;
using namespace std;

Settings devices::gst_rtp::readSettings(const std::string &pathToSettings, const  std::string & ini_section_name, bool &success)
{
    success = true;
    cout << "Begin readSettings in section [" << ini_section_name << "]\n";
    devices::gst_rtp::Settings settings;
    INIReader reader(pathToSettings);
    if (reader.ParseError() < 0)
    {
        cout << "ini reader parse error!\n";
        success = false;
        return settings;
    }

    namespace  ini = toolbox_utils::ini_reader_tool;

    cout << "dbg:: ini_section_name = " << ini_section_name << endl;
    ///SETTINGS.src
    success &= ini::Get(reader, ini_section_name, "ip", settings.src.ip);

    int temp_sensor_id = reader.GetInteger(ini_section_name, "sensor_id", -1);
    if (temp_sensor_id == -1)
    {
        std::cout << "\t sensor_id not declared!" << std::endl;
        success = false;
    }
    else
    {
        settings.sensor_id = temp_sensor_id;
        std::cout << "\t sensor_id = " << settings.sensor_id << ";\n";
    }

    int temp_camera_mode = reader.GetInteger(deviceName, "camera_mode", -1);
    if (temp_camera_mode == -1)
    {
        std::cout << "\t camera_mode not declared!" << std::endl;
        success = false;
    }
    else
    {
        settings.camera_mode = temp_camera_mode;
        std::cout << "\t camera_mode = " << settings.camera_mode << ";\n";
    }

    int temp_square_crop_sz = reader.GetInteger(deviceName, "square_crop_sz", -1);
    if (temp_square_crop_sz == -1)
    {
        std::cout << "\t square_crop_sz not declared!" << std::endl;
        success = false;
    }
    else
    {
        settings.square_crop_sz = temp_square_crop_sz;
        std::cout << "\t square_crop_sz = " << settings.square_crop_sz << ";\n";
    }

    int temp_fps_denominator = reader.GetInteger(deviceName, "fps_denominator", -1);
    if (temp_fps_denominator == -1)
    {
        std::cout << "\t temp_fps_denominator not declared!" << std::endl;
        success = false;
    }
    else
    {
        settings.fps_denominator = temp_fps_denominator;
        std::cout << "\t temp_fps_denominator = " << settings.fps_denominator << ";\n";
    }

    int temp_square_out_sz = reader.GetInteger(deviceName, "square_out_sz", -1);
    if (temp_square_out_sz == -1)
    {
        std::cout << "\t square_out_sz not declared!" << std::endl;
        success = false;
    }
    else
    {
        settings.square_out_sz = temp_square_out_sz;
        std::cout << "\t square_out_sz = " << settings.square_out_sz << ";\n";
    }

    int temp_max_buffers = reader.GetInteger(deviceName, "max_buffers", -1);
    if (temp_max_buffers == -1)
    {
        std::cout << "\t max_buffers not declared!" << std::endl;
        success = false;
    }
    else
    {
        settings.max_buffers = temp_max_buffers;
        std::cout << "\t max_buffers = " << settings.max_buffers << std::endl;
    }

    std::cout << "End " << deviceName << "::readSettings\n";
    success = true;
    return settings;
} // -- END readSettings(const std::string &pathToSettings)

bool devices::gst_rtp::checkValidAndAdaptationSettings(UserSettings &settings)
{
    std::string deviceName = "gst_rtp";
    std::cout << "Begin " << deviceName << "::checkValidAndAdaptationSettings\n";
    // pass 
    std::cout << "End " << deviceName << "::checkValidAndAdaptationSettings\n";
    return true;
} // -- END checkValidSettings(Settings settings)

std::shared_ptr<GstRtp> devices::gst_rtp::create(const std::string &config_path, const std::string & ini_section_name)
{
    bool success_rd_ini = false;
    devices::gst_rtp::UserSettings settings = readSettings(config_path, ini_section_name, success_rd_ini);
    if(!success_rd_ini)
    {
        return nullptr;
    }
    if(!checkValidAndAdaptationSettings(settings))
    {
        std::cout << "Error: settings gst_rtp not correct!" << std::endl;
    }
    std::shared_ptr<GstRtp> imx219device = std::make_shared<GstRtp>(settings);
    return imx219device;
} // -- END create(const std::string &config_path)
