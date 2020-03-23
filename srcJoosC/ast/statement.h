#pragma once

#include "ast/node.h"
#include "semantic/scope.h"

namespace Semantic
{
	struct SemanticDB;
	enum class SemanticErrorType;
	class Scope;
}

namespace CodeGen {
  class SContext;
}

namespace AST
{

class TypeDeclaration;
class VariableDeclaration;
class Expression;
class StaticAnalysisCtx;

//////////////////////////////////////////////////////////////////////////////
//
// Statement
//
//////////////////////////////////////////////////////////////////////////////

class Statement: public Node
{
public:
	static std::unique_ptr<Statement> create(const Parse::Tree *ptNode);

	virtual Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) = 0;
	virtual Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) = 0;

	// a4

	virtual void staticAnalysis(StaticAnalysisCtx *ctx);

	// a5
	virtual void codeGenerate(CodeGen::SContext* ctx) = 0;
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

	// a4

	void staticAnalysis(StaticAnalysisCtx *ctx) override;

	std::vector<std::unique_ptr<Statement>> statements;

	// a5
	Semantic::Scope theScope;

	void codeGenerate(CodeGen::SContext *ctx) override;
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

	// nullable
	std::unique_ptr<Expression> expression;

	void codeGenerate(CodeGen::SContext *ctx) override;
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

	// a4

	void staticAnalysis(StaticAnalysisCtx *ctx) override;

  // a5
  void codeGenerate(CodeGen::SContext *ctx) override;  

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

  // a5
  void codeGenerate(CodeGen::SContext *ctx) override;
protected:
	std::unique_ptr<VariableDeclaration> declaration;
};

//////////////////////////////////////////////////////////////////////////////
//
// ConditionalStatements are in their own file
//
//////////////////////////////////////////////////////////////////////////////

} //namespace AST
