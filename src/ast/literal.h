#pragma once

#include "ast/primary.h"

namespace AST
{

class Literal: public Primary
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
