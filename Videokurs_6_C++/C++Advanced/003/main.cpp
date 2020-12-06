#include <array>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main()
{
    // array
    //    array< int, 10 > my_array;

    //    my_array[ 4 ] = 4;
    //    cout << my_array.at( 4 ) << endl;

    // vector
    //    vector< int > my_vector;

    //    my_vector.reserve( 20 );

    //    my_vector = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

    //    cout << my_vector.size() << endl;

    //    list< int > my_list;
    //    list< int > my_list_2;
    //    forward_list< int > my_forward_list;
    //    forward_list< int > my_forward_list_2;

    //    my_list.push_back( 3 );
    //    my_list_2.push_front( 1 );
    //    my_list.splice( my_list.begin(), my_list_2 );
    //    my_list.merge( my_list_2 );
    //    my_list.sort();
    //    my_list.emplace_front();

    //    for ( auto elem : my_list )
    //    {
    //        cout << elem << endl;
    //    }

    //    cout << endl;

    //    my_forward_list.push_front( 100 );

    //    my_forward_list.insert_after( my_forward_list.begin(), 7 );
    //    my_forward_list_2.emplace_after( my_forward_list.begin(), 10 ); // be careful

    //    cout << my_forward_list_2.empty() << endl;

    //    cout << endl;

    //    my_forward_list_2.push_front( 111 );

    //    my_forward_list.splice_after( my_forward_list.before_begin(), my_forward_list_2 );

    //    for ( auto elem : my_forward_list )
    //    {
    //        cout << elem << endl;
    //    }

    //    cout << endl << my_forward_list_2.empty() << endl;

    //    cout << endl;

    //    set< string > my_set = { "a", "a", "d", "big_string" };

    //    cout << my_set.size() << endl;

    //    my_set.insert( "ab" );
    //    my_set.insert( "dabd" );

    //    auto it = my_set.find( "d" );
    //    my_set.emplace_hint( it, "de" );
    //    auto st = my_set.equal_range( "d" );

    //    cout << "equal range:" << *st.first << endl;
    //    cout << "equal range:" << *st.second << endl;

    //    cout << my_set.count( "a" ) << endl;

    //    for ( auto el : my_set )
    //    {
    //        cout << el << endl;
    //    }

    //    // multiset

    //    multiset< string > multi_set = { "a", "a", "d", "big_string" };

    //    cout << endl << "multiset:" << endl << multi_set.size() << endl;

    //    multi_set.insert( "ab" );
    //    multi_set.insert( "dabd" );

    //    auto _it = multi_set.find( "d" );
    //    multi_set.emplace_hint( _it, "de" );
    //    auto _st = multi_set.equal_range( "d" );

    //    cout << "equal range:" << *_st.first << endl;
    //    cout << "equal range:" << *_st.second << endl;

    //    cout << multi_set.count( "a" ) << endl;

    //    for ( auto el : multi_set )
    //    {
    //        cout << el << endl;
    //    }

    //    // map

    //    map< string, int > my_map;

    //    my_map[ "as" ] = 2;
    //    cout << endl << endl << "map:" << endl << my_map.at( "as" ) << endl;
    //    cout << my_map[ "a" ] << endl;
    //    cout << my_map.at( "a" ) << endl;

    // unordered_set & unordered_map

    //    unordered_set< string > un_s;

    //    unordered_map< string, int > un_m;

    //    unordered_multimap< string, int > unm_map;

    //    // reserves at least the specified number of buckets.
    //    un_m.rehash( 6 );

    //    // reserves space for at least the specified number of elements.
    //    // un_set.reserve( 50 );

    //    un_m[ "2" ] = 2;
    //    un_m[ "4" ] = 4;
    //    // un_m[ "5" ] = 4;

    //    cout << un_m.bucket( "2" ) << endl;
    //    cout << un_m.bucket( "4" ) << endl;
    //    //    cout << un_m.bucket( "0" ) << endl;
    //    //    cout << un_m.bucket( "5" ) << endl;

    //    cout << "buckets sizes:" << endl;
    //    cout << un_m.bucket_size( 0 ) << endl; // returns the number of elements in specific
    //    bucket cout << un_m.bucket_size( 1 ) << endl; // returns the number of elements in
    //    specific bucket
    //    // cout << un_m.bucket_size( 2 ) << endl; // returns the number of elements in specific
    //    bucket

    //    cout << "the number of buckets " << endl;
    //    cout << un_m.bucket_count() << endl; // returns the number of buckets - elements at all
    //    cout << un_m.size() << endl;
    //    cout << un_m.max_bucket_count() << endl;

    //    cout << "average number of elements per bucket" << endl;
    //    cout << un_m.load_factor() << endl;
    //    cout << un_m.max_load_factor() << endl;

    //    un_m.hash_function();

    //    cout << un_m[ "2" ] << " " << un_m[ "4" ] << endl;

    stack< int > st; // based on deque
    queue< int > qu; // based on deque

    priority_queue< int, deque< int > > prio; // based on vector

    prio.push( 4 );
    prio.push( 3 );
    prio.push( 6 );

    cout << "priority_queue" << endl;
    while ( !prio.empty() )
    {
        cout << prio.top() << endl;
        prio.pop();
    }

    // stack
    st.push( 4 );
    st.push( 3 );
    st.push( 6 );

    cout << "stack" << endl;

    while ( !st.empty() )
    {
        cout << st.top() << endl;
        st.pop();
    }

    // queue
    qu.push( 4 );
    qu.push( 3 );
    qu.push( 6 );

    cout << "queue" << endl;

    while ( !qu.empty() )
    {
        cout << qu.front() << endl;
        qu.pop();
    }

    return 0;
}
