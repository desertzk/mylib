#include<stdio.h>
#include"sort.h"
#define CUTOFF 3

//void swap(int *p1, int *p2)//通过地址交换实际的值
//{
//	int temp = *p1;
//	*p1 = *p2;
//	*p2 = temp;
//}

//p242 241
//choose privot
//at last we choose median
int Median(int arr[], int left, int right)
{
	int center = (left + right) / 2;

	if (arr[left] > arr[center])
		swap(&arr[left], &arr[center]);
	if (arr[left] > arr[right])
		swap(&arr[left], &arr[right]);
	if (arr[center] > arr[right])
		swap(&arr[center], &arr[right]);

	swap(&arr[center], &arr[right - 1]);
	return arr[right - 1];
}


void Qsort(int arr[], int left, int right)
{
	//ij can use sentinel
	int i, j;
	int pivot;
	if (left + CUTOFF <= right)
	{
		pivot = Median(arr, left, right);
		i = left;
		j = right - 1;
		for (;;)
		{
			while (arr[++i] < pivot){}
			while (arr[--j]>pivot){}
			if (i < j)
				swap(&arr[i], &arr[j]);
			else
				break;
		}
		swap(&arr[i], &arr[right - 1]);

		Qsort(arr, left, i - 1);
		Qsort(arr, i + 1, right);
	}
else
	insert_sort(arr + left, right - left + 1);
}


int main()
{
	int arr[17] = { 17, 3, 5, 2, 41, 91, 72, 6, 8, 0,10,8,16,22,44,77,4 };
	Qsort(arr, 0, 16);
	print(arr, 17);
}
