#pragma once

#include "ast/node.h"

namespace AST
{

class Type: public Node
{
public:
	static std::unique_ptr<Type> create(const Parse::Tree *ptNode);

	//IMPORTANT: we need to update this if we hit the ArrayType rule
	bool isArray = false;

	std::string toCode() override { return "[Type]"; }
protected:
	Type() = default;
};

} //namespace AST
