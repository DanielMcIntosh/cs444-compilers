#pragma once

#include "ast/memberDeclaration.h"
#include <memory>

namespace AST
{

class VariableDeclaration;
class FieldAccess;
class Expression;

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

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic) override;
	Semantic::SemanticErrorType resolveExprs() override;

	// need a src for non-static fields, but not for static fields
	std::unique_ptr<FieldAccess> asFieldAccess(std::unique_ptr<Expression> src = nullptr);

public:
	std::unique_ptr<VariableDeclaration> varDecl;
};

} //namespace AST
