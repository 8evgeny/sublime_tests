#include <iostream>
#include <ctime>

using namespace std;

int main ()
{

#define LEN_LN 4
#define OFFS_LN 8

//#define BUF_LEN 15
#define BUF_LEN ((1 << LEN_LN) - 1)
//#define DICT_LEN 256
#define DICT_LEN ((1 << OFFS_LN) - 1)
cout<<"BUF_LEN:"<<BUF_LEN<<endl;
cout<<"DICT_LEN:"<<DICT_LEN<<endl;

//cin.get();
return 0;
}
