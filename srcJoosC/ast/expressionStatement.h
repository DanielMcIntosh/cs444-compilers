#pragma once

#include "ast/statement.h"
#include "ast/expression.h"
#include <memory>

namespace AST
{

class ExpressionStatement: public Statement
{
public:
	ExpressionStatement(std::vector<Parser::ASTToken>& children);

	// nullable
	std::shared_ptr<Expression> expression;
};

} //namespace AST
