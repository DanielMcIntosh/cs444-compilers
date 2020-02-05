#pragma once

#include "ast/conditionalStatement.h"
#include "ast/statement.h"
#include <memory>

namespace AST
{

class IfThenElseStatement: public ConditionalStatement
{
public:
	IfThenElseStatement(std::vector<Parser::ASTToken>& children);

	std::shared_ptr<Statement> elseBody;
};

} //namespace AST
