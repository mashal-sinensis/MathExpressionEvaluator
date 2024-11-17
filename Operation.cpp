#include "Operation.h"

int Operation::solve()
{
	switch (mainOperator->getValue())
	{
	case '+':
		return firstOperand->getValue() + secondOperand->getValue();
	case '-':
		return firstOperand->getValue() - secondOperand->getValue();
	case '*':
		return firstOperand->getValue() * secondOperand->getValue();
	case '/':
		if (secondOperand->getValue() == 0) {
			throw exception();
		}
		return firstOperand->getValue() / secondOperand->getValue();
	case '%':
		return firstOperand->getValue() % secondOperand->getValue();
	default:
		throw exception();
	}
}
