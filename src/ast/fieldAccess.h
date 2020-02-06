#pragma once

#include "ast/expression.h"
#include <memory>
#include <string>

namespace AST
{

class FieldAccess: public Expression
{
public:
	FieldAccess(std::vector<Parser::ASTToken>& children);

	std::shared_ptr<Expression> object;
	std::string member;
};

} //namespace AST
