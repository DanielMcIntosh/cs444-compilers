#include "ast/castExpression.h"
#include "ast/expression.h"
#include "ast/unaryExpression.h"
#include "ast/type.h"
#include "parse/parseTree.h"
#include "utility.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<CastExpression> CastExpression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::CastExpression:
		return std::make_unique<CastExpression>(static_cast<const Parse::TCastExpression*>(ptNode));
	default:
		throw std::runtime_error("inappropriate PT type for CastExpression: " + std::to_string((int)ptNode->type));
	}
}
CastExpression::CastExpression(const Parse::TCastExpression *ptNode)
{
    switch (ptNode->v) {
        case Parse::TCastExpressionV::LParPrimitiveTypeRParUnaryExpression:
            type = Type::create(ptNode->primitiveType);
            rhs = Expression::create(ptNode->unaryExpression);
            break;
        case Parse::TCastExpressionV::LParPrimitiveTypeLSBrRSBrRParUnaryExpression:
            type = Type::create(ptNode->primitiveType);
            type->isArray = true;
            rhs = Expression::create(ptNode->unaryExpression);
            break;
        case Parse::TCastExpressionV::LParExpressionRParUnaryExpressionNotPlusMinus:
            type = Type::create(ptNode->expression->assignmentExpression->conditionalOrExpression->conditionalAndExpression
                    ->inclusiveOrExpression->andExpression->equalityExpression->relationalExpression->additiveExpression
                    ->multiplicativeExpression->unaryExpression->unaryExpressionNotPlusMinus->name);
            rhs = Expression::create(ptNode->unaryExpressionNotPlusMinus);
            break;
        case Parse::TCastExpressionV::LParNameLSBrRSBrRParUnaryExpressionNotPlusMinus:
            type = Type::create(ptNode->name);
            type->isArray = true;
            rhs = Expression::create(ptNode->unaryExpressionNotPlusMinus);
            break;
        default:
            ASSERT(false);
    }
}

std::string CastExpression::toCode() {
    return "(" + type->toCode() + ")" + rhs->toCode();
}

} //namespace AST
