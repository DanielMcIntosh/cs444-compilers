#pragma once

#include "ast/type.h"
#include <map>

namespace AST
{

class PrimitiveType: public Type
{
public:
	PrimitiveType(std::vector<Parser::ASTToken>& children);

	enum class Value
	{
		Boolean,
		Byte,
		Short,
		Int,
		Char,
	};

	Value val;

	static const std::map<std::string, Value> valueLookup;
};


} //namespace AST
