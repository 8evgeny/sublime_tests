#ifndef BUILDER_H
#define BUILDER_H

#include "meta_strategy.h"
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Pizza
{
public:
    void setDough( const string& dough );
    void setSauce( const string& sauce );
    void setTopping( const string& topping );
    void open() const;

private:
    string m_dough;
    string m_sauce;
    string m_topping;
};

class PizzaBuilder
{
public:
    virtual ~PizzaBuilder() = default;

    Pizza* getPizza();
    void createNewPizzaProduct();
    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildTopping() = 0;

protected:
    unique_ptr< Pizza > m_pizza;
};

class HawaiianPizzaBuilder : public PizzaBuilder
{
public:
    ~HawaiianPizzaBuilder() override = default;

    void buildDough() override;
    void buildSauce() override;
    void buildTopping() override;
};

class SpicyPizzaBuilder : public PizzaBuilder
{
public:
    ~SpicyPizzaBuilder() override = default;

    void buildDough() override;
    void buildSauce() override;
    void buildTopping() override;
};

class Cook
{
public:
    void openPizza();
    void makePizza( PizzaBuilder* pb );

private:
    PizzaBuilder* m_pizzaBuilder;
};

class ClientBuilder : public MetaStrategy
{
public:
    void run() override;
};

#endif // BUILDER_H
