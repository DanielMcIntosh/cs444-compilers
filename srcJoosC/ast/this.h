#pragma once

#include "ast/expression.h"

namespace AST
{

// mostly a dummy class - the equivalent of the Literal class, but for a "this" expression
class This: public Expression
{
public:
	static std::unique_ptr<This> create(const Parse::Tree *ptNode);
	explicit This(const Parse::TThis2 *ptNode);

	std::string toCode() override;
};

} //namespace AST
