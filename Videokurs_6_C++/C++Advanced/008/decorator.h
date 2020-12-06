#ifndef DECORATOR_H
#define DECORATOR_H

#include "meta_strategy.h"
#include <iostream>
#include <memory>
#include <string>

class Interface
{
public:
    virtual ~Interface() = default;
    virtual void write( std::string& ) = 0;
};

class Core : public Interface
{
public:
    ~Core() override;
    void write( std::string& text ) override;
};

class Decorator : public Interface
{
private:
    std::unique_ptr< Interface > interface;

public:
    Decorator( std::unique_ptr< Interface > c );
    void write( std::string& text ) override;
};

class MessengerWithSalutation : public Decorator
{
private:
    std::string salutation;

public:
    MessengerWithSalutation( std::unique_ptr< Interface > c, const std::string& str );
    ~MessengerWithSalutation() override;
    void write( std::string& text ) override;
};

class MessengerWithValediction : public Decorator
{
private:
    std::string valediction;

public:
    MessengerWithValediction( std::unique_ptr< Interface > c, const std::string& str );
    ~MessengerWithValediction() override;
    void write( std::string& text ) override;
};

class ClientDecorator : public MetaStrategy
{
public:
    void run() override;
};

#endif // DECORATOR_H
