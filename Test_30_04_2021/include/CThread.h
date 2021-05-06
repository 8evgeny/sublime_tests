#pragma once
#include "main.h"

class CThread {
public:
    CThread(const CThread&) = delete;
    CThread(CThread&&) = delete;
    CThread& operator=(const CThread&) = delete;
    CThread& operator=(CThread&&) = delete;

public:
    explicit CThread();
    virtual ~CThread();

public:
    virtual void run();
    virtual void stop();
    virtual void join();
    virtual void set_iteration_period_milliseconds(const int64_t period);
    virtual void set_iteration_callback(const std::function<void()>& on_iteration_callback);
    void run_without_iteration();

private:
    void shutdown();

private:
    std::atomic_bool stop_flag { false };
    int64_t period_ms = 20;
    std::shared_ptr<std::thread> thread = nullptr;
    std::function<void()> on_iteration_callback = nullptr;
};

/*
3. Создать класс CThread, инкапсулирующий стандартный поток C++.
Деструктор должен корректно останавливать работающий поток, не генерировать исключения.

Метод run() - неблокирующий, запускает внутренний поток. При невозможности корректно
запустить поток, генерирует исключение. При нормальном запуске потока возвращает
управление вызвавшему коду.

Метод stop() - неблокирующий, потокобезопасный. Сигнализирует объекту о необходимости
завершить работу внутреннего потока, без фактического ожидания остановки.

Метод join() предназначен для ожидания фактического завершения работы потока
после подачи сигнала остановки вызовом stop().

Метод set_iteration_period_milliseconds(const int64_t period) задает период
вызова внешней callback — функции, в миллисекундах.

Метод set_iteration_callback(const std::function<void()> & on_iteration_callback)
задает callback — функциию, которую объект будет вызывать каждые period миллисекунд.

Например, period равен 50 миллисекундам. Если  on_iteration_callback
выполнил свою работу за 1 миллисекунду, следующий вызов  on_iteration_callback
произойдет через 49 миллисекунд. Если  on_iteration_callback выполнил свою
работу за 30 миллисекунд, следующий вызов  on_iteration_callback произойдет
через 20 миллисекунд. Если  on_iteration_callback выполнил свою работу за 60
миллисекунд, следующий вызов  on_iteration_callback произойдет немедленно, без
паузы. Высокая точность не требуется, желаемый период задается примерно,
фактически интервалы вызовов зависят от работы планировщика ядра ОС, пытаться
обеспечить точность не нужно.
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   Жизненный цикл объекта:
Жизненный цикл объекта:
 СThread thread;
 thread.set_iteration_period_milliseconds(50);
 thread.set_iteration_callback(callback);
 thread.run();

Из этого же, или из другого потока может быть вызван stop()

Этот же поток:
 thread.stop();
 thread.join();
*/
