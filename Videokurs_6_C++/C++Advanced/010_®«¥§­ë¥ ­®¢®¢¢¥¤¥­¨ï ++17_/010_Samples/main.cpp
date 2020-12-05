#include "inlinevariables.h"
#include <any>
#include <cassert>
#include <experimental/algorithm>
#include <experimental/filesystem>
//#include <filesystem>
#include <iostream>
#include <memory>
#include <optional>
//#include <parallel/algorithm>
#include <string>
#include <string_view>
#include <utility>
#include <variant>
#include <vector>

using namespace std;

// void* operator new( std::size_t count )
//{
//    std::cout << "   " << count << " bytes" << std::endl;
//    return malloc( count );
//}

namespace namespaces
{
namespace n1::n2
{
void f()
{
    cout << "f()" << endl;
}
}

void example()
{
    n1::n2::f();
}
}

namespace ext_aggregate
{
void example()
{
    // aggregate
    struct base1
    {
        int b1, b2 = 42;
    };

    // non-aggregate
    struct base2
    {
        base2()
            : b3( 42 )
        {
        }
        int b3;
    };

    // Extension to aggregate initialization
    struct derived
        : base1
        , base2
    {
        int d;
    };

    // aggregate
    base1 b1{ 1, 2 };

    // non-aggregate
    // base2 b2{ 1 }; // compilation error

    // aggregate in C++17
    derived d1{ { 1, 2 }, {}, 4 }; // d1.b1 = 1, d1.b2 = 2,  d1.b3 = 42, d1.d = 4
    derived d2{ {}, {}, 4 };       // d2.b1 = 0, d2.b2 = 42, d2.b3 = 42, d2.d = 4
    derived d3{
        { 1 },
        {},
    }; // d2.b1 = 1, d2.b2 = 42, d2.b3 = 42, d2.d = 0
}
}

namespace fold_expression
{
template < typename... Args >
void printer( Args&&... args )
{
    ( cout << ... << args ) << '\n';
}

template < typename T, typename... Args >
void push_back_vec( vector< T >& v, Args&&... args )
{
    ( v.push_back( args ), ... );
}

template < typename... Args >
int summa( Args&&... args )
{
    return ( args + ... );
}

template < typename... Args >
bool compare( Args... args )
{
    return ( args && ... );
}

void example()
{
    printer( 1, 2, 3, "abc" );
    printer( 1, ", ", 2, ", ", 3, ", ", "abc" );

    vector< int > v;
    push_back_vec( v, 6, 2, 45, 12 );
    push_back_vec( v, 1, 2, 9 );
    for ( int i : v )
        cout << i << ' ';
    cout << endl;

    cout << summa( 1, 2, 3, 4, 5 ) << endl;

    cout << compare( true, true, true, false ) << endl;
}
}
namespace auto_tmpl_param
{
// before c++17
template < typename T, T val >
void early()
{
    cout << val << endl;
}

// since c++17
template < auto val >
void now()
{
    cout << val << endl;
}

void example()
{
    early< int, 10 >();
    early< char, 'H' >();
    early< long, 100l >();

    now< 10 >();
    now< 'H' >();
    now< 100l >();
}
}
namespace tmpl_arg_deduction
{
void example()
{
    pair< int, string > p_a( 1, "12" );

    // c++17
    pair p_b( 1, "12" );
    pair p_c = { 1, "12" };
    vector vi = { 1, 2, 3, 4 };
    vector vs = { "str1", "str2", "str1" };
    int m = max( 12, 23 );
}
}

namespace constexpr_lambda
{
constexpr int f_calc( int aValue )
{
    auto lambda = [aValue]() { return aValue * 14; };
    return aValue + lambda();
}

void example()
{
    constexpr auto lambda = []( int aValue ) { return aValue * aValue; };

    cout << f_calc( 12 ) << endl;
    cout << lambda( 12 ) << endl;
}
}
namespace this_lambda
{
struct test
{
    void f_test()
    {
        auto lambda_const = [*this]() {
            f_const();
            return mA * mA;
        };

        auto lambda = [*this]() mutable {
            f();
            return mA * mA;
        };

        lambda_const();
        lambda();
    }

private:
    void f_const() const { cout << "f_const()" << endl; }

    void f() { cout << "f()" << endl; }

    int mA{ 100 };
};
void example()
{
    test t;
    t.f_test();
}
}

namespace constexpr_if
{
struct S
{
    int mInt{ 0 };
    float mFloat{ 0.f };
    vector< int > mVectorInt;
};

template < std::size_t aFieldNubmer >
void print( S& s )
{
    if constexpr ( aFieldNubmer == 0 )
    {
        cout << s.mInt << endl;
    }
    else if constexpr ( aFieldNubmer == 1 )
    {
        cout << s.mFloat << endl;
    }
    else if constexpr ( aFieldNubmer == 2 )
    {
        for ( auto i : s.mVectorInt )
            cout << i << ' ';
        cout << endl;
    }
}

void example()
{
    S obj = { 10, 11.f, { 1, 2, 3, 4 } };

    print< 0 >( obj );
    print< 1 >( obj );
    print< 2 >( obj );
}
}
namespace if_switch_initializer
{
void if_example( void* aP )
{
    if ( void* p = aP; p == nullptr )
        cout << "Error. Pointer is nullptr" << endl;
    else
        cout << "Pointer is OK!" << endl;
}

void switch_example( int error )
{
    switch ( int code = error; code )
    {
        case 0:
        {
            cout << "Ok!" << endl;
            break;
        }
        default:
        {
            cout << "Error!" << endl;
            break;
        }
    }
}

void example()
{
    if_example( nullptr );
    if_example( ( void* ) 100 );

    switch_example( 0 );
    switch_example( 10 );
}
}
namespace struct_binding
{
void f_pair()
{
    pair p = { 1, "Hello" };

    auto [ x, y ] = p;

    cout << x << endl;
    cout << y << endl;
}

void f_array()
{
    int coord[ 4 ] = { 1, 2, 3 };

    auto [ x, y, z, a ] = coord;

    cout << a << endl;
    cout << y << endl;
    cout << z << endl;
}

void f_a()
{
    struct Config_a
    {
        int id;
        string name;
        vector< int > data;
    };
    Config_a ca;

    auto& [ id, n, d ] = ca;
    id = 1;
    n = "Name";
    d.push_back( 1 );
}

void example()
{
    f_pair();
    f_array();
    f_a();

    int pos[ 2 ] = { 10, 20 };
    auto& [ x, y ] = pos;
    x = 100;
    y = 200;
}
}

namespace new_attributes
{
void f_fallthrough()
{
    int i = rand() % 10;
    switch ( i )
    {
        case 0:
            cout << "0" << endl;
            break;
        case 1:
            cout << "1" << endl;
            break;
        case 2:
            cout << "2" << endl;
            break;
        case 3:
            cout << "some doing" << endl;
            cout << "3" << endl;
            [[fallthrough]]; // no warning
        case 4:
            cout << "4" << endl;
    }
}

[[nodiscard]] int f_nodiscard()
{
    return 0;
}

void example()
{
    f_fallthrough();
    f_nodiscard();

    [[maybe_unused]] int i = 0;
}
}

namespace std_any
{
void example()
{
    std::any hm = 10;
    cout << std::any_cast< int >( hm ) << endl;

    hm = string( "hello" );
    cout << std::any_cast< string >( hm ) << endl;

    hm = "hello 2";
    cout << std::any_cast< const char* >( hm ) << endl;
}
}

namespace std_stringview
{

void getString( [[maybe_unused]] const std::string& str ) {}

void getStringView( [[maybe_unused]] std::string_view strView ) {}

void example()
{

    std::cout << std::endl;

    std::cout << "std::string" << std::endl;

    std::string large = "0123456789-123456789-123456789-123456789";
    std::string substr = large.substr( 10 );

    std::cout << std::endl;

    std::cout << "std::string_view" << std::endl;

    std::string_view largeStringView{ large.c_str(), large.size() };
    largeStringView.remove_prefix( 10 );

    assert( substr == largeStringView );

    std::cout << std::endl;

    std::cout << "getString" << std::endl;

    getString( large );
    getString( "0123456789-123456789-123456789-123456789" );
    const char message[] = "0123456789-123456789-123456789-123456789";
    getString( message );

    std::cout << std::endl;

    std::cout << "getStringView" << std::endl;

    getStringView( large );
    getStringView( "0123456789-123456789-123456789-123456789" );
    getStringView( message );

    std::cout << std::endl;
}
}

namespace std_optional
{
optional< int > strToInt( string aStr )
{
    if ( aStr.empty() )
        return {};

    // parse string, if Ok return value
    if ( true )
        return 1;
    return {};
}

void example()
{
    optional< int > i;
    i = strToInt( "" );
    if ( i )
        cout << "OK: " << *i << endl;

    i = strToInt( "123" );
    if ( i )
        cout << "OK: " << *i << endl;
}
}

namespace std_variant
{
void example()
{
    variant< int, char, string > v;

    v = 42;
    cout << get< int >( v ) << " " << v.index() << endl;

    v = "Hello!";
    cout << get< string >( v ) << " " << v.index() << endl;
}
}

namespace std_filesystem
{
namespace fs = experimental::filesystem;

void example()
{
    auto cur_p = fs::current_path();
    cout << "current path - " << cur_p << endl;
    cout << endl;

    auto root_p = fs::path( "/" );
    auto space = fs::space( root_p );
    /* capacity  - total size of the filesystem, in bytes
       free      - free space on the filesystem, in bytes
       available - free space available to a non-privileged process
                   (may be equal or less than free) */
    cout << "Total     : " << space.capacity / 1024 / 1024 / 1024 << "GB" << endl;
    cout << "Free      : " << space.free / 1024 / 1024 / 1024 << "GB" << endl;
    cout << "Available : " << space.available / 1024 / 1024 / 1024 << "GB" << endl;
    cout << endl;
}
}

int main()
{
    // namespaces::example();
    // ext_aggregate::example();
    // fold_expression::example();
    // auto_tmpl_param::example();
    // tmpl_arg_deduction::example();
    // constexpr_if::example();
    // struct_binding::example();
    // constexpr_lambda::example();
    //    this_lambda::example();
    //    if_switch_initializer::example();
    //    new_attributes::example();
    // std_any::example();
    // std_stringview::example();
    // std_optional::example();
    // std_variant::example();
    std_filesystem::example();

    // std::vector< int > v( 100 );

    // ...

    // Explicitly force a call to parallel sort.
    //__gnu_parallel::sort( v.begin(), v.end() );

    return 0;
}
