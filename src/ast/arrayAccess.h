#pragma once

#include "ast/expression.h"
#include <memory>

namespace AST
{

class ArrayAccess: public Expression
{
public:
	ArrayAccess(std::vector<Parser::ASTToken>& children);

	std::shared_ptr<Expression> array;
	std::shared_ptr<Expression> index;
};

} //namespace AST
