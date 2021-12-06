/*
> #include "Poco/DynamicAny.h"
> An instance of Poco::DynamicAny can hold a value of any type for
which a DynamicAnyHolder specialization is available.
> Poco::DynamicAny supports value semantics.
> The value can be extracted in a type-safe manner.
> Safe implicit and explicit conversions to various types (standard
types, std::string) are supported (ranges are checked).


*/


#include "Poco/DynamicAny.h"
#include "Poco/Exception.h"
#include <iostream>
#include <boost/type_index.hpp>

using Poco::DynamicAny;

int main(int argc, char** argv)
{
    DynamicAny any(42);
    int i = any;
    std::cout << "typeid i: " << boost::typeindex::type_id_with_cvr<decltype(i)>() <<"\n";
    std::string s(any.convert<std::string>());
    std::cout << "typeid s: " << boost::typeindex::type_id_with_cvr<decltype(s)>() <<"\n";

    any.convert(s); // or without the need to cast
    std::cout << "typeid any: " << boost::typeindex::type_id_with_cvr<decltype(any)>() <<"\n";
    const int& ri(any.extract<int>());
    std::cout << "typeid ri: " << boost::typeindex::type_id_with_cvr<decltype(ri)>() <<"\n";

    short ss = any;
    try
    {
        short ss = any.extract<short>(); // throws BadCastException
    }
    catch (Poco::BadCastException& e)
    {
        std::cout <<  e.what() << " "<<e.message()<<"\n";
    }
    return 0;
}
