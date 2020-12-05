
#include <iostream>
#include <vector>
using namespace std;
void print(vector<int> &v){
    for(auto i:v) {
        cout<<i<<" ";
    }
}

int main()
{
  int num=0;
  vector<int> v = {};

  while(num>=0) {
  cout<<endl<<"введите число: ";
  cin>> num;
  if(num>=0){v.push_back(num);  print(v);}

  }

    return 0;
}
