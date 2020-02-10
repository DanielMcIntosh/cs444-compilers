#pragma once

#include "ast/statement.h"
#include "ast/expression.h"
#include <memory>
#include <map>


namespace AST
{

class ConditionalStatement: public Statement
{
public:
	static std::unique_ptr<ConditionalStatement> create(const Parse::Tree *ptNode);
	ConditionalStatement(const Parse::TIfThenStatement *ptNode);
	ConditionalStatement(const Parse::TWhileStatement *ptNode);
	ConditionalStatement(const Parse::TWhileStatementNoShortIf *ptNode);

	enum class ConditionType {
		If,
		While,
		For,
	};

	ConditionType condType;
	// nullable (empty for-loop condition)
	std::shared_ptr<Expression> condition;
	std::shared_ptr<Statement> body;
protected:
	ConditionalStatement(ConditionType cond);

	std::string toCode() override { return "[ConditionalStatement]"; }
};

} //namespace AST
