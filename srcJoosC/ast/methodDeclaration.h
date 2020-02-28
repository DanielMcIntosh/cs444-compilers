#pragma once

#include "ast/memberDeclaration.h"
#include "ast/statement.h"
#include <memory>

namespace AST
{

class Type;
class VariableDeclaration;
class Block;
class MethodHeader;
class MethodInvocation;

class MethodDeclaration: public MemberDeclaration
{
public:
	EXPORT static std::unique_ptr<MethodDeclaration> create(const Parse::Tree *ptNode);
	EXPORT explicit MethodDeclaration(const Parse::TMethodDeclaration *ptNode);
	EXPORT explicit MethodDeclaration(const Parse::TAbstractMethodDeclaration *ptNode);
	std::string toCode() const override;

	using MemberDeclaration::equals;
	[[gnu::pure]]
	virtual bool equals(const MethodDeclaration *) const override;
	[[gnu::pure]]
	bool signatureEquals(const MethodDeclaration *other) const;
	[[gnu::pure]]
	bool signatureEquals(const MethodInvocation *invocation) const;
	[[gnu::pure]]
	bool returnEquals(const MethodDeclaration *other) const;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) override;

	void addThisParam(TypeDeclaration *decl);
protected:
	std::unique_ptr<Type> returnType;
	std::string identifier;
	std::vector<std::unique_ptr<VariableDeclaration>> parameters;
	// nullable
	std::unique_ptr<Block> body;
private:
	MethodDeclaration(MethodHeader&& header, std::unique_ptr<Block> block);
};

} //namespace AST
