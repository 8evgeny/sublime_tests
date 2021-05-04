#pragma once
#include "RadarMessage.h"
#include "main.h"
class CoastalRadarMessage : public RadarMessage {
public:
    explicit CoastalRadarMessage();
    virtual ~CoastalRadarMessage() override;

public:
    bool is_data_valid() const override;
    struct Data {
        double x = 0;
        double y = 0;
        double z = 0;
        double sx = 0;
        double sy = 0;
        double sz = 0;
        double size = 0;
        int64_t timestamp = 0;
    } data;
};

/*
6.Создать класс сообщения берегового радара, унаследованный от сообщения радара.
Данные включают в себя координаты, вектор скорости (компоненты по осям),
размер объекта, и отметку времени сообщения, в миллисекундах.
*/
