#pragma once

#include "ast/statement.h"
#include "ast/expression.h"
#include <memory>

namespace AST
{

class ReturnStatement: public Statement
{
public:
	static std::unique_ptr<ReturnStatement> create(const Parse::Tree *ptNode);
	ReturnStatement(const Parse::TReturnStatement *ptNode);

	// nullable
	std::shared_ptr<Expression> returnValue;

	std::string toCode() override { return "[ReturnStatement]"; }
};

} //namespace AST
