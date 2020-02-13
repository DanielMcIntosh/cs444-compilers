#include "ast/conditionalStatement.h"
#include "ast/statement.h"
#include "ast/expression.h"
#include "parse/parseTree.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<ConditionalStatement> ConditionalStatement::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::IfThenStatement:
		return std::make_unique<ConditionalStatement>(static_cast<const Parse::TIfThenStatement*>(ptNode));
	case Parse::NonTerminalType::WhileStatement:
		return std::make_unique<ConditionalStatement>(static_cast<const Parse::TWhileStatement*>(ptNode));
	case Parse::NonTerminalType::WhileStatementNoShortIf:
		return std::make_unique<ConditionalStatement>(static_cast<const Parse::TWhileStatementNoShortIf*>(ptNode));
	default:
		throw std::runtime_error("inappropriate PT type for ConditionalStatement: " + std::to_string((int)ptNode->type));
	}
}
ConditionalStatement::ConditionalStatement(const Parse::TIfThenStatement *ptNode)
  : condType(ConditionalStatement::ConditionType::If)
{
	/*
	condition = std::dynamic_pointer_cast<Expression>(children[cur++].astNode);
	++cur; //close paren
	body = std::dynamic_pointer_cast<Statement>(children[cur++].astNode);
	*/
}
ConditionalStatement::ConditionalStatement(const Parse::TWhileStatement *ptNode)
  : condType(ConditionalStatement::ConditionType::While)
{
}
ConditionalStatement::ConditionalStatement(const Parse::TWhileStatementNoShortIf *ptNode)
  : condType(ConditionalStatement::ConditionType::While)
{
}

// protected
ConditionalStatement::ConditionalStatement(ConditionType cond)
  : condType(cond)
{
}

} //namespace AST
