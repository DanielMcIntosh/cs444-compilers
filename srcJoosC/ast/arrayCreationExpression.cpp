#include "ast/arrayCreationExpression.h"
#include "ast/expression.h"
#include "ast/type.h"
#include "parse/parseTree.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<ArrayCreationExpression> ArrayCreationExpression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::ArrayCreationExpression:
		return std::make_unique<ArrayCreationExpression>(static_cast<const Parse::TArrayCreationExpression*>(ptNode));
	default:
		throw std::runtime_error("inappropriate PT type for ArrayCreationExpression: " + std::to_string((int)ptNode->type));
	}
}
ArrayCreationExpression::ArrayCreationExpression(const Parse::TArrayCreationExpression *ptNode)
  : type(Type::create((ptNode->v == Parse::TArrayCreationExpressionV::NewPrimitiveTypeLSBrExpressionRSBr)
                         ? (const Parse::Tree *)ptNode->primitiveType
                         : (const Parse::Tree *)ptNode->classOrInterfaceType)),
	size(Expression::create(ptNode->expression))
{
	type->isArray = true;
}

std::string ArrayCreationExpression::toCode()
{
	return "new " + type->toCode() + '[' + size->toCode() + ']';
}

} //namespace AST
