#include "ast/binaryExpression.h"
#include "ast/node.h"
#include "ast/expression.h"
#include "parse/parseTree.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<BinaryExpression> BinaryExpression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (ptNode->oneNt)
	{
		return BinaryExpression::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::AdditiveExpression:
		return std::make_unique<BinaryExpression>(static_cast<const Parse::TAdditiveExpression*>(ptNode));
	case Parse::NonTerminalType::AndExpression:
		return std::make_unique<BinaryExpression>(static_cast<const Parse::TAndExpression*>(ptNode));
	case Parse::NonTerminalType::ConditionalAndExpression:
		return std::make_unique<BinaryExpression>(static_cast<const Parse::TConditionalAndExpression*>(ptNode));
	case Parse::NonTerminalType::ConditionalOrExpression:
		return std::make_unique<BinaryExpression>(static_cast<const Parse::TConditionalOrExpression*>(ptNode));
	case Parse::NonTerminalType::EqualityExpression:
		return std::make_unique<BinaryExpression>(static_cast<const Parse::TEqualityExpression*>(ptNode));
	case Parse::NonTerminalType::InclusiveOrExpression:
		return std::make_unique<BinaryExpression>(static_cast<const Parse::TInclusiveOrExpression*>(ptNode));
	case Parse::NonTerminalType::MultiplicativeExpression:
		return std::make_unique<BinaryExpression>(static_cast<const Parse::TMultiplicativeExpression*>(ptNode));
	case Parse::NonTerminalType::RelationalExpression:
		return std::make_unique<BinaryExpression>(static_cast<const Parse::TRelationalExpression*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for BinaryExpression: " + std::to_string((int)ptNode->type));
	}
}
BinaryExpression::BinaryExpression(const Parse::TAdditiveExpression *ptNode)
{
}
BinaryExpression::BinaryExpression(const Parse::TAndExpression *ptNode)
{
}
BinaryExpression::BinaryExpression(const Parse::TConditionalAndExpression *ptNode)
{
}
BinaryExpression::BinaryExpression(const Parse::TConditionalOrExpression *ptNode)
{
}
BinaryExpression::BinaryExpression(const Parse::TEqualityExpression *ptNode)
{
}
BinaryExpression::BinaryExpression(const Parse::TInclusiveOrExpression *ptNode)
{
}
BinaryExpression::BinaryExpression(const Parse::TMultiplicativeExpression *ptNode)
{
}
BinaryExpression::BinaryExpression(const Parse::TRelationalExpression *ptNode)
{
}

} //namespace AST
