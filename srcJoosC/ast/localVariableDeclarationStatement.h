#pragma once

#include "ast/statement.h"
#include "ast/variableDeclaration.h"
#include <memory>

namespace AST
{

class LocalVariableDeclarationStatement: public Statement
{
public:
	static std::unique_ptr<LocalVariableDeclarationStatement> create(const Parse::Tree *ptNode);
	LocalVariableDeclarationStatement(const Parse::TLocalVariableDeclarationStatement *ptNode);

	std::shared_ptr<VariableDeclaration> declaration;

	std::string toCode() override { return "[LocalVariableDeclarationStatement]"; }
};

} //namespace AST
