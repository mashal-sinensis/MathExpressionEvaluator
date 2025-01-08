#pragma once

#include "Number.h"
#include "Operator.h"
#include <climits>
#include <stdexcept>
#include <iostream>

class Operation
{
public:
	Number* firstOperand;
	Number* secondOperand;
	Operator* mainOperator;

	Operation(Number* firstOperand, Number* secondOperand, Operator* mainOperator)
		: firstOperand(firstOperand), secondOperand(secondOperand), mainOperator(mainOperator) {}

	int solve();
};
