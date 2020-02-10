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
	if (ptNode->oneNt)
	{
		return ArrayCreationExpression::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::ArrayCreationExpression:
		return std::make_unique<ArrayCreationExpression>(static_cast<const Parse::TArrayCreationExpression*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for ArrayCreationExpression: " + std::to_string((int)ptNode->type));
	}
}
ArrayCreationExpression::ArrayCreationExpression(const Parse::TArrayCreationExpression *ptNode)
{
}

} //namespace AST
