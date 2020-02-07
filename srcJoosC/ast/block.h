#pragma once

#include "ast/statement.h"
#include <memory>
#include <vector>

namespace AST
{

class Block: public Statement
{
public:
	Block(std::vector<Parser::ASTToken>& children);

	std::vector<std::shared_ptr<Statement>> statements;
};

} //namespace AST
