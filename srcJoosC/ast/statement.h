#pragma once

#include "ast/node.h"

namespace Semantic
{
	struct SemanticDB;
	enum class SemanticErrorType;
	class Scope;
}

namespace AST
{

class TypeDeclaration;
class VariableDeclaration;
class Expression;

//////////////////////////////////////////////////////////////////////////////
//
// Statement
//
//////////////////////////////////////////////////////////////////////////////

class Statement: public Node
{
public:
	static std::unique_ptr<Statement> create(const Parse::Tree *ptNode);

	virtual Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass);
	virtual Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) = 0;
};

//////////////////////////////////////////////////////////////////////////////
//
// Block
//
//////////////////////////////////////////////////////////////////////////////

class Block: public Statement
{
public:
	static std::unique_ptr<Block> create(const Parse::Tree *ptNode);
	explicit Block(const Parse::TBlock *ptNode);
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) override;
protected:
	std::vector<std::unique_ptr<Statement>> statements;
};

//////////////////////////////////////////////////////////////////////////////
//
// ExpressionStatement
//
//////////////////////////////////////////////////////////////////////////////

class ExpressionStatement: public Statement
{
public:
	static std::unique_ptr<ExpressionStatement> create(const Parse::Tree *ptNode);
	explicit ExpressionStatement(const Parse::TExpressionStatement *ptNode);
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) override;
protected:
	// nullable
	std::unique_ptr<Expression> expression;
};

//////////////////////////////////////////////////////////////////////////////
//
// ReturnStatement
//
//////////////////////////////////////////////////////////////////////////////

class ReturnStatement: public Statement
{
public:
	static std::unique_ptr<ReturnStatement> create(const Parse::Tree *ptNode);
	explicit ReturnStatement(const Parse::TReturnStatement *ptNode);
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) override;
protected:
	// nullable
	std::unique_ptr<Expression> returnValue;
};

//////////////////////////////////////////////////////////////////////////////
//
// LocalVariableDeclarationStatement
//
//////////////////////////////////////////////////////////////////////////////

class LocalVariableDeclarationStatement: public Statement
{
public:
	static std::unique_ptr<LocalVariableDeclarationStatement> create(const Parse::Tree *ptNode);
	explicit LocalVariableDeclarationStatement(const Parse::TLocalVariableDeclarationStatement *ptNode);
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) override;
protected:
	std::unique_ptr<VariableDeclaration> declaration;
};

//////////////////////////////////////////////////////////////////////////////
//
// ConditionalStatements are in their own file
//
//////////////////////////////////////////////////////////////////////////////

} //namespace AST
