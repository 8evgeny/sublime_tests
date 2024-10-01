#pragma once
#include "../tracshats/trac_struct.hpp"
#include <list>

class nnet;

std::shared_ptr<nnet> create_nnet(const char* config_path, // Путь к tracking.ini.
                                  bool& ok, // Успешность выполнения create_trac (ok=0 -- неудачно, ok=1 -- успешно).
                                  std::shared_ptr<std::list<trac_data>> &ltrac_data_ptr_,
                                  trac_struct& trac_st// Структура алгоритма.
                                  );

int get_nnet(std::shared_ptr<nnet>& trac);
