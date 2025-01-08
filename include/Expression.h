#pragma once

#include <string>
#include <vector>
#include "ExpressionAtom.h"
#include "Number.h"
#include "Operator.h"
#include "Operation.h"

class Expression {
	struct SubExpressionIndices {
		SubExpressionIndices(int startIndex, int endIndex) : startIndex(startIndex), endIndex(endIndex) {}
		int startIndex;
		int endIndex;
	};

private:
	std::string strExpression;
public:
	bool simplified;
	std::vector<ExpressionAtom*> indexPointers;
	std::vector<ExpressionAtom*> uniqueBeginIndexPointers;
	std::vector<Expression*> directSubExpressions;
	std::vector<std::string*> directSubExpressionStrings;
	std::vector<SubExpressionIndices*> directSubExpressionIndices;
	std::vector<Number*> numbers;
	Expression(std::string strExpression);
	void evaluateExpressionAtoms();
	void setStrExpression(std::string strExpression);
	std::string getStrExpression() const { return strExpression; }
	void solve();
	bool simplifyStep();
	void classifyDirectSubExpressions();
	void deallocSubExpressionVariables();
	void directSubExpressionPrintChain(int nestValue);
	~Expression();
};