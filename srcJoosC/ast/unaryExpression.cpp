#include "ast/unaryExpression.h"
#include "ast/expression.h"
#include "parse/parseTree.h"
#include <memory>
#include <string>

namespace AST
{

// static
std::unique_ptr<UnaryExpression> UnaryExpression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (ptNode->oneNt)
	{
		return UnaryExpression::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::UnaryExpression:
		return std::make_unique<UnaryExpression>(static_cast<const Parse::TUnaryExpression*>(ptNode));
	case Parse::NonTerminalType::UnaryExpressionNotPlusMinus:
		return std::make_unique<UnaryExpression>(static_cast<const Parse::TUnaryExpressionNotPlusMinus*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for UnaryExpression: " + std::to_string((int)ptNode->type));
	}
}
UnaryExpression::UnaryExpression(const Parse::TUnaryExpression *ptNode)
{
}
UnaryExpression::UnaryExpression(const Parse::TUnaryExpressionNotPlusMinus *ptNode)
{
}

} //namespace AST
