#pragma once
#include <fstream>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/predef.h> // Tools to identify the OS.
#include <boost/asio.hpp>
#include <thread>
#include <mutex>
#include <memory>
#include <iostream>

struct FILE_{
  std::string nameFile;
  int lenthFile; //в данной версии не используем - передаем фиктивное значение
  int need_send;
  bool servisePart = true;
  bool errorfix = true;
  bool fileSending=false;
};

void sendServicePart(FILE_ &, std::string , int );
