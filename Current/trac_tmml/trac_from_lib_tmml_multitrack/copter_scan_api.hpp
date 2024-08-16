#pragma once
#include "copter_struct.hpp"

class copter_scan;

std::shared_ptr<copter_scan> create_copter_scan(const char* config_path,
                                                int fr_w0,
                                                int fr_h0,
                                                int img_orig_type,
                                                std::unique_ptr<std::list<trac_st>>& ltrac_ptr,
                                                std::unique_ptr<copter_struct>& cs_ptr, bool& ok);

int get_copter_scan(std::shared_ptr<copter_scan>& copt,
                    std::unique_ptr<std::list<trac_st>>& ltrac_ptr,
                    std::unique_ptr<copter_struct>& cs_ptr);
