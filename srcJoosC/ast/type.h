#pragma once

#include "ast/node.h"

namespace AST
{

class Type: public Node
{
public:
	Type(std::vector<Parser::ASTToken>& children);

	//IMPORTANT: we need to update this if we hit the ArrayType rule
	bool isArray = false;
protected:
	Type() = default;
};

} //namespace AST
