#include "Operation.h"

int Operation::solve()
{
	try {

		switch (mainOperator->getValue())
		{
		case '+':
			if ((long)firstOperand->getValue() + (long)secondOperand->getValue() > INT_MAX
			|| (long)firstOperand->getValue() + (long)secondOperand->getValue() < INT_MIN)
			{
				throw ("operation result out of bounds of integer limits");
			}
			return firstOperand->getValue() + secondOperand->getValue();
		case '-':
			if ((long)firstOperand->getValue() - (long)secondOperand->getValue() > INT_MAX
			|| (long)firstOperand->getValue() - (long)secondOperand->getValue() < INT_MIN)
			{
				throw ("operation result out of bounds of integer limits");
			}
			return firstOperand->getValue() - secondOperand->getValue();
		case '*':
			if ((long)firstOperand->getValue() * (long)secondOperand->getValue() > INT_MAX
			|| (long)firstOperand->getValue() * (long)secondOperand->getValue() < INT_MIN)
			{
				throw ("operation result out of bounds of integer limits");
			}
			return firstOperand->getValue() * secondOperand->getValue();
		case '/':
			if (secondOperand->getValue() == 0) {
				throw ("operation results in divide by zero");
			}
			if ((long)firstOperand->getValue() / (long)secondOperand->getValue() > INT_MAX
			|| (long)firstOperand->getValue() / (long)secondOperand->getValue() < INT_MIN)
			{
				throw ("operation result out of bounds of integer limits");
			}
			return firstOperand->getValue() / secondOperand->getValue();
		case '%':
			if ((long)firstOperand->getValue() % (long)secondOperand->getValue() > INT_MAX
				|| (long)firstOperand->getValue() % (long)secondOperand->getValue() < INT_MIN)
			{
				throw ("operation result out of bounds of integer limits");
			}
			return firstOperand->getValue() % secondOperand->getValue();
		default:
			throw ("Default Reached");
		}
	} catch (std::string message) {
		std::cout << "ERROR: " << message << std::endl;
	}
}
