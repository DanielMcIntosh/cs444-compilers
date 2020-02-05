#pragma once

#include "ast/primary.h"
#include "ast/type.h"
#include "ast/expression.h"
#include <memory>

namespace AST
{

class ArrayCreationExpression: public Primary
{
public:
	ArrayCreationExpression(std::vector<Parser::ASTToken>& children);

	// IMPORTANT: during construction, we have to change type->isArray to true
	std::shared_ptr<Type> type;
	std::shared_ptr<Expression> size;
};

} //namespace AST
