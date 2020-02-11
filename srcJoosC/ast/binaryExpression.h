#pragma once

#include "ast/node.h"
#include "ast/expression.h"
#include "ast/type.h"

#include <string>
#include <memory>
#include <variant>

namespace AST
{

class BinaryExpression: public Expression
{
public:
	static std::unique_ptr<BinaryExpression> create(const Parse::Tree *ptNode);

	BinaryExpression(const Parse::TAdditiveExpression *ptNode);
	BinaryExpression(const Parse::TAndExpression *ptNode);
	BinaryExpression(const Parse::TConditionalAndExpression *ptNode);
	BinaryExpression(const Parse::TConditionalOrExpression *ptNode);
	BinaryExpression(const Parse::TEqualityExpression *ptNode);
	BinaryExpression(const Parse::TInclusiveOrExpression *ptNode);
	BinaryExpression(const Parse::TMultiplicativeExpression *ptNode);
	BinaryExpression(const Parse::TRelationalExpression *ptNode);

	enum class Variant {
		Add,		// Accept Int, Return Int
		Sub,
		Mult,
		Div,
		Mod,
		Lt,			// Accept Int, Return Bool
		Gt,
		LtEq,
		GtEq,
		InstanceOf, // Accept Expr, Type, Return Bool
		Eq,			// Accpet Int/Bool, Return Bool
		NEq,
		EagerAnd,	// Accept Bool, Return Bool
		EagerOr,
		LazyAnd,
		LazyOr,
		Max
	} op;

	std::unique_ptr<Expression> lhs;
	// instanceof has a rhs that's a ReferenceType instead of an Expression
	std::variant<std::unique_ptr<Expression>, std::unique_ptr<Type>> rhs;

	std::string toCode() override;
};

std::string operator+(std::string str, BinaryExpression::Variant op);
std::string operator+=(std::string& str, BinaryExpression::Variant op);
std::ostream& operator<<(std::ostream& os, BinaryExpression::Variant op);
// not entirely sold on doing things this way. The alternative is a lot of casting in the .cpp file.
constexpr inline BinaryExpression::Variant operator+(BinaryExpression::Variant a, int b) { return (BinaryExpression::Variant)((int)a + b); }

} //namespace AST
