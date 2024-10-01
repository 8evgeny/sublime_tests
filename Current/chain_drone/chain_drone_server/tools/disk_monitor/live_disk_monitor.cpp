#include "live_disk_monitor.hpp"

LvDiskMonitor::LvDiskMonitor(
    const std::string &disk, 
    int check_step_ms, 
    bool &ok)
{
    check_step = chr::milliseconds(check_step_ms);
    bool ok1 = false;
    disk_monitor = std::make_shared<DiskMonitor>(disk, ok1);
    if(!ok1 || disk_monitor == nullptr)
    {
        std::cout << "ERROR: create DiskMonitor failed" << std::endl;
        ok = false;
        return;
    }
    sync.execute.store(true);
    std::thread thr(&LvDiskMonitor::exec, this);
    thr.detach();
    ok = true;
    sync.init.store(true);
} // -- LvDiskMonitor

void LvDiskMonitor::exec()
{
    while(sync.execute.load())
    {
        sync.fr_sp_mtx.lock();
        cur_free_space_mb = disk_monitor->get_free_space_mb() * 1'048'576 / 1e6;
        sync.fr_sp_mtx.unlock();
        std::this_thread::sleep_for(check_step);
    } // -- END while(execute)
    sync.exec_compl.store(true);
} // -- END exec

long LvDiskMonitor::get_free_space_mb()
{
    if(!sync.init.load())
    {
        return default_val;
    }
    sync.fr_sp_mtx.lock();
    long ret_val = cur_free_space_mb;
    sync.fr_sp_mtx.unlock();

    return ret_val;
} // -- END get_free_space_mb

bool LvDiskMonitor::quit()
{
    if(sync.quit_was_call.load())
    {
        return sync.success_quit.load();
    }
    sync.quit_was_call.store(true);
    sync.execute.store(false);

    chr::system_clock::time_point tp_lim = chr::system_clock::now();
    bool success = true;
    while(!sync.exec_compl.load())
    {
        if(tp_lim > chr::system_clock::now())
        {
            success = false;
            break; 
        }
    }
    if(!success)
    {
        std::cout << "ERROR: LvDiskMonitor quit failed" << std::endl;
        sync.success_quit.store(false);
        return false;
    }
    sync.success_quit.store(true);
    return true;
} // -- END quit