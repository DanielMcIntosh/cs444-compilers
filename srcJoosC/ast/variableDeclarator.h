#pragma once

#include "ast/node.h"
#include <memory>
#include <string>

namespace AST
{

class Expression;

class VariableDeclarator: public Node
{
public:
	EXPORT static std::unique_ptr<VariableDeclarator> create(const Parse::Tree *ptNode);
	explicit VariableDeclarator(const Parse::TVariableDeclarator *ptNode);
	std::string toCode() const override { return "[VariableDeclarator]"; }
protected:
	std::string id;
	std::unique_ptr<Expression> initializer;
	friend class VariableDeclaration;
};

} //namespace AST
