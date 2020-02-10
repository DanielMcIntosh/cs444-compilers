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
	if (ptNode->oneNt)
	{
		return IfThenElseStatement::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::IfThenElseStatement:
		return std::make_unique<IfThenElseStatement>(static_cast<const Parse::TIfThenElseStatement*>(ptNode));
	case Parse::NonTerminalType::IfThenElseStatementNoShortIf:
		return std::make_unique<IfThenElseStatement>(static_cast<const Parse::TIfThenElseStatementNoShortIf*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for IfThenElseStatement: " + std::to_string((int)ptNode->type));
	}
}
IfThenElseStatement::IfThenElseStatement(const Parse::TIfThenElseStatement *ptNode)
  : ConditionalStatement(ConditionalStatement::ConditionType::If)
{
}
IfThenElseStatement::IfThenElseStatement(const Parse::TIfThenElseStatementNoShortIf *ptNode)
  : ConditionalStatement(ConditionalStatement::ConditionType::If)
{
}

} //namespace AST
