#include "ast/ifThenElseStatement.h"
#include "ast/conditionalStatement.h"
#include "ast/statement.h"
#include "parse/parseTree.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<IfThenElseStatement> IfThenElseStatement::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::IfThenElseStatement:
		return std::make_unique<IfThenElseStatement>(static_cast<const Parse::TIfThenElseStatement*>(ptNode));
	case Parse::NonTerminalType::IfThenElseStatementNoShortIf:
		return std::make_unique<IfThenElseStatement>(static_cast<const Parse::TIfThenElseStatementNoShortIf*>(ptNode));
	default:
		FAILED("inappropriate PT type for IfThenElseStatement: " + std::to_string((int)ptNode->type));
	}
}
IfThenElseStatement::IfThenElseStatement(const Parse::TIfThenElseStatement *ptNode)
  : ConditionalStatement(ConditionalStatement::ConditionType::If, Expression::create(ptNode->expression), Statement::create(ptNode->statementNoShortIf)),
	elseBody(Statement::create(ptNode->statement))
{
}
IfThenElseStatement::IfThenElseStatement(const Parse::TIfThenElseStatementNoShortIf *ptNode)
  : ConditionalStatement(ConditionalStatement::ConditionType::If, Expression::create(ptNode->expression), Statement::create(ptNode->statementNoShortIf)),
	elseBody(Statement::create(ptNode->statementNoShortIf2))
{
}

std::string IfThenElseStatement::toCode()
{
	std::string str = "if (" + condition->toCode() + ")\n";
	str += body->toCode();
	str += "\nelse\n";
	str += elseBody->toCode();
	return str;
}

} //namespace AST
