#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class Functor
{
public:
    bool operator()( int a, int b )
    {
        cout << "some operation" << endl;
        return a > b;
    }
    void operator()()
    {
        cout << "some operation" << endl;
    }

    static void method( int a ) { cout << "method" << a << endl; }
};

int sum( int a, int b )
{
    return a + b;
}

bool cmp( int a, int b )
{
    return b < a;
}

using MyFunc = int( int, int );

int main()
{
    using namespace std::placeholders;

    Functor f;
    f();

    vector< int > a = { 42, 1, 3, 4, 8, 2 };

    sort( a.begin(), a.end());
    for ( auto it : a )
        cout << it << " ";
    cout <<  endl;

    sort( a.begin(), a.end(), []( int a, int b ) -> bool { return a > b; } );

    for ( auto it : a )
        cout << it << " ";
    cout <<  endl;

    std::function< MyFunc > func_sum;

    func_sum = sum;

    int value = 4;

    [value = std::move( value )]( string s ) { cout << value << endl; }( "hello" );

    auto w = std::bind( Functor::method, 100 );

    w( 3 );

    cout << a[ 2 ] << endl;

    cout << func_sum( 3, 4 ) << endl;

    int ( *func )( int a, int b );
    func = &sum;
    cout << func( 4, 5 ) << endl;

    return 0;
}
