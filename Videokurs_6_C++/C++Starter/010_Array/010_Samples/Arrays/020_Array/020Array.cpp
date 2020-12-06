#include "stdafx.h"
#include <iostream>

using namespace std;

void get_array_info(int *arr, int count, int *max, int *min, int *avrg);

int main()
{
	int * p_arr = new int[100];

	for (int i = 0; i < 100; i++)
	{
		*(p_arr + i) = rand();
	}
	
	int max = 0, min = 0, avrg = 0;

	get_array_info(p_arr, 100, &max, &min, &avrg);

	cout << "Max element in array : " << max << ", min element = " << min << ", average value = " << avrg << endl;

	system("pause");
	return 0;
}

void get_array_info(int *arr, int count, int *max, int *min, int *avrg)
{
	*max = arr[0];
	*min = arr[0];
	*avrg = 0;
	for (int i = 0; i < count; i++)
	{
		if (arr[i] > *max) {
			*max = arr[i];
		}
		
		if (arr[i] < *min) {
			*min = arr[i];
		}
		*avrg += *(arr + i);
	}

	*avrg = *avrg / count;
}
