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
	explicit ConditionalStatement(const Parse::TIfThenElseStatement *ptNode);
	explicit ConditionalStatement(const Parse::TIfThenElseStatementNoShortIf *ptNode);
	explicit ConditionalStatement(const Parse::TForStatementNoShortIf *ptNode);
	explicit ConditionalStatement(const Parse::TForStatement *ptNode);
	std::string toCode() const override;

	enum class ConditionType {
		If,
		While,
		For,
		Max
	};

	ConditionType condType;
	// nullable
	std::unique_ptr<Statement> init;
	// nullable (empty for-loop condition)
	std::unique_ptr<Expression> condition;
	// nullable
	std::unique_ptr<Expression> increment;
	std::unique_ptr<Statement> body;
	// nullable
	std::unique_ptr<Statement> elseBody;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) override;
};

std::string operator+(std::string str, ConditionalStatement::ConditionType type);
std::string operator+=(std::string& str, ConditionalStatement::ConditionType type);
std::ostream& operator<<(std::ostream& os, ConditionalStatement::ConditionType type);

} //namespace AST
