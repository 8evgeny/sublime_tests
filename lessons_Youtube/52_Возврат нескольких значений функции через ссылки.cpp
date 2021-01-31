#include <cstdlib> 
#include <iostream>
using namespace std;
 
void Foo ( int &a, int &b, int &c )
{
a = 10;
b *= 2;
c -= 100; 




}

int main()
{
 int a = 0, b = 4, c = 34 ;
cout<<"a = \t"<<a<<endl;
cout<<"b = \t"<<b<<endl;
cout<<"c = \t"<<c<<endl;

cout<<"Foo "<<endl;
Foo(a,b,c);
cout<<"a = \t"<<a<<endl;
cout<<"b = \t"<<b<<endl;
cout<<"c = \t"<<c<<endl;

 system( "PAUSE" ) ; return 0 ;
 }