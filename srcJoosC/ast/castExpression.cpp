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
		FAILED("inappropriate PT type for CastExpression: " + std::to_string((int)ptNode->type));
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
            type = Type::create(ptNode->expression);
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

std::string CastExpression::toCode() const {
    return "(" + type->toCode() + ")" + rhs->toCode();
}

Semantic::SemanticErrorType CastExpression::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
    return type->resolve(semantic, enclosingClass);
}

} //namespace AST
