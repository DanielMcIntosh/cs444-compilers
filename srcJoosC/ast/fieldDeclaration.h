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
	std::string toCode() const override;

	using MemberDeclaration::equals;
	virtual bool equals(FieldDeclaration *) override;
	bool idEquals(FieldDeclaration *) const;

	virtual int getTypeId() override { return 0; }

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) override;
	// TODO: remove this
	Semantic::SemanticErrorType initScope(Semantic::Scope &parentScope) override;
protected:
	std::unique_ptr<VariableDeclaration> declaration;
};

} //namespace AST
