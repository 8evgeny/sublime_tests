#include <iostream>
#include <fstream>
#include <string>
int main()
{
ifstream infile("in_file");
ofstream outfile("out_file");
if ( ! infile ) {
cerr << "Ошибка открытия входного файла.\n"
return -1;
}
if ( ! outfile ) {
cerr << "Ошибка открытия выходного файла.\n"
return -2;
}

string word;
while ( infile >> word )
outfile << word << ' ';
return 0;
}
