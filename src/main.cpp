#include <iostream>
#include <string>
#include "Expression.h"

int main()
{
	bool run{ true };

	while (run)
	{
		std::string inputExpression;
		std::cout << "Enter Expression: ";

		std::getline(std::cin, inputExpression);

		Expression* mainExpression = new Expression(inputExpression);

		mainExpression->solve();

		std::cout << "Answer: " << mainExpression->getStrExpression() << std::endl << std::endl;
	}
}