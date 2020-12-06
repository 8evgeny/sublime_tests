#ifndef MODERNOBSERVER_H
#define MODERNOBSERVER_H

#include "meta_strategy.h"
#include <functional>
#include <iostream>
#include <vector>

class ModernObserver
{
public:
    typedef std::function< void( int ) > UpdateDelegate;
    ModernObserver( UpdateDelegate updateDelegate );

    ~ModernObserver() = default;

    void update( int value );

protected:
    UpdateDelegate updateDelegate;
};

class ModernSubject
{
    int m_value;
    std::vector< ModernObserver > m_views;

public:
    void attach( const ModernObserver& obs );
    void set_val( int value );
    void notify();
};

class ModernDivObserver
{
    int m_div;

public:
    ModernDivObserver( ModernSubject* model, int div );

    void update( int v );
};

class ModernModObserver
{
    int m_mod;

public:
    ModernModObserver( ModernSubject* model, int mod );
    void update( int v );
};

class ClientModernObserver : public MetaStrategy
{
public:
    void run() override;
};

#endif // MODERNOBSERVER_H
