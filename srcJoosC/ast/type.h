#pragma once

#include "ast/node.h"

namespace AST
{

class Type: public Node
{
public:
	static std::unique_ptr<Type> create(const Parse::Tree *ptNode);

	bool isArray = false;
protected:
	Type() = default;
};

} //namespace AST
