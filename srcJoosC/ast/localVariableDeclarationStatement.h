#pragma once

#include "ast/statement.h"
#include <memory>

namespace AST
{

class VariableDeclaration;

class LocalVariableDeclarationStatement: public Statement
{
public:
	static std::unique_ptr<LocalVariableDeclarationStatement> create(const Parse::Tree *ptNode);
	explicit LocalVariableDeclarationStatement(const Parse::TLocalVariableDeclarationStatement *ptNode);
	std::string toCode() const override;

	std::unique_ptr<VariableDeclaration> declaration;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) override;
};

} //namespace AST
