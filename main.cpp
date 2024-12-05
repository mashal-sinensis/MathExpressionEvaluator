#include <iostream>
#include <string>
#include "Expression.h"
#include "Number.h"
#include "Operator.h"

using namespace std;

int main()
{
	bool run{ true };

	while (run)
	{
		string inputExpression;
		string answer = "";
		vector<Number*> numbers;
		cout << "Enter Expression: ";
		getline(cin, inputExpression);
		Expression* mainExpression = 
			new Expression(inputExpression);
		mainExpression->solve();
		cout << "Answer: " << 
			mainExpression->getStrExpression() << endl;
		cout << "\n-------------\n";
		delete mainExpression;
	}

	return 0;
}



