#pragma once

#include "ast/memberDeclaration.h"
#include <memory>

namespace AST
{

class VariableDeclaration;
class FieldAccess;

class FieldDeclaration: public MemberDeclaration
{
public:
	static std::unique_ptr<FieldDeclaration> create(const Parse::Tree *ptNode);
	explicit FieldDeclaration(const Parse::TFieldDeclaration *ptNode);
	std::string toCode() const override;

	using MemberDeclaration::equals;
	[[gnu::pure]]
	virtual bool equals(const FieldDeclaration *) const override;
	[[gnu::pure]]
	bool idEquals(const FieldDeclaration *) const;
	[[gnu::pure]]
	bool idEquals(const FieldAccess *) const;

	virtual int getTypeId() override { return 0; }

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) override;

	std::unique_ptr<VariableDeclaration> declaration;
};

} //namespace AST
