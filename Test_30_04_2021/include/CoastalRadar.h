#pragma once
#include "Radar.h"
#include "main.h"

class CoastalRadar : public Radar {
public:
    ~CoastalRadar();
    void internal_thread_iteration() override;

protected:
    //    virtual RadarDataConnector get_data_connector() const;
    //    virtual int64_t get_radar_id() const;
};
