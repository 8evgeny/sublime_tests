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

/*
4. Создать базовый класс для сообщения радара.
Метод is_data_valid() проверяет, содержит ли объект валидные данные.
Поле  radar_id содержит уникальный идентификатор радара — источника сообщения.
*/
