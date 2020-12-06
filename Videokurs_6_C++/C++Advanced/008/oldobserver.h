#ifndef OLDOBSERVER_H
#define OLDOBSERVER_H

#include "meta_strategy.h"
#include <iostream>
#include <vector>

class Observer
{
public:
    Observer() = default;
    virtual ~Observer() = default;
    virtual void update( int value ) = 0;
};

class Subject
{
    int m_value;
    std::vector< Observer* > m_views;

public:
    void attach( Observer* obs );
    void set_val( int value );
    void notify();
};

class DivObserver : public Observer
{
    int m_div;

public:
    DivObserver( Subject* model, int div );

    void update( int v ) override;
};

class ModObserver : public Observer
{
    int m_mod;

public:
    ModObserver( Subject* model, int mod );
    void update( int v ) override;
};

class ClientOldObserver : public MetaStrategy
{
public:
    void run() override;
};

#endif // OLDOBSERVER_H
