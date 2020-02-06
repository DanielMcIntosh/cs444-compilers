#pragma once

#include "ast/expression.h"

namespace AST
{

class Literal: public Expression
{
public:
	Literal(std::vector<Parser::ASTToken>& children);

	enum class Value {
		IntegerLiteral,
		BooleanLiteral,
		CharacterLiteral,
		StringLiteral,
		NullLiteral,
	};
	Value literalType;
};

} //namespace AST
