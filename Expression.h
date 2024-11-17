#pragma once

#include <string>
#include <vector>
#include "ExpressionAtom.h"
#include "Number.h"
#include "Operator.h"
#include "Operation.h"

using namespace std;

class Expression {
private:
	string strExpression;
public:
	vector<ExpressionAtom*> indexPointers;
	vector<ExpressionAtom*> uniqueBeginIndexPointers;
	vector<Number*> numbers;
	Expression(string strExpression);
	void evaluateExpressionAtoms();
	void setStrExpression(string strExpression);
	string getStrExpression() const { return strExpression; }
	int solve();
	bool simplifyStep();
	~Expression();
};