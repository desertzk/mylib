#include"cmath.h"



bool IsPrime(int candidate)
{
	if ((candidate & 1) != 0) // ������
	{
		int limit = (int)sqrt((double)candidate);
		for (int divisor = 3; divisor <= limit; divisor += 2) // divisor = 3��5��7...candidate��ƽ����
		{
			if ((candidate % divisor) == 0)
				return false;
		}
		return true;
	}
	return (candidate == 2); // ����2������ż��ȫ����������
}