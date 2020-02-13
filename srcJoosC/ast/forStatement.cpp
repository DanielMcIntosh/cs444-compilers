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
  : ConditionalStatement(ConditionalStatement::ConditionType::For)
{
	/*
	if (!Parser::isTerminal(children[cur].sym))
	{
		init = std::dynamic_pointer_cast<Expression>(children[cur++].astNode);
	}
	++cur; // semicolon
	if (!Parser::isTerminal(children[cur].sym))
	{
		condition = std::dynamic_pointer_cast<Expression>(children[cur++].astNode);
	}
	++cur; // semicolon
	if (!Parser::isTerminal(children[cur].sym))
	{
		increment = std::dynamic_pointer_cast<Expression>(children[cur++].astNode);
	}
	++cur; //close paren
	body = std::dynamic_pointer_cast<Statement>(children[cur++].astNode);
	*/
}
ForStatement::ForStatement(const Parse::TForStatementNoShortIf *ptNode)
  : ConditionalStatement(ConditionalStatement::ConditionType::For)
{
}

} //namespace AST
