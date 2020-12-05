#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>
#include <strstream>
#include <vector>

using namespace std;

// https://stackoverflow.com/questions/524591/performance-of-creating-a-c-stdstring-from-an-input-iterator/524843#524843

string readFile1( const string& fileName )
{
    ifstream f( fileName.c_str() );
    return string( std::istreambuf_iterator< char >( f ), std::istreambuf_iterator< char >() );
}

string readFile2( const string& fileName )
{
    ifstream ifs( fileName.c_str(), ios::in | ios::binary | ios::ate );

    ifstream::pos_type fileSize = ifs.tellg();
    ifs.seekg( 0, ios::beg );

    vector< char > bytes( fileSize );
    ifs.read( &bytes[ 0 ], fileSize );

    return string( &bytes[ 0 ], fileSize );
}

string readFile3( const string& fileName )
{
    string data;
    ifstream in( fileName.c_str() );
    getline( in, data, string::traits_type::to_char_type( string::traits_type::eof() ) );
    return data;
}

string readFile4( const std::string& filename )
{
    ifstream file( filename.c_str(), ios::in | ios::binary | ios::ate );

    string data;
    data.reserve( file.tellg() );
    file.seekg( 0, ios::beg );
    data.append( istreambuf_iterator< char >( file.rdbuf() ), istreambuf_iterator< char >() );
    return data;
}

string readFile5( const string& fileName )
{
    std::ifstream input( fileName );
    std::stringstream sstr;

    while ( input >> sstr.rdbuf() )
        ;

    return sstr.str();
}

int main()
{
    // ofstream out( "lesson_files" );
    cout << "Start" << endl;

    ofstream out_right;

    out_right.open( "lesson_files", ofstream::app );

    if ( out_right.is_open() )
    {
        out_right << "\n ___ test text from lesson";
    }

    out_right.close();

    ifstream in_stream;

    in_stream.open( "lesson_files" );

    std::string result;
    char char_result;
    char res[ 16 ];

    cout << "start" << endl;

    if ( in_stream.is_open() )
    {
        while ( std::getline( in_stream, result ) )
        {
            // in_stream >> result;
            cout << result;
        }
    }

    in_stream.close();

    cout << "\nend" << endl;

    std::streambuf *psbuf, *backup;
    std::ofstream filestr;
    filestr.open( "test.txt" );

    backup = std::cout.rdbuf(); // back up cout's streambuf

    psbuf = filestr.rdbuf();  // get file's streambuf
    std::cout.rdbuf( psbuf ); // assign streambuf to cout

    std::cout << "This is written to the file";

    std::cout.rdbuf( backup ); // restore cout's original streambuf

    filestr.close();

    return 0;
}
