#include "MathFunctions.h"

int MathFunctions::pow(int num, int power)
{
	int sum{1};
	for (int i = 0; i < power; i++)
	{
		sum *= num;
	}
	return sum;
}