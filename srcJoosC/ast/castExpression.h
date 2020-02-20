#pragma once

#include "ast/expression.h"
#include "ast/type.h"
#include "ast/unaryExpression.h"
#include <vector>
#include <memory>

namespace AST
{

class CastExpression: public Expression
{
public:
	static std::unique_ptr<CastExpression> create(const Parse::Tree *ptNode);
	explicit CastExpression(const Parse::TCastExpression *ptNode);

	std::unique_ptr<Type> type;
	std::unique_ptr<Expression> rhs;

	std::string toCode() const override;
};

} //namespace AST
