#ifndef DISK_MONITOR_HPP
#define DISK_MONITOR_HPP

#include <string>

class DiskMonitor
{
public:
    DiskMonitor(const std::string &path2diskPart, bool &ok);
    long get_free_space_mb();
private:
    bool init = false;
    std::string disk_path;
    std::string check_free_memory_mb_cmd;
}; // -- DiskMonitor

#endif // DISK_MONITOR_HPP