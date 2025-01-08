#include "Number.h"

void Number::translateToInteger()
{
	value = 0;
	for (int i = (int)digits.size() - 1; i >= 0; i--)
	{
		value += (digits[i] - 48) * std::pow(10, (int)digits.size() - 1 - i);
	}
}

void Number::addDigit(char digit, int index)
{
	digits.push_back(digit);
	indices.push_back(index);
	translateToInteger();
}

bool Number::containsIndex(int index)
{
	for (int i = 0; i < indices.size(); i++)
	{
		if (indices[i] == index)
		{
			return true;
		}
	}
	return false;
}
