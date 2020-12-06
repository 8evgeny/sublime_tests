#ifndef STRATEGY_H
#define STRATEGY_H

#include "meta_strategy.h"

class StrategyInterface
{
public:
    virtual void execute() const = 0;
};

class ConcreteStrategyA : public StrategyInterface
{
public:
    void execute() const override;
};

class ConcreteStrategyB : public StrategyInterface
{
public:
    void execute() const override;
};

class ConcreteStrategyC : public StrategyInterface
{
public:
    void execute() const override;
};

class Context
{
private:
    StrategyInterface* strategy_;

public:
    explicit Context( StrategyInterface* strategy );

    void set_strategy( StrategyInterface* strategy );

    void execute() const;
};

class ClientStrategy : public MetaStrategy
{
public:
    ClientStrategy() = default;
    void run() override;
};

#endif // STRATEGY_H
