#pragma once

#include "ast/expression.h"

namespace AST
{

class Literal: public Expression
{
public:
	static std::unique_ptr<Literal> create(const Parse::Tree *ptNode);
	Literal(const Parse::TLiteral *ptNode);

	enum class Value {
		IntegerLiteral,
		BooleanLiteral,
		CharacterLiteral,
		StringLiteral,
		NullLiteral,
	};
	Value literalType;

	std::string toCode() override { return "[Literal]"; }
};

} //namespace AST
