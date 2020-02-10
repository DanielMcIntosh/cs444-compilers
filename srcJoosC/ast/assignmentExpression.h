#pragma once

#include "ast/expression.h"
#include <memory>

namespace AST
{

class AssignmentExpression: public Expression
{
public:
	static std::unique_ptr<AssignmentExpression> create(const Parse::Tree *ptNode);
	AssignmentExpression(const Parse::TAssignment *ptNode);

	std::shared_ptr<Expression> lhs;
	std::shared_ptr<Expression> rhs;

	std::string toCode() override { return "[AssignmentExpression]"; }
};

} //namespace AST
