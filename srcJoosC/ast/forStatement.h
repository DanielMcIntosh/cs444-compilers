#pragma once

#include "ast/conditionalStatement.h"
#include "ast/statement.h"
#include <memory>

namespace AST
{

class ForStatement: public ConditionalStatement
{
public:
	ForStatement(std::vector<Parser::ASTToken>& children);

	std::shared_ptr<Expression> init;
	std::shared_ptr<Expression> increment;
};

} //namespace AST
