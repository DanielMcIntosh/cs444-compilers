#pragma once

#include "ast/memberDeclaration.h"
#include "semantic/scope.h"
#include <memory>

namespace AST
{

class Block;
class VariableDeclaration;
class MethodDeclarator;
class ClassInstanceCreationExpression;

class ConstructorDeclaration: public MemberDeclaration
{
public:
	static std::unique_ptr<ConstructorDeclaration> create(const Parse::Tree *ptNode);
	explicit ConstructorDeclaration(const Parse::TConstructorDeclaration *ptNode);
	std::string toCode() const override;

	using MemberDeclaration::equals;
	virtual bool equals(const ConstructorDeclaration *) const override;
	// TODO: turn into template function to remove duplication in methodDeclaration
	bool signatureEquals(const ConstructorDeclaration *) const;
	bool signatureEquals(const ClassInstanceCreationExpression *) const;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic) override;
	Semantic::SemanticErrorType resolveExprs() override;

	void addThisParam();

	// a4

	void staticAnalysis(StaticAnalysisCtx *ctx) override;

	std::string identifier;
	std::vector<std::unique_ptr<VariableDeclaration>> parameters;
	std::unique_ptr<Block> body;

	// a5

	Semantic::Scope theScope;
private:
	// not convinced this is the best way of dealing with needing 2 members from declarator
	ConstructorDeclaration(std::vector<std::unique_ptr<Modifier>> mods, MethodDeclarator &&declarator, std::unique_ptr<Block> block);
};

} //namespace AST
