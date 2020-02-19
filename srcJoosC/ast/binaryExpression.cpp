#include "ast/binaryExpression.h"
#include "ast/node.h"
#include "ast/expression.h"
#include "parse/parseTree.h"
#include <memory>
#include <ostream>

namespace AST
{

// static
std::unique_ptr<BinaryExpression> BinaryExpression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (isSingleton(ptNode))
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
		FAILED("inappropriate PT type for BinaryExpression: " + std::to_string((int)ptNode->type));
	}
}

static_assert(BinaryExpression::Variant::Sub == BinaryExpression::Variant::Add + ((int)Parse::TAdditiveExpressionV::AdditiveExpressionMinusMultiplicativeExpression - (int)Parse::TAdditiveExpressionV::AdditiveExpressionPlusMultiplicativeExpression));
BinaryExpression::BinaryExpression(const Parse::TAdditiveExpression *ptNode)
  : op(Variant::Add + ((int)ptNode->v - (int)Parse::TAdditiveExpressionV::AdditiveExpressionPlusMultiplicativeExpression)),
	lhs(Expression::create(ptNode->additiveExpression)),
	rhs(Expression::create(ptNode->multiplicativeExpression))
{
}
static_assert(BinaryExpression::Variant::Div == BinaryExpression::Variant::Mult + ((int)Parse::TMultiplicativeExpressionV::MultiplicativeExpressionRSlashUnaryExpression - (int)Parse::TMultiplicativeExpressionV::MultiplicativeExpressionStarUnaryExpression));
static_assert(BinaryExpression::Variant::Mod == BinaryExpression::Variant::Mult + ((int)Parse::TMultiplicativeExpressionV::MultiplicativeExpressionPercUnaryExpression - (int)Parse::TMultiplicativeExpressionV::MultiplicativeExpressionStarUnaryExpression));
BinaryExpression::BinaryExpression(const Parse::TMultiplicativeExpression *ptNode)
  : op(Variant::Mult + ((int)ptNode->v - (int)Parse::TMultiplicativeExpressionV::MultiplicativeExpressionStarUnaryExpression)),
	lhs(Expression::create(ptNode->multiplicativeExpression)),
	rhs(Expression::create(ptNode->unaryExpression))
{
}
static_assert(BinaryExpression::Variant::Gt == BinaryExpression::Variant::Lt + ((int)Parse::TRelationalExpressionV::RelationalExpressionGrAdditiveExpression - (int)Parse::TRelationalExpressionV::RelationalExpressionLeAdditiveExpression));
static_assert(BinaryExpression::Variant::LtEq == BinaryExpression::Variant::Lt + ((int)Parse::TRelationalExpressionV::RelationalExpressionLeEqAdditiveExpression - (int)Parse::TRelationalExpressionV::RelationalExpressionLeAdditiveExpression));
static_assert(BinaryExpression::Variant::GtEq == BinaryExpression::Variant::Lt + ((int)Parse::TRelationalExpressionV::RelationalExpressionGrEqAdditiveExpression - (int)Parse::TRelationalExpressionV::RelationalExpressionLeAdditiveExpression));
static_assert(BinaryExpression::Variant::InstanceOf == BinaryExpression::Variant::Lt + ((int)Parse::TRelationalExpressionV::RelationalExpressioninstanceofReferenceType - (int)Parse::TRelationalExpressionV::RelationalExpressionLeAdditiveExpression));
BinaryExpression::BinaryExpression(const Parse::TRelationalExpression *ptNode)
  : op(Variant::Lt + ((int)ptNode->v - (int)Parse::TRelationalExpressionV::RelationalExpressionLeAdditiveExpression)),
	lhs(Expression::create(ptNode->relationalExpression)),
	// will initialize to nullptr for instanceof
	rhs(Expression::create(ptNode->additiveExpression))
{
	if (op == Variant::InstanceOf)
	{
		rhs = Type::create(ptNode->referenceType);
	}
}
static_assert(BinaryExpression::Variant::NEq == BinaryExpression::Variant::Eq + ((int)Parse::TEqualityExpressionV::EqualityExpressionBangEqRelationalExpression - (int)Parse::TEqualityExpressionV::EqualityExpressionEqEqRelationalExpression));
BinaryExpression::BinaryExpression(const Parse::TEqualityExpression *ptNode)
  : op(Variant::Eq + ((int)ptNode->v - (int)Parse::TEqualityExpressionV::EqualityExpressionEqEqRelationalExpression)),
	lhs(Expression::create(ptNode->equalityExpression)),
	rhs(Expression::create(ptNode->relationalExpression))
{
}
BinaryExpression::BinaryExpression(const Parse::TAndExpression *ptNode)
  : op(Variant::EagerAnd),
	lhs(Expression::create(ptNode->andExpression)),
	rhs(Expression::create(ptNode->equalityExpression))
{
}
BinaryExpression::BinaryExpression(const Parse::TInclusiveOrExpression *ptNode)
  : op(Variant::EagerOr),
	lhs(Expression::create(ptNode->inclusiveOrExpression)),
	rhs(Expression::create(ptNode->andExpression))
{
}
BinaryExpression::BinaryExpression(const Parse::TConditionalAndExpression *ptNode)
  : op(Variant::LazyAnd),
	lhs(Expression::create(ptNode->conditionalAndExpression)),
	rhs(Expression::create(ptNode->inclusiveOrExpression))
{
}
BinaryExpression::BinaryExpression(const Parse::TConditionalOrExpression *ptNode)
  : op(Variant::LazyOr),
	lhs(Expression::create(ptNode->conditionalOrExpression)),
	rhs(Expression::create(ptNode->conditionalAndExpression))
{
}

std::string BinaryExpression::toCode()
{
	if (op == Variant::InstanceOf)
	{
		auto &rhsType = std::get<std::unique_ptr<Type>>(rhs);
		return "(" + lhs->toCode() + op + rhsType->toCode() + ")";
	}
	auto &rhsExpr = std::get<std::unique_ptr<Expression>>(rhs);
	return "(" + lhs->toCode() + op + rhsExpr->toCode() + ")";
}

std::string operator+=(std::string& str, BinaryExpression::Variant op)
{
    switch(op)
    {
		case BinaryExpression::Variant::Add:       	return str += "+";
		case BinaryExpression::Variant::Sub:       	return str += "-";
		case BinaryExpression::Variant::Mult:      	return str += "*";
		case BinaryExpression::Variant::Div:       	return str += "/";
		case BinaryExpression::Variant::Mod:       	return str += "%";
		case BinaryExpression::Variant::Lt:        	return str += "<";
		case BinaryExpression::Variant::Gt:        	return str += ">";
		case BinaryExpression::Variant::LtEq:      	return str += "<=";
		case BinaryExpression::Variant::GtEq:      	return str += ">=";
		case BinaryExpression::Variant::InstanceOf:	return str += "instanceof";
		case BinaryExpression::Variant::Eq:        	return str += "==";
		case BinaryExpression::Variant::NEq:       	return str += "!=";
		case BinaryExpression::Variant::EagerAnd:  	return str += "&";
		case BinaryExpression::Variant::EagerOr:   	return str += "|";
		case BinaryExpression::Variant::LazyAnd:   	return str += "&&";
		case BinaryExpression::Variant::LazyOr:    	return str += "||";
		case BinaryExpression::Variant::Max:		;// fallthrough
		// no default to trigger compiler warning on missing case
    }
    FAILED("String conversion on invalid opcode: " + std::to_string((int)op));
}
std::string operator+(std::string str, BinaryExpression::Variant op)
{
	return str += op;
}

std::ostream& operator<<(std::ostream& os, BinaryExpression::Variant op)
{
	if (op >= BinaryExpression::Variant::Max) {
		os.setstate(std::ios_base::failbit);
		return os;
	}
	return os << ("" + op);
}

} //namespace AST
