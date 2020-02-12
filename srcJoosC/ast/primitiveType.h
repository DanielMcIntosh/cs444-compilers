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
		Max
	} type;

	std::string toCode() override;
};

std::string operator+(std::string str, PrimitiveType::Variant type);
std::string operator+=(std::string& str, PrimitiveType::Variant type);
std::ostream& operator<<(std::ostream& os, PrimitiveType::Variant type);

} //namespace AST
