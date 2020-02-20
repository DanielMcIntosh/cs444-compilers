#include "ast/unaryExpression.h"
#include "ast/expression.h"
#include "parse/parseTree.h"
#include <memory>
#include <string>
#include <ostream>

namespace AST
{

// static
std::unique_ptr<UnaryExpression> UnaryExpression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (isSingleton(ptNode))
	{
		return UnaryExpression::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::UnaryExpression:
		return std::make_unique<UnaryExpression>(static_cast<const Parse::TUnaryExpression*>(ptNode));
	case Parse::NonTerminalType::UnaryExpressionNotPlusMinus:
		return std::make_unique<UnaryExpression>(static_cast<const Parse::TUnaryExpressionNotPlusMinus*>(ptNode));
	default:
		FAILED("inappropriate PT type for UnaryExpression: " + std::to_string((int)ptNode->type));
	}
}

UnaryExpression::UnaryExpression(const Parse::TUnaryExpression *ptNode)
  : op(Variant::Minus),
	expr(Expression::create(ptNode->unaryExpression))
{
}

UnaryExpression::UnaryExpression(const Parse::TUnaryExpressionNotPlusMinus *ptNode)
  : op(Variant::Bang),
	expr(Expression::create(ptNode->unaryExpression))
{
}

std::string UnaryExpression::toCode() const
{
	return "" + op + expr->toCode();
}

std::string operator+=(std::string& str, UnaryExpression::Variant type)
{
    switch(type)
    {
		case UnaryExpression::Variant::Minus:	return str += "-";
		case UnaryExpression::Variant::Bang: 	return str += "!";
		case UnaryExpression::Variant::Max:		;// fallthrough
		// no default to trigger compiler warning on missing case
    }
    FAILED("String conversion on invalid operator type: " + std::to_string((int)type));
}
std::string operator+(std::string str, UnaryExpression::Variant type)
{
	return str += type;
}

std::ostream& operator<<(std::ostream& os, UnaryExpression::Variant type)
{
	if (type >= UnaryExpression::Variant::Max) {
		os.setstate(std::ios_base::failbit);
		return os;
	}
	return os << ("" + type);
}

} //namespace AST
