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
	CastExpression(std::vector<Parser::ASTToken>& children);

	std::shared_ptr<Type> type;
	std::shared_ptr<UnaryExpression> rhs;
};

} //namespace AST
