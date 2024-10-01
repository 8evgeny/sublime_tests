#include <iostream>
#include <string>
#include <iomanip>

#include "path_processing.hpp"

#include "esrt_api.hpp"
#include "paritel_telemetry_general.hpp"
#include "paritel_telemetry_multiplexor.hpp"

/*
    Приложение конвертирует множество ESRT файлов субтитров в множество PTD файлов.
    Один ESRT файл соответствует одному кадру и, следовательно, одному PTD файлу.
    Механизм преобразования в соответствии с механикой мультиплексора.
    Программа принимает путь к директории ESRT файлов
    и к директории, в которую сохраняются PTD файлы.
    P.S.    1) ESRT - Extern SRT. (SRT - SubRip Subtitle File - DJI definition)
            2) PTD - Paritel Telemetry Data (general format)
*/

std::string path2srcESRT_dir = "../test_data/DJI_0109_ESRT/";
std::string esrt_extension = "ESRT"; // расширение ESRT файла
std::string path2dstPTD_dir = "../test_data/DJI_109_PTD/";
std::string ptd_extension = "PTD";

bool force_replace = true; // принудительная очистка директории path2dstPTD_dir, если она не empty
bool make_dst_path = true; // автоматическое создание path2dstPTD_dir, если ее не существует по этому пути в файловой системе

int main(int argc, char* argv[])
{
    if(argc > 2)
    {
        path2srcESRT_dir = argv[1];
        path2dstPTD_dir = argv[2];
        std::cout << "NOTE: use terminal args" << std::endl;
    }

    std::cout << "\tpath2srcESRT_dir=" << path2srcESRT_dir << std::endl;
    std::cout << "\tpath2dstPTD_dir=" << path2dstPTD_dir << std::endl;

    if(!path_processing::isDirExist(path2srcESRT_dir))
    {
        std::cout << "ERROR: path2dstPTD_dir dir not exist" << std::endl;
        return 1;
    }

    if(path_processing::isDirEmpty(path2srcESRT_dir))
    {
        std::cout << "WARNING: path2dstPTD_dir empty dir" << std::endl;
        return 1;
    }

    if(!path_processing::isDirExist(path2dstPTD_dir))
    {
        if(make_dst_path)
        {
            if(!path_processing::makePath(path2dstPTD_dir))
            {
                std::cout << "ERROR: create path2dstPTD_dir failed" << std::endl;
                return 1;
            }
        }
        else
        {
            std::cout << "ERROR: path2dstPTD_dir not exist" << std::endl;
            return 1;
        }
    }

    if(!path_processing::isDirEmpty(path2dstPTD_dir))
    {
        if(force_replace)
        {
            std::cout << "WARNING: path2dstPTD_dir not empty. It will be clear before save new data!" << std::endl;
            if(!path_processing::cleanDir(path2dstPTD_dir))
            {
                std::cout << "ERROR: clear path2dstPTD_dir failed" << std::endl;
                return 1;
            }
        }
        else
        {
            std::cout << "ERROR: path2dstPTD_dir not empty" << std::endl;
        }
    }
    
    std::vector<std::string> src_dir_content_fullpaths;
    std::set<std::string> valid_exts = {esrt_extension};
    if(!path_processing::getDirFilesContent(path2srcESRT_dir, valid_exts, src_dir_content_fullpaths, true))
    {
        std::cout << "ERROR: call getDirFilesContent(..) failed" << std::endl;
        return 1;
    }

    size_t total_esrt = src_dir_content_fullpaths.size();
    int base_len = std::to_string(total_esrt).size();
    std::string esrt_fullpath, esrt_basename, esrt_clearname, telemetry_fullpath;
    ESRTdata esrt_tmp;
    ParitelTelemetryGen telemetry_tmp;
    for(size_t i = 0; i < src_dir_content_fullpaths.size(); ++i)
    {
        esrt_fullpath = src_dir_content_fullpaths[i];
        if(!path_processing::getBaseName(esrt_fullpath, esrt_basename))
        {
            std::cout << "ERROR: call getBaseName(...) failed:\n";
            std::cout << "\tpath=" << esrt_fullpath << std::endl;
            return 1;
        }

        std::cout << "i = " << std::setw(base_len) << std::setfill('0') << i << " / " << total_esrt << "; ";
        std::cout << "name=" << esrt_basename << std::endl;
        
        if(!path_processing::getClearName(esrt_fullpath, esrt_clearname))
        {
            std::cout << "ERROR: call getClearName(...) failed:\n";
            std::cout << "\t path=" << esrt_fullpath << std::endl;
            return 1;
        }

        telemetry_fullpath = path2dstPTD_dir + "/" + esrt_clearname + "." + ptd_extension;

        if(!parseESRT(esrt_fullpath, esrt_tmp))
        {
            std::cout << "ERROR: parseESRT(...) call failed" << std::endl;
            return 1;
        }

        telemetry_mux::conv_ESRT_to_TeleGen(esrt_tmp, telemetry_tmp);

        if(!telemetry_tmp.save2txt(telemetry_fullpath, false))
        {
            std::cout << "ERROR: call telemetry_tmp.save2txt failed:\n";
            std::cout << "\tpath=" << telemetry_fullpath << std::endl;
            return 1;
        }
    } // -- END for(size_t i = 0; i < src_dir_content_fullpaths.size(); ++i)

    std::cout << "END main" << std::endl;
    return 0;
} // -- END main
