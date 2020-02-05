#pragma once

#include "ast/expression.h"
#include <memory>

namespace AST
{

class AssignmentExpression: public Expression
{
public:
	AssignmentExpression(std::vector<Parser::ASTToken>& children);

	std::shared_ptr<Expression> lhs;
	std::shared_ptr<Expression> rhs;
};

} //namespace AST
