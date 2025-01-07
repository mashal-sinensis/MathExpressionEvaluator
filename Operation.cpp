#include "Operation.h"

int Operation::solve()
{
	switch (mainOperator->getValue())
	{
	case '+':
		if ((long)firstOperand->getValue() + (long)secondOperand->getValue() > INT_MAX
			|| (long)firstOperand->getValue() + (long)secondOperand->getValue() < INT_MIN)
		{
			throw std::exception("operation result out of bounds of integer limits");
		}
		return firstOperand->getValue() + secondOperand->getValue();
	case '-':
		if ((long)firstOperand->getValue() - (long)secondOperand->getValue() > INT_MAX
			|| (long)firstOperand->getValue() - (long)secondOperand->getValue() < INT_MIN)
		{
			throw std::exception("operation result out of bounds of integer limits");
		}
		return firstOperand->getValue() - secondOperand->getValue();
	case '*':
		if ((long)firstOperand->getValue() * (long)secondOperand->getValue() > INT_MAX
			|| (long)firstOperand->getValue() * (long)secondOperand->getValue() < INT_MIN)
		{
			throw std::exception("operation result out of bounds of integer limits");
		}
		return firstOperand->getValue() * secondOperand->getValue();
	case '/':
		if (secondOperand->getValue() == 0) {
			throw std::exception();
		}
		if ((long)firstOperand->getValue() / (long)secondOperand->getValue() > INT_MAX
			|| (long)firstOperand->getValue() / (long)secondOperand->getValue() < INT_MIN)
		{
			throw std::exception("operation result out of bounds of integer limits");
		}
		return firstOperand->getValue() / secondOperand->getValue();
	case '%':
		if ((long)firstOperand->getValue() % (long)secondOperand->getValue() > INT_MAX
			|| (long)firstOperand->getValue() % (long)secondOperand->getValue() < INT_MIN)
		{
			throw std::exception("operation result out of bounds of integer limits");
		}
		return firstOperand->getValue() % secondOperand->getValue();
	default:
		throw std::exception();
	}
}