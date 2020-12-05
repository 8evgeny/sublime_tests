#include <forward_list>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

template < typename T >
bool test = std::is_same< typename std::iterator_traits< typename T::iterator >::iterator_category,
                          std::forward_iterator_tag >::value;

template < typename T >
bool test_bidirectional =
    std::is_same< typename std::iterator_traits< typename T::iterator >::iterator_category,
                  std::bidirectional_iterator_tag >::value;

void print_is_forward_iterator()
{
    std::cout << std::boolalpha << test< std::forward_list< int > > << std::endl;
    // what about std::list?
    std::cout << std::boolalpha << test< std::list< int > > << std::endl;
}

void print_is_bidirectional_iterator()
{
    std::cout << std::boolalpha << test_bidirectional< std::list< int > > << std::endl;
    // what about std::forward_list?
    std::cout << std::boolalpha << test_bidirectional< std::forward_list< int > > << std::endl;
}

int main()
{
    //    std::vector< int > vec = { 2, 5, 9, 13, 18, -8, 0 };

    //    // works on write\store
    //    std::ostream_iterator< int > it = { std::cout, " :: " };
    //    std::ostream_iterator< int > it_2 = { std::cout, " :: " };

    //    // std::copy simple implementation
    //    auto first = vec.begin();
    //    while ( first != vec.end() )
    //    {
    //        *it++ = *first++;
    //    }

    //    // it == it_2; // won't compile

    //    std::istringstream bytes( "13 14 15 16 17 18 19 20" );

    //    std::vector< int > bar{ std::istream_iterator< int >( bytes ), std::istream_iterator< int
    //    >() };

    //    std::cout << std::endl;

    //    for ( auto it : bar )
    //    {
    //        std::cout << it << " - ";
    //    }

    //    std::cout << std::endl;

    //    print_is_forward_iterator();
    //    print_is_bidirectional_iterator();

    //    auto it1 = vec.begin();

    //    std::cout << ( ( it1 + 2 ) > it1 ) << std::endl;

    //    std::unordered_map< int, int > mp = { { 1, 1 }, { 2, 2 }, { 3, 3 } };

    //    bool test_unordered_map_iterator_type =
    //        std::is_same< typename std::iterator_traits<
    //                          typename std::unordered_map< int, int >::iterator
    //                          >::iterator_category,
    //                      std::forward_iterator_tag >::value;

    //    std::cout << "test_unordered_map_iterator_type = forward is " << std::boolalpha
    //              << test_unordered_map_iterator_type << std::endl;

    // algorithms

    //    std::vector< int > vec = { 2, 5, 9, 13, 18, -8, 0, 5, 5 };

    //    std::vector< int > new_vec;

    //    std::copy_if( vec.begin(), vec.end(), std::back_inserter( new_vec ), []( const int elem )
    //    {
    //        return elem % 2 == 0;
    //    } );

    //    std::copy( new_vec.begin(), new_vec.end(), std::ostream_iterator< int >{ std::cout, ", " }
    //    );

    //    vec.erase( std::remove( vec.begin(), vec.end(), 0 ) );

    //    std::cout << std::endl;

    //    std::copy( vec.begin(), vec.end(), std::ostream_iterator< int >{ std::cout, ", " } );

    //    std::cout << std::endl;

    //    auto found = std::count( vec.begin(), vec.end(), 5 );

    //    std::cout << found << std::endl;

    //    if ( found != vec.end() ) // OK
    //    {
    //        std::cout << *found << std::endl;
    //    }
    //    else
    //    {
    //        std::cout << "element is not found" << std::endl;
    //    }

    std::string str = "Hello World";
    std::transform( str.begin(), str.end(), str.begin(), ::toupper );

    std::cout << str << std::endl;

    std::reverse( str.begin(), str.end() );

    std::cout << str << std::endl;

    auto splitted =
        std::partition( str.begin(), str.end(), []( const char elem ) { return elem > 'L'; } );

    std::cout << "\nPartitioned string:\n    ";
    std::copy( std::begin( str ), splitted, std::ostream_iterator< char >( std::cout, "," ) );
    std::cout << " |||| ";
    std::copy( splitted, std::end( str ), std::ostream_iterator< char >( std::cout, "," ) );

    sort( str.begin(), str.end() );

    std::cout << std::endl << "Sorted:" << std::endl << str << std::endl;

    sort( str.begin(), str.end(), []( const char elem1, const char elem2 ) {
        return elem1 > elem2;
    } );

    std::cout << std::endl << str << std::endl;

    std::cout << std::max( 19, 9698 ) << std::endl;

    std::vector< int > vec{ 1, 2, 3 };

    while ( std::next_permutation( vec.begin(), vec.end() ) )
    {
        std::copy( vec.begin(), vec.end(), std::ostream_iterator< int >{ std::cout, ", " } );
        std::cout << std::endl;
    }

    return 0;
}
