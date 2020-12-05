#include "modernobserver.h"

#include <functional>
#include <iostream>
#include <vector>

ModernObserver::ModernObserver( UpdateDelegate updateDelegate )
    : updateDelegate( updateDelegate ){};

void ModernObserver::update( int value )
{
    if ( updateDelegate )
    {
        updateDelegate( value );
    }
}

void ModernSubject::attach( const ModernObserver& obs )
{
    m_views.push_back( obs );
}

void ModernSubject::set_val( int value )
{
    m_value = value;
    notify();
}

void ModernSubject::notify()
{
    for ( auto& it : m_views )
    {
        it.update( m_value );
    }
}

ModernDivObserver::ModernDivObserver( ModernSubject* model, int div )
{
    ModernObserver observer( std::bind( &ModernDivObserver::update, this, std::placeholders::_1 ) );
    if ( model )
    {
        model->attach( observer );
        m_div = div;
    }
}

void ModernDivObserver::update( int v )
{
    std::cout << v << " div " << m_div << " is " << v / m_div << '\n';
}

ModernModObserver::ModernModObserver( ModernSubject* model, int mod )
{
    ModernObserver observer( std::bind( &ModernModObserver::update, this, std::placeholders::_1 ) );
    if ( model )
    {
        model->attach( observer );
        m_mod = mod;
    }
}

void ModernModObserver::update( int v )
{
    std::cout << v << " mod " << m_mod << " is " << v % m_mod << '\n';
}

void ClientModernObserver::run()
{
    ModernSubject subj;
    ModernDivObserver divObs1( &subj, 4 );
    ModernDivObserver divObs2( &subj, 3 );
    ModernModObserver modObs3( &subj, 3 );
    subj.set_val( 14 );
}
