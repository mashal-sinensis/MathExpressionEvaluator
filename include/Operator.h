#pragma once

class Operator : public ExpressionAtom
{
private:
	char value;
public:
	Operator(char value, ExpressionAtomType type) : value(value), ExpressionAtom(type) {}
	~Operator() = default;
	int getValue() const { return value; }
};