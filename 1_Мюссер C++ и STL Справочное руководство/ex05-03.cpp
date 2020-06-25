// Using the generic sort algorithm with a binary predicate
#include <iostream>
#include <algorithm>
#include <cassert>
#include <functional>  
using namespace std;

		void print(int* x)
		{
			for (int i = 0; i<1000; ++i)
			{
				cout << x[i] << "\t";
			}
			cout << endl << endl;
		}

int main() {
  cout << "Using the generic sort algorithm "
       << "with a binary predicate." << endl;
  int a[1000];
  int i;
  for (i = 0; i < 1000; ++i) 
    a[i] = i;
		print(a);
  random_shuffle(&a[0], &a[1000]);//Случайная перестановка

		print(a);

  // Sort into ascending order:  
  sort(&a[0], &a[1000]);

		print(a);
  for (i = 0; i < 1000; ++i) 
    assert (a[i] == i);

  random_shuffle(&a[0], &a[1000]); 

  // Sort into descending order:  
  sort(&a[0], &a[1000], greater<int>()); 
		print(a);
  for (i = 0; i < 1000; ++i) 
     assert (a[i] == 1000 - i - 1);
  cout << " --- Ok." << endl;
  return 0;
}
