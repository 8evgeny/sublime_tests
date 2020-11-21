#include <iostream>

using namespace std;

int main() {
 int *p = nullptr;
 int &r = *p;
 cout<<"p = "<<p<<'\n';
 cout<<"&p = "<<&p<<'\n';
 cout<<"&r = "<<&r<<'\n';

 char *p_a = new char;
 char &r_a = *p_a;
 char *p_b = &r_a;
 //далее дебагером шагать
 *p_a = 'A';
 r_a = 'B'; //виден код ASKI
 *p_b = 'C';


}
