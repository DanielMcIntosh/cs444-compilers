#pragma once

#include "ast/node.h"
#include "ast/expression.h"
#include "ast/type.h"

#include <string>
#include <memory>
#include <variant>

namespace AST
{

class BinaryExpression: public Expression
{
public:
	BinaryExpression(std::vector<Parser::ASTToken>& children);

	std::string op;
	std::shared_ptr<Expression> lhs;
	// instanceof has a rhs that's a ReferenceType instead of an Expression
	std::shared_ptr<std::variant<Expression, Type>> rhs;
};

} //namespace AST
