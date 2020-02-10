#pragma once

#include "ast/node.h"

namespace AST
{

class Expression: public Node
{
public:
	static std::unique_ptr<Expression> create(const Parse::Tree *ptNode);
};

} //namespace AST
