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
	explicit ConditionalStatement(const Parse::TIfThenStatement *ptNode);
	explicit ConditionalStatement(const Parse::TWhileStatement *ptNode);
	explicit ConditionalStatement(const Parse::TWhileStatementNoShortIf *ptNode);

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

	std::string toCode() override;
protected:
	ConditionalStatement(ConditionType type, std::unique_ptr<Expression> cond, std::unique_ptr<Statement> statement);
};

std::string operator+(std::string str, ConditionalStatement::ConditionType type);
std::string operator+=(std::string& str, ConditionalStatement::ConditionType type);
std::ostream& operator<<(std::ostream& os, ConditionalStatement::ConditionType type);

} //namespace AST
