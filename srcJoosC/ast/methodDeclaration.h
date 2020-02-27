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

class MethodDeclaration: public MemberDeclaration
{
public:
	EXPORT static std::unique_ptr<MethodDeclaration> create(const Parse::Tree *ptNode);
	EXPORT explicit MethodDeclaration(const Parse::TMethodDeclaration *ptNode);
	EXPORT explicit MethodDeclaration(const Parse::TAbstractMethodDeclaration *ptNode);
	std::string toCode() const override;

	using MemberDeclaration::equals;
	virtual bool equals(MethodDeclaration *) override;
	bool signatureEquals(MethodDeclaration *other);
	bool returnEquals(MethodDeclaration *other);

	virtual int getTypeId() override { return 1; }

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
