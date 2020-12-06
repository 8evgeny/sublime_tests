#include "decorator.h"

#include <iostream>
#include <memory>
#include <string>

Core::~Core()
{
    std::cout << "Core destructor called.\n";
}

void Core::write( std::string& /*text*/ ){}; // Do nothing.

Decorator::Decorator( std::unique_ptr< Interface > c )
{
    interface = std::move( c );
}
void Decorator::write( std::string& text )
{
    interface->write( text );
}

MessengerWithSalutation::MessengerWithSalutation( std::unique_ptr< Interface > c,
                                                  const std::string& str )
    : Decorator( std::move( c ) )
    , salutation( str )
{
}
MessengerWithSalutation::~MessengerWithSalutation()
{
    std::cout << "Messenger destructor called.\n";
}
void MessengerWithSalutation::write( std::string& text )
{
    text = salutation + "\n\n" + text;
    Decorator::write( text );
}

MessengerWithValediction::MessengerWithValediction( std::unique_ptr< Interface > c,
                                                    const std::string& str )
    : Decorator( std::move( c ) )
    , valediction( str )
{
}
MessengerWithValediction::~MessengerWithValediction()
{
    std::cout << "MessengerWithValediction destructor called.\n";
}
void MessengerWithValediction::write( std::string& text )
{
    Decorator::write( text );
    text += "\n\n" + valediction;
}

void ClientDecorator::run()
{
    const std::string salutation = "Greetings,";
    const std::string valediction = "Sincerly, Andy";
    std::string message1 = "This message is not decorated.";
    std::string message2 = "This message is decorated with a salutation.";
    std::string message3 = "This message is decorated with a valediction.";
    std::string message4 = "This message is decorated with a salutation and a valediction.";

    std::unique_ptr< Interface > messenger1 = std::make_unique< Core >();
    std::unique_ptr< Interface > messenger2 =
        std::make_unique< MessengerWithSalutation >( std::make_unique< Core >(), salutation );
    std::unique_ptr< Interface > messenger3 =
        std::make_unique< MessengerWithValediction >( std::make_unique< Core >(), valediction );
    std::unique_ptr< Interface > messenger4 = std::make_unique< MessengerWithValediction >(
        std::make_unique< MessengerWithSalutation >( std::make_unique< Core >(), salutation ),
        valediction );

    messenger1->write( message1 );
    std::cout << message1 << '\n';
    std::cout << "\n------------------------------\n\n";

    messenger2->write( message2 );
    std::cout << message2 << '\n';
    std::cout << "\n------------------------------\n\n";

    messenger3->write( message3 );
    std::cout << message3 << '\n';
    std::cout << "\n------------------------------\n\n";

    messenger4->write( message4 );
    std::cout << message4 << '\n';
    std::cout << "\n------------------------------\n\n";
}
