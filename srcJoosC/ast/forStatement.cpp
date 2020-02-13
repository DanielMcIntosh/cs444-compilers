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
  : ConditionalStatement(ConditionalStatement::ConditionType::For),
    init(Statement::create(ptNode->forInit->v == Parse::TForInitV::ExpressionStatement
                           ? static_cast<Parse::Tree *>(ptNode->forInit->expressionStatement)
                           : static_cast<Parse::Tree *>(ptNode->forInit->localVariableDeclarationStatement))),
    increment(Statement::create(ptNode->forInit->localVariableDeclarationStatement))
{
}
ForStatement::ForStatement(const Parse::TForStatementNoShortIf *ptNode)
  : ConditionalStatement(ConditionalStatement::ConditionType::For),
    init(Statement::create(ptNode->forInit->v == Parse::TForInitV::ExpressionStatement
    ? static_cast<Parse::Tree *>(ptNode->forInit->expressionStatement)
    : static_cast<Parse::Tree *>(ptNode->forInit->localVariableDeclarationStatement))),
    increment(Statement::create(ptNode->forInit->localVariableDeclarationStatement))
{
}
std::string ForStatement::toCode() {
    return "for (" + init->toCode() + " " + condition->toCode() + "; " + increment->toCode() + ") " + body->toCode();
}

} //namespace AST
