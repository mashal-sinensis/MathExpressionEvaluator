#pragma once

enum ExpressionAtomType {
	OperatorType,
	NumberType
};

class ExpressionAtom {
private: 
	ExpressionAtomType type;
public:
	ExpressionAtom(ExpressionAtomType type) : type(type) {}
	virtual ~ExpressionAtom() = default;
	ExpressionAtomType getType() const { return type; }
};