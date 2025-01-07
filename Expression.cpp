#include <iostream>
#include "Expression.h"

#define ISNUMBER(str, index) str[index] > 47 && str[index] < 58

std::string truncateString(std::string input)
{
	std::string temp = "";
	for (char c : input)
	{
		if (c != ' ' && c != '\t')
		{
			temp += c;
		}
	}
	return temp;
}

Expression::Expression(std::string strExpression)
{
	setStrExpression(strExpression);
}

void Expression::evaluateExpressionAtoms()
{
	for (ExpressionAtom* atom : uniqueBeginIndexPointers) // clear atoms from previous expression evals
	{
		delete atom;
	}

	uniqueBeginIndexPointers = {};
	indexPointers = {};
	numbers = {};

	for (int i = 0; i < strExpression.size(); i++)
	{
		if (ISNUMBER(strExpression, i))
		{
			bool createNewNumber = true;
			if (i != 0 && ISNUMBER(strExpression, i - 1))
			{
				if (!numbers.empty() && numbers[numbers.size() - 1]->containsIndex(i - 1))
				{
					createNewNumber = false;
				}
			}

			if (createNewNumber)
			{
				Number* newNumber = new Number(ExpressionAtomType::NumberType);
				newNumber->addDigit(strExpression[i], i);
				numbers.push_back(newNumber);
				indexPointers.push_back(newNumber);
				uniqueBeginIndexPointers.push_back(newNumber);
			}
			else
			{
				numbers[numbers.size() - 1]->addDigit(strExpression[i], i);
				indexPointers.push_back(indexPointers[i - 1]);
			}
		}
		else if (strExpression[i] != '+' && strExpression[i] != '-' && strExpression[i] != '/' && strExpression[i] != '*' && strExpression[i] != '%' && strExpression[i] != '(' && strExpression[i] != ')')
		{
			throw std::exception();
		}
		else
		{
			Operator* op = new Operator(strExpression[i], ExpressionAtomType::OperatorType);
			indexPointers.push_back(op);
			uniqueBeginIndexPointers.push_back(op);
		}
	}
}

std::string inclusive_replace(std::string input_string, std::string replace_string, int start, int end)
{
	std::string output;
	bool added_string = false;
	bool replace_area = false;

	for (int i = 0; i < input_string.size(); i++)
	{
		replace_area = (i <= end) && (i >= start);

		if (replace_area)
		{
			if (!added_string)
			{
				output += replace_string;
				added_string = true;
			}
		}
		else
		{
			output += input_string[i];
		}
	}

	return output;
}

void Expression::setStrExpression(std::string strExpression)
{
	this->strExpression = truncateString(strExpression);
	evaluateExpressionAtoms();
	classifyDirectSubExpressions();

	if (directSubExpressions.size() != 0)
	{
		directSubExpressions[0]->solve();
		std::string tempString = directSubExpressions[0]->getStrExpression();
		directSubExpressions.erase(directSubExpressions.begin());
		setStrExpression(inclusive_replace(this->strExpression, tempString, directSubExpressionIndices[0]->startIndex, directSubExpressionIndices[0]->endIndex));
	}
}

void Expression::solve()
{
	while (simplifyStep()) {}
}

std::string translateIntegerToString(int value)
{
	if (value == 0)
	{
		return "0";
	}

	std::string strValue = "";
	int tempValue{ value };

	int place = 1000000000;
	while (tempValue < place)
	{
		place /= 10;
	}

	while (tempValue != 0)
	{
		strValue += (char)((tempValue / place) + 48);

		if (place != 1 && (tempValue - ((tempValue / place) * place)) == 0)
		{
			while (place != 1)
			{
				strValue += '0';
				place /= 10;
			}
			tempValue = 0;
		}
		else
		{
			tempValue -= ((tempValue / place) * place);
			place /= 10;
		}
	}

	return strValue;
}

bool Expression::simplifyStep()
{
	std::vector<Operation*> operations;

	if (uniqueBeginIndexPointers.size() < 3)
	{
		return false;
	}

	for (int i = 0; i < uniqueBeginIndexPointers.size() - 2; i += 2)
	{
		if (uniqueBeginIndexPointers[i]->getType() != ExpressionAtomType::NumberType
			&& uniqueBeginIndexPointers[i + 1]->getType() != ExpressionAtomType::OperatorType
			&& uniqueBeginIndexPointers[i + 2]->getType() != ExpressionAtomType::NumberType)
		{ // validation check
			throw std::exception();
		}

		Number* num1 = static_cast<Number*>(uniqueBeginIndexPointers[i]);
		Number* num2 = static_cast<Number*>(uniqueBeginIndexPointers[i + 2]);
		Operator* op = static_cast<Operator*>(uniqueBeginIndexPointers[i + 1]);

		Operation* operation = new Operation(num1, num2, op);
		operations.push_back(operation);
	}

	std::vector<Operation*> sortedOperations;

	// Multiplication Pass
	for (int i = 0; i < operations.size(); i++)
	{
		if (operations[i]->mainOperator->getValue() == '*')
		{
			sortedOperations.push_back(operations[i]);
		}
	}

	// Division Pass
	for (int i = 0; i < operations.size(); i++)
	{
		if (operations[i]->mainOperator->getValue() == '/')
		{
			sortedOperations.push_back(operations[i]);
		}
	}

	// Modulus Pass
	for (int i = 0; i < operations.size(); i++)
	{
		if (operations[i]->mainOperator->getValue() == '%')
		{
			sortedOperations.push_back(operations[i]);
		}
	}

	// Subtraction Pass
	for (int i = 0; i < operations.size(); i++)
	{
		if (operations[i]->mainOperator->getValue() == '-')
		{
			sortedOperations.push_back(operations[i]);
		}
	}

	// Addition Pass
	for (int i = 0; i < operations.size(); i++)
	{
		if (operations[i]->mainOperator->getValue() == '+')
		{
			sortedOperations.push_back(operations[i]);
		}
	}

	std::vector<int> indicesOfHighestOrderOperation;
	for (int i = 0; i < indexPointers.size(); i++)
	{
		if (indexPointers[i] == sortedOperations[0]->firstOperand)
		{
			indicesOfHighestOrderOperation.push_back(i);
		}
		else if (indexPointers[i] == sortedOperations[0]->mainOperator)
		{
			indicesOfHighestOrderOperation.push_back(i);
		}
		else if (indexPointers[i] == sortedOperations[0]->secondOperand)
		{
			indicesOfHighestOrderOperation.push_back(i);
		}
	}

	std::cout << "\n" << sortedOperations[0]->firstOperand->getValue() << (char)sortedOperations[0]->mainOperator->getValue() << sortedOperations[0]->secondOperand->getValue() << " = ";

	int value = sortedOperations[0]->solve();

	std::cout << value << std::endl;

	std::string valueString = translateIntegerToString(value);
	bool addedValueString = false;
	std::string newStrExpression = "";

	for (int i = 0; i < strExpression.size(); i++)
	{
		bool indexOfOperation = false;

		for (int j = 0; j < indicesOfHighestOrderOperation.size(); j++)
		{
			if (i == indicesOfHighestOrderOperation[j])
			{
				indexOfOperation = true;
				break;
			}
		}

		if (indexOfOperation)
		{
			if (!addedValueString)
			{
				newStrExpression += valueString;
				addedValueString = true;
			}
		}
		else
		{
			newStrExpression += strExpression[i];
		}
	}

	std::cout << "Thus, " << strExpression << " = " << newStrExpression << std::endl;
	setStrExpression(newStrExpression);

	for (Operation* operation : operations)
	{
		delete operation;
	}

	return true;
}

void Expression::classifyDirectSubExpressions()
{
	deallocSubExpressionVariables();

	int parenthesisLevel = 0;
	int start = 0;

	for (int i = 0; i < strExpression.size(); i++)
	{
		if (strExpression[i] == '(')
		{
			if (parenthesisLevel == 0) {
				Expression* newDirectSubExpression = new Expression("");
				directSubExpressions.push_back(newDirectSubExpression);
				directSubExpressionStrings.push_back(new std::string);
				start = i;
				parenthesisLevel++;
				continue;
			}

			parenthesisLevel++;
		}

		if (strExpression[i] == ')')
		{
			parenthesisLevel--;
			if (parenthesisLevel == 0)
			{
				directSubExpressions[directSubExpressions.size() - 1]->setStrExpression(*directSubExpressionStrings[directSubExpressionStrings.size() - 1]);
				directSubExpressionIndices.push_back(new Expression::SubExpressionIndices(start, i));
				continue;
			}
		}

		if (parenthesisLevel != 0)
		{
			directSubExpressionStrings[directSubExpressionStrings.size() - 1]->push_back(strExpression[i]);
		}
	}
}

void Expression::deallocSubExpressionVariables()
{
	for (Expression* expression : directSubExpressions)
	{
		delete expression;
	}

	directSubExpressionStrings.clear();
}

void Expression::directSubExpressionPrintChain(int nestValue)
{
	for (int i = 0; i < directSubExpressions.size(); i++)
	{
		std::cout << "Direct Sub Expression NestValue #" << nestValue + 1 << ", Number #" << i + 1 << ": " << directSubExpressions[i]->getStrExpression() << std::endl;
		directSubExpressions[i]->directSubExpressionPrintChain(nestValue + 1);
	}
}

Expression::~Expression()
{
	for (ExpressionAtom* atom : uniqueBeginIndexPointers)
	{
		delete atom;
	}
}