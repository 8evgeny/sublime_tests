#pragma once
#include "main.h"

class object {
public:
    object();
    ~object();
    void readConfig(const char* conf_file);
    static void CreateObjects();
    struct ToRadar {
        double x = 0;
        double y = 0;
        double z = 0;
        double sx = 0;
        double sy = 0;
        double sz = 0;
        double size = 0;
        int64_t timestamp = 0;
    };
    ToRadar toRadar;
    void calculatePosition(ToRadar&);
    int periodCalculate { 1 };
    static const int numObj = 100; //Колл. объектов
private:
    boost::program_options::variables_map vm;
    struct Data {
        double x = 0;
        double y = 0;
        double z = 0;
        double v = 0;
        double kx = 0; // -1 - 1
        double ky = 0;
        double kz = 0;
        double size = 0;
        int64_t timestamp = 0;
    };
    Data _d;
};
