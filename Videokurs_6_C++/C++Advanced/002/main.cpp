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

    static void method( int a ) { cout << "method" << a << endl; }
};

int sum( int a, int b )
{
    return a - b;
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

    vector< int > a = { 2, 1, 3, 4 };

    sort( a.begin(), a.end(), []( int a, int b ) -> bool { return a > b; } );

    for ( auto it : a )
        cout << it << endl;

    std::function< MyFunc > func_sum;

    func_sum = sum;

    int value = 4;

    [value = std::move( value )]( string s ) { cout << value; }( "hello" );

    auto w = std::bind( Functor::method, 100 );

    w( 3 );

    cout << a[ 2 ] << endl;

    cout << func_sum( 3, 4 ) << endl;

    //    int ( *func )( int a, int b );

    //    func = &sum;

    //    cout << func( 4, 5 ) << endl;
    return 0;
}
