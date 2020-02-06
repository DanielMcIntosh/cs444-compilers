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
	ClassInstanceCreationExpression(std::vector<Parser::ASTToken>& children);

	std::shared_ptr<Type> type;
	std::vector<std::shared_ptr<Expression>> args;
};

} //namespace AST
