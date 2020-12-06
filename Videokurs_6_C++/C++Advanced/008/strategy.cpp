#include "strategy.h"
#include <iostream>

using namespace std;

void ConcreteStrategyA::execute() const
{
    cout << "Called ConcreteStrategyA execute method" << endl;
}

void ConcreteStrategyB::execute() const
{
    cout << "Called ConcreteStrategyB execute method" << endl;
}

void ConcreteStrategyC::execute() const
{
    cout << "Called ConcreteStrategyC execute method" << endl;
}

Context::Context( StrategyInterface* strategy )
    : strategy_( strategy )
{
}

void Context::set_strategy( StrategyInterface* strategy )
{
    strategy_ = strategy;
}

void Context::execute() const
{
    strategy_->execute();
}

void ClientStrategy::run()
{
    ConcreteStrategyA concreteStrategyA;
    ConcreteStrategyB concreteStrategyB;
    ConcreteStrategyC concreteStrategyC;

    Context contextA( &concreteStrategyA );
    Context contextB( &concreteStrategyB );
    Context contextC( &concreteStrategyC );

    contextA.execute(); // output: "Called ConcreteStrategyA execute method"
    contextB.execute(); // output: "Called ConcreteStrategyB execute method"
    contextC.execute(); // output: "Called ConcreteStrategyC execute method"

    contextA.set_strategy( &concreteStrategyB );
    contextA.execute(); // output: "Called ConcreteStrategyB execute method"
    contextA.set_strategy( &concreteStrategyC );
    contextA.execute(); // output: "Called ConcreteStrategyC execute method"
}
