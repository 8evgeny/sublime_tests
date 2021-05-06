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

/*
7. Создать класс берегового радара, унаследованный от класса радара.
Переопределить метод internal_thread_iteration().
В классе реализовать следующую логику:
каждые 100 мс радар посылает приемнику сообщение с координатами, размером объекта,
вектором скорости и отметкой времени.
Обратить внимание на потокобезопасность при передаче сообщения.
Объект, данные которого передаются радаром, должен совершать эволюции в пространстве —
перемещаться по какой-нибудь траектории в пределах куба размерами 100 х 100 х 100 м.
*/
