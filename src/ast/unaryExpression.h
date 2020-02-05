#pragma once

#include "ast/expression.h"
#include <memory>
#include <string>

namespace AST
{

class UnaryExpression: public Expression
{
public:
	UnaryExpression(std::vector<Parser::ASTToken>& children);

	std::string op;
	std::shared_ptr<UnaryExpression> expr;
};

} //namespace AST
