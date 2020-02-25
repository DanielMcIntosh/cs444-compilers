#pragma once

#include "ast/memberDeclaration.h"
#include <memory>

namespace AST
{

class Block;
class VariableDeclaration;
class MethodDeclarator;

class ConstructorDeclaration: public MemberDeclaration
{
public:
	static std::unique_ptr<ConstructorDeclaration> create(const Parse::Tree *ptNode);
	explicit ConstructorDeclaration(const Parse::TConstructorDeclaration *ptNode);
	std::string toCode() const override;

	using MemberDeclaration::equals;
	virtual bool equals(ConstructorDeclaration *) override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) override;
protected:
	std::string identifier;
	std::vector<std::unique_ptr<VariableDeclaration>> parameters;
	std::unique_ptr<Block> body;
private:
	// not convinced this is the best way of dealing with needing 2 members from declarator
	ConstructorDeclaration(std::vector<std::unique_ptr<Modifier>> mods, MethodDeclarator &&declarator, std::unique_ptr<Block> block);
};

} //namespace AST
