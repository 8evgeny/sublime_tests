// Demonstrating the STL vector front and erase operations.

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

template <typename Container>
Container make(const char s[])
{
  return Container(&s[0], &s[strlen(s)]);
}

int main() 
{
  cout << "Demonstrating STL vector front "
       << "and erase operations." << endl;
  vector<char> vector1 = make< vector<char> >("abcdefghij");
  
  cout << "Popping characters off the front produces: "; 

  while (vector1.size() > 0) {
    cout << vector1.front();
    vector1.erase(vector1.begin());
  }
  cout << endl;
  return 0;
}
