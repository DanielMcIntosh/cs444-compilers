#pragma once

#include "ast/statement.h"
#include "ast/expression.h"
#include <memory>

namespace AST
{

class ReturnStatement: public Statement
{
public:
	ReturnStatement(std::vector<Parser::ASTToken>& children);

	// nullable
	std::shared_ptr<Expression> returnValue;
};

} //namespace AST
