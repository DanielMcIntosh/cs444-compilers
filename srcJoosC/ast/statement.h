#pragma once

#include "ast/node.h"

namespace AST
{

class Statement: public Node
{
public:
	static std::unique_ptr<Statement> create(const Parse::Tree *ptNode);
};

} //namespace AST
