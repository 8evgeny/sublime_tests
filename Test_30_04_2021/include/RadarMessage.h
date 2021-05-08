#pragma once
#include "main.h"

class RadarMessage {
public:
    explicit RadarMessage();
    virtual ~RadarMessage();

public:
    virtual bool is_data_valid() const = 0;

public:
    int64_t radar_id = 0;
};
