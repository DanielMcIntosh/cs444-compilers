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

	std::string op;
	std::shared_ptr<Expression> lhs;
	// instanceof has a rhs that's a ReferenceType instead of an Expression
	std::shared_ptr<std::variant<Expression, Type>> rhs;

	std::string toCode() override { return "[BinaryExpression]"; }
};

} //namespace AST
