#pragma once

#include "ast/type.h"
#include "ast/expression.h"
#include <vector>
#include <memory>

namespace AST
{

class ClassInstanceCreationExpression: public Expression
{
public:
	static std::unique_ptr<ClassInstanceCreationExpression> create(const Parse::Tree *ptNode);
	ClassInstanceCreationExpression(const Parse::TClassInstanceCreationExpression *ptNode);

	std::unique_ptr<Type> type;
	std::vector<std::unique_ptr<Expression>> args;

	std::string toCode() override { return "[ClassInstanceCreationExpression]"; }
};

} //namespace AST
