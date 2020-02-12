#include "ast/expressionStatement.h"
#include "ast/statement.h"
#include "parse/parseTree.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<ExpressionStatement> ExpressionStatement::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (ptNode->oneNt)
	{
		return ExpressionStatement::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::ExpressionStatement:
		return std::make_unique<ExpressionStatement>(static_cast<const Parse::TExpressionStatement*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for ExpressionStatement: " + std::to_string((int)ptNode->type));
	}
}
ExpressionStatement::ExpressionStatement(const Parse::TExpressionStatement *ptNode)
{
}

} //namespace AST