#pragma once

#include "ast/conditionalStatement.h"
#include "ast/statement.h"
#include <memory>

namespace AST
{

class IfThenElseStatement: public ConditionalStatement
{
public:
	static std::unique_ptr<IfThenElseStatement> create(const Parse::Tree *ptNode);
	IfThenElseStatement(const Parse::TIfThenElseStatement *ptNode);
	IfThenElseStatement(const Parse::TIfThenElseStatementNoShortIf *ptNode);

	std::unique_ptr<Statement> elseBody;

	std::string toCode() override { return "[IfThenElseStatement]"; }
};

} //namespace AST
