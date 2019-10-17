#include<iostream>
#include<array>
#include<vector>
#include<map>
using namespace std;
//插入法排序
void insert_sort(int *arr,int num)
{
	for (int i = 1; i < num; i++)
	{
		int tmp = arr[i];
		int j = i - 1;
		while (tmp<arr[j]&&j>=0)//all move back 1 step
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j+1] = tmp;
	}
	
}

//冒泡排序
void bubble_sort(int *arr,int num)
{
	for (int i = 0; i < num; i++)
	{
		//arr[i]
		for (int j = i+1; j < num; j++)
		{
			if (arr[i] < arr[j])
			{
				int tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}


//选择排序
void select_sort(int array[], int n)
{
	int i, j, k, t;
	for (i = 0; i < n - 1; i++)
	{
		k = i;
		for (j = i + 1; j < n; j++)
		if (array[j] < array[k])
			k = j;
		t = array[k]; array[k] = array[i]; array[i] = t;

	}
}

//希尔排序
template<typename T>
void shell_sort(T *p, int len)
{
	
	for (int increase = len / 2;/*增量*/increase > 0; increase /= 2)
	{
		for (int i = increase; i < len ; i++)
		{
			T tmp = p[i];//backup
			int j = 0;
			for (j = i; j >= increase; j -= increase)
			{
				if (tmp < p[j - increase])                 //1-插入排序
					p[j] = p[j - increase];
				else
					break;
			}
			p[j] = tmp;                                //1-插入排序
		}
		
	}

}



void print(int *arr ,int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}


//归并排序 s start m middle e end
void merge(int arr[], int s, int m, int e)
{
	int n1 = m - s + 1;
	int n2 = e - m;
	//array<int,n1> subarr1;
	vector<int> subarr1(n1);
	vector<int> subarr2(n2);
	int i = 0;
	for (i = 0; i < n1; i++)
	{
		subarr1[i] = arr[s + i];
	}
	int j = 0;
	for (j = 0; j < n2; j++)
	{
		subarr2[j] = arr[m + j+1];
	}
	int totallen = e - s + 1;
	for (int k = s, i = 0, j = 0; k <= e; k++)
	{
		if (i == n1){//when subarr1 is done
			while (j < n2)
				arr[k++] = subarr2[j++];
			break;
		}
		else if (j == n2){//when subarr2 is done
			while (i < n1)
				arr[k++] = subarr1[i++];
			break;
		}


		if (subarr1[i] <= subarr2[j])
		{
			arr[k] = subarr1[i];
			i++;
		}
		else{
			arr[k] = subarr2[j];
			j++;
		}


	}
}

void merge_sort(int *arr, int start, int end)
{
	if (start < end)
	{
		int middle = (start + end) / 2;
		merge_sort(arr, start, middle);
		merge_sort(arr, middle + 1, end);
		merge(arr, start, middle, end);
	}
}
//堆排序p85
int parent(int i)
{
	return (i-1) / 2;
}

int left(int i)
{
	return 2*i + 1;
}
int right(int i)
{
	return 2 * i + 2;
}

void swap(int *p1, int *p2)//通过地址交换实际的值
{
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

void max_heapify(int arr[], int index, int heapsize)
{
	int l = left(index);
	int r = right(index);
	int largest = 0;
	if (l < heapsize&&arr[l] > arr[index])
		largest = l;
	else
		largest = index;
	if (r < heapsize&&arr[r] > arr[largest])
		largest = r;
	if (largest != index)
	{
		swap(arr + index, arr + largest);
		max_heapify(arr, largest, heapsize);
	}

}


void build_max_heap(int arr[],int arrlen)
{
	int heapsize = arrlen;
	for (int i = arrlen / 2; i >=0; i--)
	{
		max_heapify(arr, i, heapsize);
	}
}

void heap_sort(int arr[],int len)
{
	build_max_heap(arr, len);
	int heapsize = len;
	for (int i = len; i >= 1; i--)
	{
		swap(arr[0], arr[i - 1]);
		heapsize--;
		max_heapify(arr, 0, heapsize);//0代表最大堆最上面那个
	}
}

//最大优先队列p91
template<typename T>
void max_heapify(vector<T> &arr, int index, int heapsize)
{
	int l = left(index);
	int r = right(index);
	int largest = 0;
	if (l < heapsize&&arr[l] > arr[index])
		largest = l;
	else
		largest = index;
	if (r < heapsize&&arr[r] > arr[largest])
		largest = r;
	if (largest != index)
	{
		swap(arr[index], arr[largest]);
		max_heapify(arr, largest, heapsize);
	}

}

template<typename T>
void build_pri(vector<T> &arr)
{
	int heapsize = arr.size();
	for (int i = arr.size() / 2; i >= 0; i--)
	{
		max_heapify(arr, i, heapsize);
	}
}

template<typename T>
int heap_maximum(vector<T> arr)
{
	return arr[0];
}

template<typename T>
T heap_extract_max(vector<T> &arr, int arrlen)
{
	int heapsize = arrlen;
	T max = arr[0];
	arr[0] = arr[heapsize - 1];//last
	heapsize--;
	max_heapify(arr, 0, heapsize);
	return max;
}

template<typename T>
void heap_increase_key(vector<T> arr,int index,T key)//key就是要插入的
{
	if (key < arr[index])
		return; //error new key is smaller than current key
	arr[index] = key;
	while (index>0 && arr[parent(index)] < arr[index])
	{
		swap(arr[index], arr[parent(index)]);
		index = parent(index);
	}
}

template<typename T>
void max_heap_insert(vector<T> &arr, T key)
{
	arr.push_back(key);
	int index = arr.size()-1;
	
	
	while (index>0 && arr[parent(index)] < arr[index])
	{
		swap(arr[index], arr[parent(index)]);
		index = parent(index);
	}
}








//快速排序p95
//核心思想比主元小的放前面大的放后面
int partition(int arr[], int p, int r)
{
	int pivot_elmt = arr[r];//主元
	int i = p - 1;
	for (int j = p; j < r; j++)
	{
		if (arr[j] <= pivot_elmt)
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[r]);
	return i + 1;
}



//p是首元素   r是未元素
void quicksort(int arr[], int p, int r)
{
	if (p < r)
	{
		int q = partition(arr, p, r);
		quicksort(arr, p, q - 1);
		quicksort(arr, q + 1, r);
	}
}


//计数排序p109
template<typename T>
void counting_sort(T arr[],int len,T sortarr[])
{
	//存储关键字和关键字出现的次数
	map<T,int> tmp;
	for (int i = 0; i < len; i++)
	{
		tmp[arr[i]] = tmp[arr[i]] + 1;
	}
	//
	for (map<T, int>::iterator it = tmp.begin(); it != --(tmp.end());)
	{
//		*it.second = *it.second + *(it-1).second;
		//先运行赋值运算符之后在赋值的所以刚好
		it->second = it->second + (++it)->second;
		//(*it).second= 1;
	}/**/

	for (int j = 0; j<len; j++)
	{
		sortarr[tmp[arr[j]]-1] = arr[j];
		tmp[arr[j]] = tmp[arr[j]] - 1;
	}
}

void main01()
{
	int arr[10] = { 1, 3, 5, 2, 4, 9, 7, 6, 8, 0 };
	//insert_sort(arr, 10);
	//merge_sort(arr, 0, 9);
	select_sort(arr,10);
	print(arr,10);
	printf("\n");
	int myarr[8] = { 5, 2, 4, 7, 1, 3, 2, 6 };
	merge_sort(myarr, 0, 7);
	/*merge(myarr, 0, 0, 1);
	merge(myarr, 2, 2, 3);
	merge(myarr, 0, 1, 3);*/
	print(myarr, 8);
	cout << endl;
	int maxheap[] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	//max_heapify(maxheap, 1, 10);
	build_max_heap(maxheap, 10);
	//heap_sort(maxheap, 10);
	printf("build_max_heap");
	print(maxheap, 10);
	cout << endl;


	printf("优先队列");
	vector<int> priqueue = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	build_pri(priqueue);
	max_heap_insert(priqueue, 15);
	max_heap_insert(priqueue, 22);
	max_heap_insert(priqueue, 11);
	max_heap_insert(priqueue, 5);
	int total = priqueue.size();
	while (total > 0)
	{
		int max=heap_extract_max(priqueue, total--);
		cout << max << "  ";
	}

	cout << endl;
	int qarr[] = {2,8,7,1,3,5,6,4};
	quicksort(qarr, 0, 7);
	print(qarr, 8);
	cout << endl;

	int countarr[] = { 2, 5, 3, 0, 2, 3, 0, 3 };
	int sortarr[8] = { 0 };
	counting_sort(countarr, 8, sortarr);
	print(sortarr, 8);

	int sarr[] = { 81, 94, 11, 96, 12, 35, 17, 95, 28, 58, 41, 75, 15 };
	shell_sort<int>(sarr, 13);
	print(sarr, 13);



	system("pause");
}