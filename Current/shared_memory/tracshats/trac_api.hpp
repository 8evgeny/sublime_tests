#pragma once
#include "trac_struct.hpp"

class trac_tmml;

std::shared_ptr<trac_tmml> create_track(const char* config_path, // Путь к tracking.ini.
                       bool& ok, // Успешность выполнения create_trac (ok=0 -- неудачно, ok=1 -- успешно).
                       trac_struct& trac_st); // Структура алгоритма.

int get_trac(std::shared_ptr<trac_tmml>& trac);




