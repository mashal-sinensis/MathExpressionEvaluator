#include <iostream>
#include "Expression.h"

using namespace std;

#define ISNUMBER(str, index) str[index] > 47 && str[index] < 58

string truncateString(string input)
{
	string temp = "";
	for (char c : input)
	{
		if (c != ' ' && c != '\t')
		{
			temp += c;
		}
	}
	return temp;
}

Expression::Expression(string strExpression)
{
	setStrExpression(strExpression);
}

void Expression::evaluateExpressionAtoms()
{
	for (ExpressionAtom* atom : uniqueBeginIndexPointers)
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
		else if (strExpression[i] != '+' && strExpression[i] != '-' && strExpression[i] != '/' && strExpression[i] != '*' && strExpression[i] != '%')
		{
			throw exception();
		}
		else
		{
			Operator* add = new Operator(strExpression[i], ExpressionAtomType::OperatorType);
			indexPointers.push_back(add);
			uniqueBeginIndexPointers.push_back(add);
		}
	}
}

void Expression::setStrExpression(string strExpression)
{
	this->strExpression = truncateString(strExpression);
	evaluateExpressionAtoms();
}

int Expression::solve()
{
	while (simplifyStep()) {}

	if (uniqueBeginIndexPointers.size() > 3)
	{
		throw exception();
	}
	if (uniqueBeginIndexPointers[0]->getType() != ExpressionAtomType::NumberType
		&& uniqueBeginIndexPointers[1]->getType() != ExpressionAtomType::OperatorType
		&& uniqueBeginIndexPointers[2]->getType() != ExpressionAtomType::NumberType)
	{
		throw exception();
	}
}

string translateIntegerToString(int value)
{
	if (value == 0)
	{
		return "0";
	}

	string strValue = "";
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
	vector<Operation*> operations;

	if (uniqueBeginIndexPointers.size() < 3)
	{
		return false;
	}

	for (int i = 0; i < uniqueBeginIndexPointers.size() - 2; i += 2)
	{
		if (uniqueBeginIndexPointers[i]->getType() != ExpressionAtomType::NumberType
			&& uniqueBeginIndexPointers[i + 1]->getType() != ExpressionAtomType::OperatorType
			&& uniqueBeginIndexPointers[i + 2]->getType() != ExpressionAtomType::NumberType)
		{
			throw exception();
		}

		Number* num1 = static_cast<Number*>(uniqueBeginIndexPointers[i]);
		Number* num2 = static_cast<Number*>(uniqueBeginIndexPointers[i + 2]);
		Operator* op = static_cast<Operator*>(uniqueBeginIndexPointers[i + 1]);

		Operation* operation = new Operation(num1, num2, op);
		operations.push_back(operation);
	}

	vector<Operation*> sortedOperations;

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
	
	vector<int> indicesOfHighestOrderOperation;
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

	cout << "\n" << sortedOperations[0]->firstOperand->getValue() << (char)sortedOperations[0]->mainOperator->getValue() << sortedOperations[0]->secondOperand->getValue() << " = ";

	int value = sortedOperations[0]->solve();

	cout << value << endl;

	string valueString = translateIntegerToString(value);
	bool addedValueString = false;
	string newStrExpression = "";

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

	cout << "Thus, " << strExpression << " = " << newStrExpression << endl;
	setStrExpression(newStrExpression);

	for (Operation* operation : operations)
	{
		delete operation;
	}

	return true;
}

Expression::~Expression()
{
	for (ExpressionAtom* atom : uniqueBeginIndexPointers)
	{
		delete atom;
	}
}