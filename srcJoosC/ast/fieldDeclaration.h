#pragma once

#include "ast/memberDeclaration.h"
#include "ast/variableDeclaration.h"
#include <memory>

namespace AST
{

class FieldDeclaration: public MemberDeclaration
{
public:
	static std::unique_ptr<FieldDeclaration> create(const Parse::Tree *ptNode);
	explicit FieldDeclaration(const Parse::TFieldDeclaration *ptNode);

	std::unique_ptr<VariableDeclaration> declaration;

	std::string toCode() const override;

	virtual bool equals(FieldDeclaration *) override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
};

} //namespace AST
