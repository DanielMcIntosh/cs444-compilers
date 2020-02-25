#pragma once

#include "ast/memberDeclaration.h"
#include <memory>

namespace AST
{

class VariableDeclaration;

class FieldDeclaration: public MemberDeclaration
{
public:
	static std::unique_ptr<FieldDeclaration> create(const Parse::Tree *ptNode);
	explicit FieldDeclaration(const Parse::TFieldDeclaration *ptNode);

	std::unique_ptr<VariableDeclaration> declaration;

	std::string toCode() const override;

	using MemberDeclaration::equals;
	virtual bool equals(FieldDeclaration *) override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) override;
	// TODO: remove this
	Semantic::SemanticErrorType initScope(Semantic::Scope &parentScope) override;
};

} //namespace AST
