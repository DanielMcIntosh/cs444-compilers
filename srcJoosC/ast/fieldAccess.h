#pragma once

#include "ast/expression.h"
#include <memory>
#include <string>

namespace AST
{

class FieldAccess: public Expression
{
public:
	static std::unique_ptr<FieldAccess> create(const Parse::Tree *ptNode);
	explicit FieldAccess(const Parse::TFieldAccess *ptNode);

	std::unique_ptr<Expression> object;
	std::string member;

	std::string toCode() const override;
};

} //namespace AST
