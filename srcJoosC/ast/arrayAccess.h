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

	std::unique_ptr<Expression> array;
	std::unique_ptr<Expression> index;

	std::string toCode() override;
};

} //namespace AST
