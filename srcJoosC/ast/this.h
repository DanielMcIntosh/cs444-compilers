#pragma once

#include "ast/expression.h"

namespace AST
{

// mostly a dummy class - the equivalent of the Literal class, but for a "this" expression
class This: public Expression
{
public:
	This(std::vector<Parser::ASTToken>& children);

};

} //namespace AST
