#include "ast/unaryExpression.h"
#include "ast/expression.h"
#include "parse/parseTree.h"

#include "utility.h"

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
	// NOTE: removed because otherwise losing operator information
	switch(ptNode->type) {
	case Parse::NonTerminalType::UnaryExpression:
		return std::make_unique<UnaryExpression>(static_cast<const Parse::TUnaryExpression*>(ptNode));
	case Parse::NonTerminalType::UnaryExpressionNotPlusMinus:
		return std::make_unique<UnaryExpression>(static_cast<const Parse::TUnaryExpressionNotPlusMinus*>(ptNode));
	default:
		throw std::runtime_error("inappropriate PT type for UnaryExpression: " + std::to_string((int)ptNode->type));
	}
}

UnaryExpression::UnaryExpression(const Parse::TUnaryExpression *ptNode)
{
	switch (ptNode->v) {
		case Parse::TUnaryExpressionV::MinusUnaryExpression:
			op = "-";
			expr = std::move(Expression::create(ptNode->unaryExpression));
			break;
		case Parse::TUnaryExpressionV::UnaryExpressionNotPlusMinus:
			op = "+";
			expr = std::move(Expression::create((ptNode->unaryExpressionNotPlusMinus)));
			break;
		default:
			ASSERT(false);
	}
}

UnaryExpression::UnaryExpression(const Parse::TUnaryExpressionNotPlusMinus *ptNode):
expr(Expression::create(ptNode->children[0]))
{
	switch (ptNode->v) {
		case Parse::TUnaryExpressionNotPlusMinusV::BangUnaryExpression:
			op = "!";
			break;
		case Parse::TUnaryExpressionNotPlusMinusV::Name:
		case Parse::TUnaryExpressionNotPlusMinusV::Primary:
		case Parse::TUnaryExpressionNotPlusMinusV::CastExpression:
			op = "+";
			break;
		default:
			ASSERT(false);
	}
}

} //namespace AST
