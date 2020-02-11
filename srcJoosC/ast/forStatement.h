#pragma once

#include "ast/conditionalStatement.h"
#include "ast/statement.h"
#include <memory>

namespace AST
{

class ForStatement: public ConditionalStatement
{
public:
	static std::unique_ptr<ForStatement> create(const Parse::Tree *ptNode);
	ForStatement(const Parse::TForStatementNoShortIf *ptNode);
	ForStatement(const Parse::TForStatement *ptNode);

	std::unique_ptr<Expression> init;
	std::unique_ptr<Expression> increment;

	std::string toCode() override { return "[ForStatement]"; }
};

} //namespace AST
