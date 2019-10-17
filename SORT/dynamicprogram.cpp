#include<iostream>
#include<array>
#include<cstdlib>

using namespace std;
//钢条切割问题朴素递归法p206
template<class T, int Size>
int cutrod(array<T, Size> arr, int num)
{
	if (num == 0)
		return 0;
	int max = 0;
	int i = 1;
	for (i = 1; i <= num; ++i)
	{
		int thismax = arr[i-1] + cutrod(arr, num - i);
		if (thismax > max)
		{
			max = thismax;
			cout << "size:" << i << "max:"<<max<<endl;
			
		}	
	}
	
	return max;
}


void main()
{

	array<int, 10> steelrod = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
	cout << cutrod<int, 10>(steelrod, 10);
	cin.get();
}