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
	explicit LocalVariableDeclarationStatement(const Parse::TLocalVariableDeclarationStatement *ptNode);

	std::unique_ptr<VariableDeclaration> declaration;

	std::string toCode() const override;
};

} //namespace AST
