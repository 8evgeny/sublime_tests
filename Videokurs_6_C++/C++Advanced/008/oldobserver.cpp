#include "oldobserver.h"

#include <iostream>
#include <vector>

void Subject::attach( Observer* obs )
{
    m_views.push_back( obs );
}

void Subject::set_val( int value )
{
    m_value = value;
    notify();
}

void Subject::notify()
{
    for ( int i = 0; i < m_views.size(); ++i )
    {
        m_views[ i ]->update( m_value );
    }
}

DivObserver::DivObserver( Subject* model, int div )
{
    if ( model )
    {
        model->attach( this );
        m_div = div;
    }
}

void DivObserver::update( int v )
{
    std::cout << v << " div " << m_div << " is " << v / m_div << '\n';
}

ModObserver::ModObserver( Subject* model, int mod )
{
    if ( model )
    {
        model->attach( this );
        m_mod = mod;
    }
}

void ModObserver::update( int v )
{
    std::cout << v << " mod " << m_mod << " is " << v % m_mod << '\n';
}

void ClientOldObserver::run()
{
    Subject subj;
    DivObserver divObs1( &subj, 4 );
    DivObserver divObs2( &subj, 3 );
    ModObserver modObs3( &subj, 3 );
    subj.set_val( 14 );
}
