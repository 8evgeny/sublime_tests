#pragma once
#include "CThread.h"
#include "RadarDataConnector.h"
#include "main.h"
class Radar {
public:
    Radar(const Radar&) = delete;
    Radar(Radar&&) = delete;
    Radar& operator=(const Radar&) = delete;
    Radar& operator=(Radar&&) = delete;

public:
    explicit Radar();
    virtual ~Radar();

public:
    virtual void run(int64_t);
    virtual void stop();
    virtual void wait_shutdown();
    virtual void set_radar_id(const int64_t id);
    virtual void set_data_connector(const RadarDataConnector& data_connector);

protected:
    virtual RadarDataConnector get_data_connector() const;
    virtual void internal_thread_iteration() = 0;
    virtual int64_t get_radar_id() const;

private:
    CThread thread;
    bool is_runned_flag = false;
    //  RadarDataConnector data_connector = nullptr;
    std::shared_ptr<RadarDataConnector> data_connector = nullptr;
    int64_t radar_id = 0;
};

/*
5. Создать базовый класс радара.
Базовый класс обеспечивает функционирование внутреннего потока, вызов
переопределенного в потомке метода итерации потока.
Деструктор корректно останавливает внутренний поток.

Деструктор должен быть защищен от генерации исключений.
Обратить внимание на идеологию перехвата исключений во внутреннем
потоке — все исключения во внутреннем потоке не должны покидать его.

Метод run() неблокирующий, запускает работу внутреннего потока.
Требования к исключениям аналогичны классу потока.

Метод stop() сигнализирует о необходимости завершить работу внутреннего потока.
Неблокирующий, потокобезопасный.

Метод wait_shutdown() ожидает завершения работы внутреннего потока
(аналог метода join() класса потока).

Метод set_radar_id(const int64_t id) задает уникальный идентификатор
экземпляра радара.

Метод set_data_connector(const RadarDataConnector & data_connector)
задает приeмник сообщений радара.
Класс должен агрегировать экземпляр класса  CThread.
*/
