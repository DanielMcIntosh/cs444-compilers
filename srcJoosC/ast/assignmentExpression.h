#pragma once

#include "ast/expression.h"
#include <memory>

namespace AST
{

class AssignmentExpression: public Expression
{
public:
	static std::unique_ptr<AssignmentExpression> create(const Parse::Tree *ptNode);
	explicit AssignmentExpression(const Parse::TAssignment *ptNode);

	std::unique_ptr<Expression> lhs;
	std::unique_ptr<Expression> rhs;

	std::string toCode() const override;
};

} //namespace AST
