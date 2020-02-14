#pragma once

#include "ast/expression.h"
#include "utility.h"
#include <variant>
#include <string>

namespace AST
{

class Literal: public Expression
{
public:
	static std::unique_ptr<Literal> create(const Parse::Tree *ptNode);
	explicit Literal(const Parse::TLiteral *ptNode);

	struct null {};
	std::variant<unsigned int,bool,char,std::string,null> value;

	std::string toCode() override;
};

} //namespace AST
