#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include"cstring.h"
#include"ctime.h"
#include"cmath.h"
#include<string>
#include<iostream>
#include<map>
#include"file.h"
#include<stdarg.h>
#include<sstream>
using namespace std;
int maxof(int n_args, ...)
{
	va_list ap;
	va_start(ap, n_args);
	int max = va_arg(ap, int);
	for (int i = 2; i <= n_args; i++) {
		int a = va_arg(ap, int);
		if (a > max) max = a;
	}
	va_end(ap);
	return max;
}




int main0423()
{
	char str[100] = "1";
	char * stocktypewithout = replace(replace(str, "(,", ""), "),", "");
	FILE *fwp = fopen("d:/Hook.txt", "a");
	fputc('1', fwp);
	fclose(fwp);
	printf("%s\n",get_time("%Y-%m-%d %H:%M:%S"));
	printf("%d\n", IsPrime(7));
	printf("%d\n", IsPrime(17));
	printf("%d\n", IsPrime(27));


	char *pHeader = "HEADER|MTP1.00 |   1908139| 4942|        |XSHG01|20151221-16:30:03.200|0|E11";
	std::string line=hsGetCol(pHeader,3, '|');

	char *strsp = "600121#1#1##3";
	for (int i = 0; i < 5; i++)
	{
		std::string line = hsGetCol(strsp, i, '#');
		std::cout << line << std::endl;
	}
	
	int marketno = atoi(hsGetCol(strsp, 1, '#').c_str());
	cout << marketno << endl;
	traversal_dir("F:\\");
	system("pause");
	return 0;
}

//实现重复累加
int main23()
{
	using namespace std;
	string strs[] = { "600000", "600001", "600570", "600001", "600571", "600570", "600570", "600570" };
	map<string, int> seqid;
	int imax = 0;
	for (int i = 0; i <8 ;i++)
	{
		int tmp=seqid[strs[i]] = ++seqid[strs[i]];
		imax = imax>tmp ? imax : tmp;
	}

	
	string s1 = "dasfdadf";
	string s = s1 + "fdafs";
	cout << s;
	system("pause");
	return 0;
}


int main777()
{
	printf("%d\n",get_weekday());
	//printf("%s", get_time("%H:%M:%s"));
	printf("%s\n",GetFormatedTime());
	map<int,int> maptest;
	maptest[1] = 1;
	maptest[2] = 2;
	maptest.erase(1);
	maptest.erase(1);


	cout<<maxof(4,"112","333","6345","hey")<<endl;
	
	system("pause");
	return 0;
}