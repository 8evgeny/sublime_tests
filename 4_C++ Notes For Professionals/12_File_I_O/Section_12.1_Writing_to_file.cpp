#include <iostream>
#include <fstream>
#include <exception>
int main(){

std::ofstream os("foo.txt");
if(os.is_open()){
os << "Hello World!";
}

std::ofstream os1("foo1.txt");
if(os1.is_open()){
char data[] = "Foo";
// Writes 3 characters from data -> "Foo".
os1.write(data, 3);
}

std::ifstream ifs("foo.txt");  // ifstream: Opens file "foo.txt" for reading only.
std::ofstream ofs("foo.txt");  // ofstream: Opens file "foo.txt" for writing only.
std::fstream iofs("foo.txt");  // fstream:  Opens file "foo.txt" for reading and writing.


// Alternatively, you can use the file stream's member function open():
std::ifstream ifs1;
ifs.open("bar.txt");  // ifstream: Opens file "bar.txt" for reading only.
std::ofstream ofs1;
ofs.open("bar.txt");  // ofstream: Opens file "bar.txt" for writing only.
std::fstream iofs1;
iofs.open("bar.txt"); // fstream:  Opens file "bar.txt" for reading and writing.




}