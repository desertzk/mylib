#include"cmath.h"



bool IsPrime(int candidate)
{
	if ((candidate & 1) != 0) // 是奇数
	{
		int limit = (int)sqrt((double)candidate);
		for (int divisor = 3; divisor <= limit; divisor += 2) // divisor = 3、5、7...candidate的平方根
		{
			if ((candidate % divisor) == 0)
				return false;
		}
		return true;
	}
	return (candidate == 2); // 除了2，其它偶是全都不是质数
}