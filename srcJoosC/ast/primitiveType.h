#pragma once

#include "ast/type.h"
#include <map>

namespace AST
{

class PrimitiveType: public Type
{
public:
	static std::unique_ptr<PrimitiveType> create(const Parse::Tree *ptNode);
	PrimitiveType(const Parse::TPrimitiveType *ptNode);

	enum class Variant
	{
		Boolean,
		Byte,
		Short,
		Int,
		Char,
	};

	Variant val;
private:
	static const std::map<std::string, Variant> valueLookup;

	std::string toCode() override { return "[PrimitiveType]"; }
};


} //namespace AST
