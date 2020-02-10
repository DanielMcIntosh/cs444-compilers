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

	std::string op;
	std::shared_ptr<UnaryExpression> expr;

	std::string toCode() override { return "[UnaryExpression]"; }
};

} //namespace AST
