#pragma once

#include "ast/expression.h"
#include <memory>

namespace AST
{

class ArrayAccess: public Expression
{
public:
	static std::unique_ptr<ArrayAccess> create(const Parse::Tree *ptNode);
	ArrayAccess(const Parse::TArrayAccess *ptNode);

	std::shared_ptr<Expression> array;
	std::shared_ptr<Expression> index;

	std::string toCode() override { return "[ArrayAccess]"; }
};

} //namespace AST
