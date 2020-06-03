// Using an in-place generic sort algorithm
#include <iostream>
#include <algorithm>
#include <cassert>
#include <Windows.h>
using namespace std;
/*��� ��������� ��������� ������ � � �������� ��������������� ������������������
������� � �, �.�.������ ���������� ��������������� ������� ������ ����, ���������
���������� �������� sort �������� ����������, ���������� ��� �����. */
		void print(int* x) 
		{
			for (int i=0;i<1000;++i)
			{
				cout << x[i] <<"\t";
			}
			cout << endl;
		}

int main() {
		setlocale(LC_ALL, "ru");
  cout << "������������� ��������� ���������� ��� �����" << endl;
  int a[1000];
  int i;
  for (i = 0; i < 1000; ++i) 
    a[i] = 1000 - i - 1;
		print(a);
  sort(&a[0], &a[1000]);
  		print(a);
  for (i = 0; i < 1000; ++i) 
    assert (a[i] == i);
  cout << " --- Ok." << endl;
  return 0;
}
