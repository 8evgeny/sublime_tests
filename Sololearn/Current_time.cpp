#include <iostream>
#include <ctime>
 
using namespace std;



 
int main ()

{
time_t seconds = time(NULL);
tm* timeinfo = localtime(&seconds);
cout<<"Current date and time:"<<asctime(timeinfo)<<endl;
cin.get();
return 0;
}