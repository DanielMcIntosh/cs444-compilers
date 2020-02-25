#pragma once

#include "ast/memberDeclaration.h"
#include <memory>

namespace AST
{

class Type;
class VariableDeclaration;
class Block;
class MethodHeader;

class MethodDeclaration: public MemberDeclaration
{
public:
	static std::unique_ptr<MethodDeclaration> create(const Parse::Tree *ptNode);
	explicit MethodDeclaration(const Parse::TMethodDeclaration *ptNode);
	explicit MethodDeclaration(const Parse::TAbstractMethodDeclaration *ptNode);
	std::string toCode() const override;

	std::unique_ptr<Type> returnType;
	std::string identifier;
	std::vector<std::unique_ptr<VariableDeclaration>> parameters;
	// nullable
	std::unique_ptr<Block> body;

	using MemberDeclaration::equals;
	virtual bool equals(MethodDeclaration *) override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) override;
private:
	MethodDeclaration(MethodHeader&& header, std::unique_ptr<Block> block);
};

} //namespace AST
