#pragma once

#include "ast/type.h"
#include "ast/expression.h"
#include <memory>

namespace AST
{

class ArrayCreationExpression: public Expression
{
public:
	static std::unique_ptr<ArrayCreationExpression> create(const Parse::Tree *ptNode);
	ArrayCreationExpression(const Parse::TArrayCreationExpression *ptNode);

	// IMPORTANT: during construction, we have to change type->isArray to true
	std::unique_ptr<Type> type;
	std::unique_ptr<Expression> size;

	std::string toCode() override { return "[ArrayCreationExpression]"; }
};

} //namespace AST
