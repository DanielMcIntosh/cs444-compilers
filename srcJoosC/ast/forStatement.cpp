#include "ast/forStatement.h"
#include "ast/conditionalStatement.h"
#include "ast/statement.h"
#include "parse/parseTree.h"
#include <memory>

namespace AST
{


// static
std::unique_ptr<ForStatement> ForStatement::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::ForStatement:
		return std::make_unique<ForStatement>(static_cast<const Parse::TForStatement*>(ptNode));
	case Parse::NonTerminalType::ForStatementNoShortIf:
		return std::make_unique<ForStatement>(static_cast<const Parse::TForStatementNoShortIf*>(ptNode));
	default:
		throw std::runtime_error("inappropriate PT type for ForStatement: " + std::to_string((int)ptNode->type));
	}
}
ForStatement::ForStatement(const Parse::TForStatement *ptNode)
  : ConditionalStatement(ConditionalStatement::ConditionType::For, Expression::create(ptNode->expression), Statement::create(ptNode->statement)),
    init(Statement::create(ptNode->forInit)),
    increment(Expression::create(ptNode->forUpdate))
{
}
ForStatement::ForStatement(const Parse::TForStatementNoShortIf *ptNode)
  : ConditionalStatement(ConditionalStatement::ConditionType::For, Expression::create(ptNode->expression), Statement::create(ptNode->statementNoShortIf)),
    init(Statement::create(ptNode->forInit)),
    increment(Expression::create(ptNode->forUpdate))
{
}
std::string ForStatement::toCode() {
    return "for (" + init->toCode() + " " + condition->toCode() + "; " + increment->toCode() + ")\n"
    		+ body->toCode();
}

} //namespace AST
