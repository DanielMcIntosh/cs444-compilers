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
	ConditionalStatement(std::vector<Parser::ASTToken>& children);

	enum class ConditionType {
		If,
		While,
		For,
	};
	static const std::map<std::string, ConditionType> condTypeLookup;

	ConditionType condType;
	// nullable (empty for-loop condition)
	std::shared_ptr<Expression> condition;
	std::shared_ptr<Statement> body;
protected:
	ConditionalStatement();
};

} //namespace AST
