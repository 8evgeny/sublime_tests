#pragma once
#include "main.h"
#include "object.h"

class RadarDataConnector {
public:
    RadarDataConnector();
    ~RadarDataConnector();

    object::ToRadar getDataFromAllObject();
    void sendMessage();
};
