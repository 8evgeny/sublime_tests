#include "recorder_srst.hpp"
#include <thread>
#include <iomanip>

namespace recorder
{

RecorderSRST::RecorderSRST(const RecorderSRSTSettings &_settings) : settings(_settings)
{

}
RecorderSRST::~RecorderSRST()
{

}
bool RecorderSRST::setup()
{
    if(!path_processing::isDirExist(settings.base.dir_path))
    {
        if(settings.base.make_path)
        {
            if(!path_processing::makePath(settings.base.dir_path))
            {
                return false;
            } // END if(!path_processing::makePath(settings.base.dir_path))
        } // END  if(settings.base.make_path)
        else
        {
            return false;
        } // END  if(!settings.base.make_path)
        
    } // END if(!path_processing::isDirExist(settings.base.dir_path))
    else
    {
        if(!path_processing::isDirEmpty(settings.base.dir_path))
        {
            if(settings.base.force_replace)
            {
                if(!path_processing::cleanDir(settings.base.dir_path))
                {
                    return false;
                } // END if(!path_processing::cleanDir(settings.base.dir_path))
            } // END if(settings.base.force_replace)
            else
            {
                return false;
            } // END else
        } // END if(!path_processing::isDirEmpty(settings.base.dir_path))
    } // END if(path_processing::isDirExist(settings.base.dir_path))

    if(!imgFormat2extension(settings.base.format, extension))
    {
        return false;
    } // END if(!imgFormat2extension(settings.base.format, extension))

    auto& compl_cnt = save_complete_counter;
    save_lambda = [&compl_cnt](cv::Mat frame, std::string path, std::vector<int> params)
    {
        if(cv::imwrite(path, frame, params))
        {
            ++compl_cnt;
        } // END if(cv::imwrite(path, frame, params))
        
        return;
    }; // END save_lambda = [&compl_cnt](cv::Mat frame, std::string path, std::vector<int> params)

    vec_params = settings.base.get_imwrite_params();

    is_configure = true;
    return true;
}


bool RecorderSRST::save(const cv::Mat &frame, const std::string &path)
{
    if(!is_configure)
    {
        return false;
    } // END if(!is_configure)
    ++save_started_counter;
    cv::Mat frame_buf = frame.clone();
    std::thread(save_lambda,frame_buf, path, vec_params).detach();
    return true;
}  // END RecorderSRST::save

bool RecorderSRST::save(const cv::Mat &frame, long frame_num)
{
    if(!is_configure)
    {
        return false;
    } // END if(!is_configure)
    std::string path = settings.base.dir_path + "/" + std::to_string(settings.base.base_value + frame_num) + "." + extension;
    return save(frame, path);
} // END bool RecorderSRST::save(const cv::Mat &frame, long frame_num)

void RecorderSRST::log()
{
    long complete = save_complete_counter.load();
    std::cout << "[COMPLETE] [BEGIN] [DIFF]= " 
        << "[" << std::setw(3) << complete                          << "] "
        << "[" << std::setw(3) << save_started_counter              << "] "
        << "[" << std::setw(2) << save_started_counter - complete   << "]" << std::endl;
} // END void RecorderSRST::log()

long RecorderSRST::getDiff()
{
    return save_started_counter - save_complete_counter.load();
} // END getDiff


bool RecorderSRST::quit()
{
    long total_wait_ms = settings.watchdog.complete_all_threads.wait_total_time;
    long delay_ms = settings.watchdog.complete_all_threads.check_delay_time;
    long time_counter = 0;
    bool success_wait = false;
    std::chrono::milliseconds delay_chr(delay_ms);
    int attempt_counter = 1;
    while(time_counter < total_wait_ms)
    {
        // std::cout << "TRY complete RecorderSRST. Try num=" << std::setw(3) << attempt_counter++ << std::endl;
        if(save_complete_counter == save_started_counter)
        {
            success_wait = true;
            break;
        }
        time_counter += delay_ms;
        std::this_thread::sleep_for(delay_chr);
    }
    if(!success_wait)
    {
        std::cout << "ERROR: fail RecorderSRST::quit(), the saving processes did not have time to complete" << std::endl;
    }
    else
    {
        std::cout << "SUCCESS complete RecorderSRST. Total quit time = " << time_counter << " (ms)" << std::endl;
    }
    return success_wait;
}

} // -- namespace recorder
