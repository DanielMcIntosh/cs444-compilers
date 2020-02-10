#include "ast/parenthesizedExpression.h"
#include "ast/expression.h"
#include "parse/parseTree.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<ParenthesizedExpression> ParenthesizedExpression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (ptNode->oneNt)
	{
		return ParenthesizedExpression::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::ParenthesizedExpression:
		return std::make_unique<ParenthesizedExpression>(static_cast<const Parse::TParenthesizedExpression*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for ParenthesizedExpression: " + std::to_string((int)ptNode->type));
	}
}
ParenthesizedExpression::ParenthesizedExpression(const Parse::TParenthesizedExpression *ptNode)
{
}

} //namespace AST
