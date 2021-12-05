#include "Poco/Any.h"
#include "Poco/Exception.h"
#include <iostream>
#include <boost/type_index.hpp>

using Poco::Any;
using Poco::AnyCast;
using Poco::RefAnyCast;
int main(int argc, char** argv)
{
    Any any(42);
    int myint = 50;
    std::cout << "typeid: " << boost::typeindex::type_id_with_cvr<decltype(myint)>() <<"\n";
    std::string mystr = "string";
    std::cout << "typeid: " << boost::typeindex::type_id_with_cvr<decltype(mystr)>() <<"\n";

    int i = AnyCast<int>(any); // okay
    std::cout << "typeid i: " << boost::typeindex::type_id_with_cvr<decltype(i)>() <<"\n";
    int& ri = RefAnyCast<int>(any); // okay
    std::cout << "typeid ri: " << boost::typeindex::type_id_with_cvr<decltype(ri)>() <<"\n";

    std::cout << i << ' '<< ri <<"\n";

    try
    {
        auto ss = RefAnyCast<const char*>(any);
        short s = AnyCast<short>(any); // throws BadCastException
    }
    catch (Poco::BadCastException& e)
    {
        std::cout <<  e.what() << " "<<e.message()<<"\n";

    }
    return 0;
}
