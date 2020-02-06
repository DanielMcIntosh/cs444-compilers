#pragma once

#include "ast/statement.h"
#include "ast/variableDeclaration.h"
#include <memory>

namespace AST
{

class LocalVariableDeclarationStatement: public Statement
{
public:
	LocalVariableDeclarationStatement(std::vector<Parser::ASTToken>& children);

	std::shared_ptr<VariableDeclaration> declaration;
};

} //namespace AST
