#pragma once

#include "ast/node.h"
#include "ast/expression.h"
#include <memory>
#include <string>

namespace AST
{

class VariableDeclarator: public Node
{
public:
	static std::unique_ptr<VariableDeclarator> create(const Parse::Tree *ptNode);
	VariableDeclarator(const Parse::TVariableDeclarator *ptNode);

	std::string id;
	std::unique_ptr<Expression> initializer;

	std::string toCode() override { return "[VariableDeclarator]"; }
};

} //namespace AST
