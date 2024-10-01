#include "disk_monitor.hpp"
#include <array>
#include <memory>
#include <iostream>
#include <vector>

/*
Функция подрезает символ ch с правой и левой сторон строки, по умолчанию ch = ' ' - пробел
*/
int strip(std::string &str, char ch)
{
    int lcnt = 0, rcnt = 0;
    int n = str.length();
    while (str[lcnt] == ch)
        lcnt++;
    while (str[n - 1 - rcnt] == ch)
        rcnt++;
    if (lcnt)
    {
        str.erase(str.begin(), str.begin() + lcnt);
    }
    if(rcnt)
    {
        str.erase(str.end() - rcnt, str.end());
    }
    return lcnt + rcnt;
} // -- END strip

std::string cmd_catch_return(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    result.pop_back();
    return result;
} // -- END cmd_catch_return

DiskMonitor::DiskMonitor(const std::string &path2diskPart, bool &ok) : disk_path(path2diskPart)
{
    std::string _cmd = "ls " + disk_path;
    std::string _res = cmd_catch_return(_cmd.c_str());
    check_free_memory_mb_cmd = "df " + disk_path + " -hm --output=avail | tail -n +2";

    // test first try
    try
    {
        std::string _res = cmd_catch_return(check_free_memory_mb_cmd.c_str());
        strip(_res, ' ');
        long _val = std::stol(_res);
    }
    catch(const std::exception& e)
    {
        ok = false;
        std::cout << "ERROR: create disk_monitor failed!" << std::endl;
        // std::cerr << e.what() << '\n';
        return;
    }
    
    ok = true;
    init = true;
} // -- END DiskMonitor

long DiskMonitor::get_free_space_mb()
{
    if(!init)
    {
        return -1;
    }
    std::string _res = cmd_catch_return(check_free_memory_mb_cmd.c_str());
    strip(_res, ' ');
    return std::stol(_res);
} // -- END get_free_space_mb