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
	virtual Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope);
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

	std::vector<std::unique_ptr<Statement>> statements;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) override;
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

	// nullable
	std::unique_ptr<Expression> expression;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
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

	// nullable
	std::unique_ptr<Expression> returnValue;

	std::string toCode() const override;
	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
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

	std::unique_ptr<VariableDeclaration> declaration;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) override;
};

//////////////////////////////////////////////////////////////////////////////
//
// ConditionalStatements are in their own file
//
//////////////////////////////////////////////////////////////////////////////

} //namespace AST
