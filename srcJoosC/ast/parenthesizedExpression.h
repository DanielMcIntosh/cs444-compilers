#pragma once

#include "ast/expression.h"
#include <memory>

namespace AST
{

class ParenthesizedExpression: public Expression
{
public:
	static std::unique_ptr<ParenthesizedExpression> create(const Parse::Tree *ptNode);
	ParenthesizedExpression(const Parse::TParenthesizedExpression *ptNode);

	std::shared_ptr<Expression> expr;

	std::string toCode() override { return "[ParenthesizedExpression]"; }
};

} //namespace AST
