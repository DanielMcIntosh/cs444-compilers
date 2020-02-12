#include "ast/castExpression.h"
#include "ast/expression.h"
#include "ast/unaryExpression.h"
#include "ast/type.h"
#include "parse/parseTree.h"
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
		throw std::runtime_error("inapropriate PT type for CastExpression: " + std::to_string((int)ptNode->type));
	}
}
CastExpression::CastExpression(const Parse::TCastExpression *ptNode)
{
	/*
	type = std::dynamic_pointer_cast<Type>(children[cur++].astNode);
	if (children[cur].lexeme == "[")
	{
		type->isArray = true;
		++cur; // open bracket
		++cur; // close bracket
	}
	++cur; // close paren
	rhs = std::dynamic_pointer_cast<UnaryExpression>(children[cur++].astNode);
	*/
}

} //namespace AST
