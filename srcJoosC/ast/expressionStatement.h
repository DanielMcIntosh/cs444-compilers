#pragma once

#include "ast/statement.h"
#include "ast/expression.h"
#include <memory>

namespace AST
{

class ExpressionStatement: public Statement
{
public:
	static std::unique_ptr<ExpressionStatement> create(const Parse::Tree *ptNode);
	ExpressionStatement(const Parse::TExpressionStatement *ptNode);

	// nullable
	std::unique_ptr<Expression> expression;

	std::string toCode() override { return "[ExpressionStatement]"; }
};

} //namespace AST
