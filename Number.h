#pragma once

#include <vector>
#include "ExpressionAtom.h"
#include "MathFunctions.h"

class Number : public ExpressionAtom
{
private:
	std::vector<char> digits;
	std::vector<int> indices;
	int value;
	void translateToInteger();
public:
	Number(ExpressionAtomType type) : value(0), ExpressionAtom(type) {}
	void addDigit(char digit, int index);
	bool containsIndex(int index);
	int getValue() const { return value; }
	~Number() = default;
};