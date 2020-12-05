#include "builder.h"

#include "meta_strategy.h"
#include <iostream>
#include <memory>
#include <string>

using namespace std;

void Pizza::setDough( const string& dough )
{
    m_dough = dough;
}

void Pizza::setSauce( const string& sauce )
{
    m_sauce = sauce;
}

void Pizza::setTopping( const string& topping )
{
    m_topping = topping;
}

void Pizza::open() const
{
    cout << "Pizza with " << m_dough << " dough, " << m_sauce << " sauce and " << m_topping
         << " topping. Mmm." << endl;
}

Pizza* PizzaBuilder::getPizza()
{
    return m_pizza.release();
}

void PizzaBuilder::createNewPizzaProduct()
{
    m_pizza = make_unique< Pizza >();
}

void HawaiianPizzaBuilder::buildDough()
{
    m_pizza->setDough( "cross" );
}
void HawaiianPizzaBuilder::buildSauce()
{
    m_pizza->setSauce( "mild" );
}
void HawaiianPizzaBuilder::buildTopping()
{
    m_pizza->setTopping( "ham+pineapple" );
}

void SpicyPizzaBuilder::buildDough()
{
    m_pizza->setDough( "pan baked" );
}
void SpicyPizzaBuilder::buildSauce()
{
    m_pizza->setSauce( "hot" );
}
void SpicyPizzaBuilder::buildTopping()
{
    m_pizza->setTopping( "pepperoni+salami" );
}

void Cook::openPizza()
{
    m_pizzaBuilder->getPizza()->open();
}

void Cook::makePizza( PizzaBuilder* pb )
{
    m_pizzaBuilder = pb;
    m_pizzaBuilder->createNewPizzaProduct();
    m_pizzaBuilder->buildDough();
    m_pizzaBuilder->buildSauce();
    m_pizzaBuilder->buildTopping();
}

void ClientBuilder::run()
{
    Cook cook;
    HawaiianPizzaBuilder hawaiianPizzaBuilder;
    SpicyPizzaBuilder spicyPizzaBuilder;

    cook.makePizza( &hawaiianPizzaBuilder );
    cook.openPizza();

    cook.makePizza( &spicyPizzaBuilder );
    cook.openPizza();
}
