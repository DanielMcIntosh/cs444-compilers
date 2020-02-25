#pragma once

#include "ast/statement.h"
#include <memory>
#include <map>

namespace AST
{

class Expression;

//////////////////////////////////////////////////////////////////////////////
//
// ConditionalStatement
//
//////////////////////////////////////////////////////////////////////////////

class ConditionalStatement: public Statement
{
public:
	static std::unique_ptr<ConditionalStatement> create(const Parse::Tree *ptNode);
	explicit ConditionalStatement(const Parse::TIfThenStatement *ptNode);
	explicit ConditionalStatement(const Parse::TWhileStatement *ptNode);
	explicit ConditionalStatement(const Parse::TWhileStatementNoShortIf *ptNode);
	std::string toCode() const override;

	enum class ConditionType {
		If,
		While,
		For,
		Max
	};

	ConditionType condType;
	// nullable (empty for-loop condition)
	std::unique_ptr<Expression> condition;
	std::unique_ptr<Statement> body;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) override;
protected:
	ConditionalStatement(ConditionType type, std::unique_ptr<Expression> cond, std::unique_ptr<Statement> statement);
};

std::string operator+(std::string str, ConditionalStatement::ConditionType type);
std::string operator+=(std::string& str, ConditionalStatement::ConditionType type);
std::ostream& operator<<(std::ostream& os, ConditionalStatement::ConditionType type);

//////////////////////////////////////////////////////////////////////////////
//
// IfThenElseStatement
//
//////////////////////////////////////////////////////////////////////////////
  
class IfThenElseStatement: public ConditionalStatement
{
public:
	static std::unique_ptr<IfThenElseStatement> create(const Parse::Tree *ptNode);
	explicit IfThenElseStatement(const Parse::TIfThenElseStatement *ptNode);
	explicit IfThenElseStatement(const Parse::TIfThenElseStatementNoShortIf *ptNode);
	std::string toCode() const override;

	std::unique_ptr<Statement> elseBody;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) override;
};

//////////////////////////////////////////////////////////////////////////////
//
// ForStatement
//
//////////////////////////////////////////////////////////////////////////////
  
class ForStatement: public ConditionalStatement
{
public:
	static std::unique_ptr<ForStatement> create(const Parse::Tree *ptNode);
	explicit ForStatement(const Parse::TForStatementNoShortIf *ptNode);
	explicit ForStatement(const Parse::TForStatement *ptNode);
	std::string toCode() const override;

	// nullable
	std::unique_ptr<Statement> init;
	// nullable
	std::unique_ptr<Expression> increment;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) override;
};

} //namespace AST
