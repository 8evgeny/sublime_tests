
#include <ctime>
#include <iostream>
using namespace std;
int  main()
{
time_t t;
t=time(0);
cout << puts(ctime(&t));  
}
