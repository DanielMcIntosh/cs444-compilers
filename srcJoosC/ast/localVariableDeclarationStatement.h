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
	std::string toCode() const override;

	std::unique_ptr<VariableDeclaration> declaration;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
};

} //namespace AST
