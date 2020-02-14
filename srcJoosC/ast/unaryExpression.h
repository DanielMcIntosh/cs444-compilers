#pragma once

#include "ast/expression.h"
#include <memory>
#include <string>

namespace AST
{

class UnaryExpression: public Expression
{
public:
	static std::unique_ptr<UnaryExpression> create(const Parse::Tree *ptNode);
	UnaryExpression(const Parse::TUnaryExpression *ptNode);
	UnaryExpression(const Parse::TUnaryExpressionNotPlusMinus *ptNode);

	enum class Variant
	{
		Minus,
		Bang,
		Max
	} op;

	std::unique_ptr<Expression> expr;

	std::string toCode() override;
};

std::string operator+(std::string str, UnaryExpression::Variant type);
std::string operator+=(std::string& str, UnaryExpression::Variant type);
std::ostream& operator<<(std::ostream& os, UnaryExpression::Variant type);

} //namespace AST
